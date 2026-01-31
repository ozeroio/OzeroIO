/**
 * Ozero IO
 *
 * An asynchronous buffered output stream that buffers output and flushes it asynchronously
 * in a separate FreeRTOS task. This allows non-blocking writes to be buffered and flushed
 * without blocking the caller.
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
	 * @param inputStream The underlying output stream
	 * @param buf The buffer to use for buffering
	 * @param size The size of the buffer
	 */
	AsyncBufferedOutputStream(OutputStream *inputStream, unsigned char *buf, int size);

	/**
	 * Virtual destructor.
	 */
	~AsyncBufferedOutputStream() override;

	/**
	 * Asynchronously writes len bytes from the specified unsigned char array
	 * starting at offset off to this buffered output stream.
	 *
	 * @param b The array of bytes to write
	 * @param off The start offset in the array
	 * @param len The number of bytes to write
	 */
	void write(unsigned char *b, int off, int len) override;

protected:
	/**
	 * Task to asynchronously flush the buffer.
	 */
	TaskHandle_t task;

	/**
	 * Queue handle to send flushable buffers to the flusher task.
	 */
	QueueHandle_t queue;

	/**
	 * Size of the async buffer.
	 */
	int asyncPos;

	/**
	 * Flush the internal buffer
	 */
	void flushBuffer() override;

	/**
	 * Flush task handler for asynchronously flushing the buffer.
	 *
	 * @param parameters Pointer to the AsyncBufferedOutputStream instance
	 */
	static void flusherTask(const void *parameters);
};

#endif// OZERO_IO_ASYNC_STREAM_ENABLED
#endif// OZERO_IO_ASYNC_BUFFERED_INPUT_STREAM_H
