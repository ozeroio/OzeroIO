#if OZERO_IO_ASYNC_STREAM_ENABLED == 1

#include "AsyncBufferedOutputStream.h"
#include <cstring>

AsyncBufferedOutputStream::AsyncBufferedOutputStream(OutputStream *outputStream, unsigned char *buf, const int size)
	: BufferedOutputStream(outputStream, buf, size), task(nullptr) {
	xTaskCreate(
			reinterpret_cast<TaskFunction_t>(AsyncBufferedOutputStream::flusherTask),
			OZERO_IO_ASYNC_BUFFERED_OUTPUT_STREAM_TASK_NAME,
			OZERO_IO_ASYNC_BUFFERED_OUTPUT_STREAM_TASK_STACK_SIZE,
			this,
			OZERO_IO_ASYNC_BUFFERED_OUTPUT_STREAM_TASK_PRIORITY,
			&task);
	queue = xQueueCreate(OZERO_IO_ASYNC_BUFFERED_OUTPUT_STREAM_QUEUE_SIZE, sizeof(unsigned char) * size);
}

AsyncBufferedOutputStream::~AsyncBufferedOutputStream() {
	vTaskDelete(task);
	vQueueDelete(queue);
}

void AsyncBufferedOutputStream::write(unsigned char *b, const int off, const int len) {
	if (b == nullptr || len == 0) {
		return;
	}

	/*
	 * If the request length exceeds the size of the output buffer,
	 * flush the output buffer and then write the data directly.
	 * In this way buffered streams will cascade harmlessly.
	 */
	if (len >= size) {

		// Synchronously flush the buffer up to where it's filled.
		outputStream->write(buf, 0, pos);

		// Then write the data.
		outputStream->write(b, off, len);

		// Reset buffer info.
		pos = 0;
		marked = false;

		return;
	}

	/*
	 * If the request length exceeds the size of the available space,
	 * flush the output buffer.
	 */
	const auto available = size - pos;
	if (len > available) {
		flushBuffer();
	}

	/*
	 * Hence len < size & if len > available the buffer was flushed, the request length is necessary
	 * smaller or equals than the remaining available space inside the buffer.
	 */
	memcpy(&buf[pos], &b[off], len);

	pos += len;
}

void AsyncBufferedOutputStream::flushBuffer() {
	asyncSize = pos;
	if (asyncSize > 0) {
		xQueueSend(queue, buf, portMAX_DELAY);
		portYIELD();
	}
	pos = 0;
	marked = false;
}

void AsyncBufferedOutputStream::flusherTask(const void *parameters) {
	auto instance = (AsyncBufferedOutputStream *) parameters;
	unsigned char buffer[instance->size];
	for (;;) {
		if (xQueueReceive(instance->queue, &buffer, portMAX_DELAY) == pdTRUE) {
			instance->outputStream->write(buffer, 0, instance->asyncSize);
		}
	}
}

#endif// OZERO_IO_ASYNC_STREAM_ENABLED == 1