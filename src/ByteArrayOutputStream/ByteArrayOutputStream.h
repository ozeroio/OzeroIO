/**
 * Ozero IO
 *
 * ByteArrayOutputStream
 *
 * This class implements an output stream in which the data is written into a
 * unsigned char array.
 */

#ifndef OZEROIO_IO_BYTE_ARRAY_OUTPUT_STREAM_H
#define OZEROIO_IO_BYTE_ARRAY_OUTPUT_STREAM_H 1

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
	unsigned int count;

	/*
	 * Current position
	 */
	unsigned int pos;

	/**
	 * The currently marked position in the stream.
	 */
	unsigned int markpos;

public:
	/**
	 * Public constructor.
	 *
	 * @param buf
	 * @param count
	 */
	ByteArrayOutputStream(unsigned char *buf, unsigned int count);

	/**
	 * Virtual destructor.
	 */
	virtual ~ByteArrayOutputStream() = default;

	/**
	 * Returns the current size of the buffer.
	 *
	 * @return unsigned int The size of the stream.
	 */
	unsigned int size() const;

	/**
	 * Creates a newly allocated unsigned char array.
	 *
	 * @return unsigned char* The unsigned char array.
	 */
	unsigned char *toByteArray();

	/**
	 * Using parent write.
	 */
	using OutputStream::write;

	/**
	 * Writes the specified unsigned char to this output stream.
	 *
	 * @param b The unsigned char to be written.
	 */
	void write(unsigned char b) override;

	/**
	 * Marks the current position in this input stream.
	 */
	void mark() override;

	/**
	 * Tests if this input stream supports the mark and reset methods.
	 *
	 * @return bool
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
	void seek(unsigned int pos) override;
};

#endif// OZEROIO_IO_BYTE_ARRAY_OUTPUT_STREAM_H
