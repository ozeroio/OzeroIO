/**
 * Ozero IO
 *
 * An asynchronous ring buffered output stream that buffers output and flushes it
 * asynchronously in a separate FreeRTOS task. This implementation uses a ring buffer
 * of multiple buffers to minimize memory usage on the FreeRTOS queue while maintaining
 * non-blocking async writes. Only metadata (buffer index and byte count) is queued,
 * not entire buffers.
 */

#ifndef OZERO_IO_ASYNC_BUFFERED_OUTPUT_STREAM_H
#define OZERO_IO_ASYNC_BUFFERED_OUTPUT_STREAM_H 1

#if OZERO_IO_ASYNC_STREAM_ENABLED == 1

#define OZERO_IO_ASYNC_BUFFERED_OUTPUT_STREAM_TASK_NAME ("Async Circular Flusher")
#define OZERO_IO_ASYNC_BUFFERED_OUTPUT_STREAM_TASK_PRIORITY (1)
#define OZERO_IO_ASYNC_BUFFERED_OUTPUT_STREAM_QUEUE_SIZE (16)

#ifndef OZERO_IO_ASYNC_BUFFERED_OUTPUT_STREAM_TASK_STACK_SIZE
#define OZERO_IO_ASYNC_BUFFERED_OUTPUT_STREAM_TASK_STACK_SIZE (2048)
#endif

#ifndef OZERO_IO_ASYNC_BUFFERED_OUTPUT_STREAM_NUM_BUFFERS
#define OZERO_IO_ASYNC_BUFFERED_OUTPUT_STREAM_NUM_BUFFERS (2)
#endif

#include <BufferedOutputStream/BufferedOutputStream.h>
#include <InputStream/InputStream.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>
#include <freertos/task.h>

/**
 * Metadata for each queued flush operation.
 * Holds only the necessary information about what to flush (8 bytes total).
 */
struct AsyncBufferFlushItem {
	/**
	 * Number of bytes to write from the buffer.
	 */
	int bytesToWrite;

	/**
	 * Index in the ring buffer pool indicating which buffer to write.
	 */
	uint8_t bufferIndex;
};

class AsyncBufferedOutputStream : public BufferedOutputStream {

public:
	/**
	 * Public constructor that initializes the ring buffering system.
	 * Allocates a ring buffer of flush buffers for efficient async flushing.
	 *
	 * @param outputStream The underlying output stream to write flushed data to
	 * @param buf The primary write buffer for accumulating data
	 * @param size The size of each buffer in bytes
	 * @param numFlushBuffers The number of buffers in the ring buffer pool (default: 2)
	 */
	AsyncBufferedOutputStream(OutputStream *outputStream, unsigned char *buf, int size, int numFlushBuffers = OZERO_IO_ASYNC_BUFFERED_OUTPUT_STREAM_NUM_BUFFERS);

	/**
	 * Virtual destructor that cleans up FreeRTOS resources and allocated buffers.
	 */
	~AsyncBufferedOutputStream() override;

	/**
	 * Asynchronously writes len bytes from the specified unsigned char array
	 * starting at offset off to this buffered output stream.
	 * Returns immediately after buffering; actual write happens in the flusher task.
	 *
	 * @param b The array of bytes to write
	 * @param off The start offset in the array
	 * @param len The number of bytes to write
	 */
	void write(unsigned char *b, int off, int len) override;

	/**
	 * Flushes the internal buffer asynchronously and waits for the queue to drain.
	 * This ensures all pending async flushes are completed before returning.
	 */
	void flush() override;

protected:
	/**
	 * FreeRTOS task handle for the async flusher task.
	 */
	TaskHandle_t task;

	/**
	 * Queue handle for passing flush metadata to the flusher task.
	 * Uses small AsyncBufferFlushItem structs (8 bytes) instead of full buffers.
	 */
	QueueHandle_t queue;

	/**
	 * Array of ring buffer pointers, each buffer of size 'size'.
	 */
	unsigned char **flushBuffers;

	/**
	 * Total number of buffers in the ring buffer pool.
	 */
	int numFlushBuffers;

	/**
	 * Current index for getting the next available flush buffer.
	 * Cycles through 0 to numFlushBuffers-1.
	 */
	int availableFlushIndex;

	/**
	 * Counting semaphore for synchronizing flush operations.
	 * Allows up to numFlushBuffers concurrent pending async operations.
	 * Each take() by flushBuffer() represents one pending flush.
	 * Each give() by flusherTask() represents one completed flush.
	 */
	SemaphoreHandle_t flushSemaphore;

	/**
	 * Asynchronously flushes the internal buffer by queueing metadata to the flusher task.
	 * Only metadata about the flush is sent to the queue, not the entire buffer.
	 * If the queue is full, falls back to synchronous write.
	 */
	void flushBuffer() override;

	/**
	 * Static FreeRTOS task function for asynchronously flushing buffers.
	 * Runs continuously, receiving flush metadata from the queue and writing data.
	 *
	 * @param parameters Pointer to the AsyncBufferedOutputStream instance
	 */
	static void flusherTask(void *parameters);

private:
	/**
	 * Gets the next available flush buffer from the ring buffer pool.
	 * Implements round-robin allocation of buffers.
	 *
	 * @return Pointer to the next available buffer
	 */
	unsigned char *getNextFlushBuffer();
};

#endif// OZERO_IO_ASYNC_STREAM_ENABLED
#endif// OZERO_IO_ASYNC_BUFFERED_OUTPUT_STREAM_H
