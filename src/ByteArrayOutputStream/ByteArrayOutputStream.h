/**
 * Ozero IO
 *
 * This class implements an output stream in which the data is written into a
 * unsigned char array.
 */

#ifndef OZERO_IO_BYTE_ARRAY_OUTPUT_STREAM_H
#define OZERO_IO_BYTE_ARRAY_OUTPUT_STREAM_H 1

#include <SeekableOutputStream/SeekableOutputStream.h>

class ByteArrayOutputStream : public SeekableOutputStream {

protected:
	/*
	 * The buffer where data is stored.
	 */
	unsigned char *buf;

	/*
	 * The number of valid bytes in the buffer.
	 */
	int size;

	/*
	 * Current position
	 */
	int pos;

	/**
	 * The currently marked position in the stream.
	 */
	int markPos;

public:
	/**
	 * Public constructor.
	 *
	 * @param buf The unsigned char array to write to
	 * @param size The size of the array
	 */
	ByteArrayOutputStream(unsigned char *buf, int size);

	/**
	 * Virtual destructor.
	 */
	virtual ~ByteArrayOutputStream() = default;

	/**
	 * Returns the buffer size.
	 *
	 * @return int The size of the buffer.
	 */
	int getBufferSize() const;

	/**
	 * Returns the buffer.
	 *
	 * @return unsigned char* The unsigned char array.
	 */
	unsigned char *getBuffer();

	/**
	 * Writes the specified unsigned char to this output stream.
	 *
	 * @param b The unsigned char to be written.
	 */
	void write(unsigned char b) override;

	/**
	 * Writes len bytes from the specified unsigned char array starting at offset off to
	 * this output stream.
	 *
	 * @param b The array of bytes to write
	 * @param off The start offset in the array
	 * @param len The number of bytes to write
	 */
	void write(unsigned char *b, int off, int len) override;

	/**
	 * Using parent write.
	 */
	using OutputStream::write;

	/**
	 * Marks the current position in this input stream.
	 */
	void mark() override;

	/**
	 * Tests if this output stream supports the mark and reset methods.
	 *
	 * @return true if mark/reset is supported, false otherwise
	 */
	bool markSupported() override;

	/**
	 * Repositions this stream to the position at the time the mark method was
	 * last called on this input stream.
	 */
	void reset() override;

	/**
	 * Seeks to the desired position.
	 *
	 * @param pos The position we want to point to.
	 */
	void seek(int pos) override;
};

#endif// OZERO_IO_BYTE_ARRAY_OUTPUT_STREAM_H
