#include "AsyncBufferedOutputStream.h"
#include <cstring>

#if OZERO_IO_ASYNC_STREAM_ENABLED == 1

AsyncBufferedOutputStream::AsyncBufferedOutputStream(
		OutputStream *outputStream,
		unsigned char *buf,
		const int size,
		int numFlushBuffers)
	: BufferedOutputStream(outputStream, buf, size),
	  task(nullptr),
	  queue(nullptr),
	  numFlushBuffers(numFlushBuffers),
	  availableFlushIndex(0) {

	// Allocate array of buffer pointers
	flushBuffers = new unsigned char *[numFlushBuffers];

	// Allocate each buffer in the ring
	for (int i = 0; i < numFlushBuffers; i++) {
		flushBuffers[i] = new unsigned char[size];
	}

	// Create queue with small metadata items instead of full buffers
	// This drastically reduces memory usage on the queue
	queue = xQueueCreate(OZERO_IO_ASYNC_BUFFERED_OUTPUT_STREAM_QUEUE_SIZE,
						 sizeof(AsyncBufferFlushItem));

	// Create counting semaphore for synchronizing flush operations
	// Initialize with numFlushBuffers to allow multiple concurrent flushes
	flushSemaphore = xSemaphoreCreateCounting(numFlushBuffers, numFlushBuffers);

	// Create flusher task
	xTaskCreate(
			AsyncBufferedOutputStream::flusherTask,
			OZERO_IO_ASYNC_BUFFERED_OUTPUT_STREAM_TASK_NAME,
			OZERO_IO_ASYNC_BUFFERED_OUTPUT_STREAM_TASK_STACK_SIZE,
			this,
			OZERO_IO_ASYNC_BUFFERED_OUTPUT_STREAM_TASK_PRIORITY,
			&task);
}

AsyncBufferedOutputStream::~AsyncBufferedOutputStream() {
	// Delete flusher task
	if (task != nullptr) {
		vTaskDelete(task);
		task = nullptr;
	}

	// Delete queue
	if (queue != nullptr) {
		vQueueDelete(queue);
		queue = nullptr;
	}

	// Delete semaphore
	if (flushSemaphore != nullptr) {
		vSemaphoreDelete(flushSemaphore);
		flushSemaphore = nullptr;
	}

	// Free all allocated buffers
	if (flushBuffers != nullptr) {
		for (int i = 0; i < numFlushBuffers; i++) {
			if (flushBuffers[i] != nullptr) {
				delete[] flushBuffers[i];
				flushBuffers[i] = nullptr;
			}
		}
		delete[] flushBuffers;
		flushBuffers = nullptr;
	}
}

unsigned char *AsyncBufferedOutputStream::getNextFlushBuffer() {
	unsigned char *buffer = flushBuffers[availableFlushIndex];
	availableFlushIndex = (availableFlushIndex + 1) % numFlushBuffers;
	return buffer;
}

void AsyncBufferedOutputStream::write(unsigned char *b, const int off, const int len) {
	if (b == nullptr || len == 0) {
		return;
	}

	// If the request length exceeds the size of the output buffer,
	// flush the output buffer and then write the data directly.
	// In this way buffered streams will cascade harmlessly.
	if (len >= size) {

		// Synchronously flush the buffer up to where it's filled
		outputStream->write(buf, 0, pos);

		// Then write the data directly
		outputStream->write(b, off, len);

		// Reset buffer info
		pos = 0;
		marked = false;

		return;
	}

	// If the request length exceeds the size of the available space,
	// flush the output buffer.
	const auto available = size - pos;
	if (len > available) {
		flushBuffer();
	}

	// Copy data to the current buffer.
	// After flush check: len < size and if len > available then buffer was flushed,
	// so len <= remaining available space.
	memcpy(&buf[pos], &b[off], len);
	pos += len;
}

void AsyncBufferedOutputStream::flushBuffer() {
	if (pos == 0) {
		return;
	}

	// Take the semaphore before queuing (will be given back when flusher finishes)
	if (flushSemaphore != nullptr) {
		xSemaphoreTake(flushSemaphore, portMAX_DELAY);
	}

	// Get next available flush buffer from ring pool
	unsigned char *flushBuf = getNextFlushBuffer();

	// Copy current buffer data to the flush buffer
	memcpy(flushBuf, buf, pos);

	// Create metadata item with only the necessary information
	AsyncBufferFlushItem item;
	item.bytesToWrite = pos;
	item.bufferIndex = (availableFlushIndex - 1 + numFlushBuffers) % numFlushBuffers;

	// Send metadata to queue (wait indefinitely for space)
	if (xQueueSend(queue, &item, portMAX_DELAY) == errQUEUE_FULL) {

		// Queue full - write directly to underlying stream as fallback.
		// This ensures data is never lost, though performance is degraded.
		outputStream->write(buf, 0, pos);

		// Give back the semaphore since we didn't queue anything
		if (flushSemaphore != nullptr) {
			xSemaphoreGive(flushSemaphore);
		}
	}

	// Reset buffer state
	pos = 0;
	marked = false;
}

void AsyncBufferedOutputStream::flusherTask(void *parameters) {
	auto instance = (AsyncBufferedOutputStream *) parameters;
	AsyncBufferFlushItem item;

	// Infinite loop waiting for flush items from the queue
	for (;;) {

		// Wait for flush items with indefinite blocking
		if (xQueueReceive(instance->queue, &item, portMAX_DELAY) == pdTRUE) {

			// Write from the specified buffer using the provided byte count
			instance->outputStream->write(
					instance->flushBuffers[item.bufferIndex],
					0,
					item.bytesToWrite);

			// Give back the semaphore to indicate this flush is complete
			if (instance->flushSemaphore != nullptr) {
				xSemaphoreGive(instance->flushSemaphore);
			}
		}
	}
}

void AsyncBufferedOutputStream::flush() {

	// First, flush any remaining buffered data
	BufferedOutputStream::flush();

	// Then wait for all pending async operations to complete
	// by draining the semaphore (taking all available permits)
	if (flushSemaphore != nullptr) {
		for (int i = 0; i < numFlushBuffers; i++) {
			xSemaphoreTake(flushSemaphore, portMAX_DELAY);
		}

		// Give them all back
		for (int i = 0; i < numFlushBuffers; i++) {
			xSemaphoreGive(flushSemaphore);
		}
	}
}

#endif// OZERO_IO_ASYNC_STREAM_ENABLED == 1
