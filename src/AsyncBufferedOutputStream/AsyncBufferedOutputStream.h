/**
 * Ozero IO
 */

#ifndef OZERO_IO_ASYNC_BUFFERED_INPUT_STREAM_H
#define OZERO_IO_ASYNC_BUFFERED_INPUT_STREAM_H 1

#if OZERO_IO_ASYNC_STREAM_ENABLED == 1

#define OZERO_IO_ASYNC_BUFFERED_OUTPUT_STREAM_TASK_NAME ("Async Flusher")
#define OZERO_IO_ASYNC_BUFFERED_OUTPUT_STREAM_TASK_PRIORITY (1)
#define OZERO_IO_ASYNC_BUFFERED_OUTPUT_STREAM_QUEUE_SIZE (1)

#ifndef OZERO_IO_ASYNC_BUFFERED_OUTPUT_STREAM_TASK_STACK_SIZE
#define OZERO_IO_ASYNC_BUFFERED_OUTPUT_STREAM_TASK_STACK_SIZE (1024)
#endif

#include <BufferedOutputStream/BufferedOutputStream.h>
#include <InputStream/InputStream.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>

class AsyncBufferedOutputStream : public BufferedOutputStream {

public:
	/**
	 * Public constructor.
	 *
	 * @param in
	 * @param buf
	 * @param size
	 */
	AsyncBufferedOutputStream(OutputStream *inputStream, unsigned char *buf, int size);

	/**
	 * Virtual destructor.
	 */
	~AsyncBufferedOutputStream() override;

	void write(unsigned char *b, int off, int len) override;

protected:
	TaskHandle_t task;
	QueueHandle_t queue;

	/**
	 * Flush the internal buffer
	 */
	void flushBuffer() override;

	/**
	 * Flush task handler.
	 *
	 * @param parameters
	 */
	static void flusherTask(const void *parameters);
};

#endif// OZERO_IO_ASYNC_STREAM_ENABLED
#endif// OZERO_IO_ASYNC_BUFFERED_INPUT_STREAM_H
