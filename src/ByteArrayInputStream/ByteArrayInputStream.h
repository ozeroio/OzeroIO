/**
 * Ozero IO
 * 
 * ByteArrayInputStream
 *
 * A ByteArrayInputStream contains an internal buffer that contains bytes that 
 * may be read from the stream.
 */

#ifndef __OZEROIO_IO_BYTE_ARRAY_INPUT_STREAM_H__
#define __OZEROIO_IO_BYTE_ARRAY_INPUT_STREAM_H__ 1

#include <SeekableInputStream/SeekableInputStream.h>

class ByteArrayInputStream : public virtual SeekableInputStream {

protected:

    /* 
     * The buffer where data is stored.
     */
    unsigned char* buf;

    /*
     * The number of valid bytes in the buffer.
     */
    unsigned int count;

    /*
     * Current position
     */
    unsigned int pos;

    /*
     * The currently marked position in the stream.
     */
    unsigned int markpos;

public:

    ByteArrayInputStream(unsigned char* buf, unsigned int count);

    /**
     * Returns the number of bytes that can be read(or skipped over) from this 
     * input stream without blocking by the next caller of a method for this input stream.
     * 
     * NOTE: This implementation return 1 or 0. It is because the size 
     * of the array is unsigned int, and this method returns a signed
     * int, which means there is no way to return the difference between
     * the current position (can be 0) and the size of the array without
     * possible overflow. 
     * 
     * @return 
     */
    virtual int available();

    /**
     * Marks the current position in this input stream.
     */
    virtual void mark();

    /**
     * Tests if this input stream supports the mark and reset methods.
     * 
     * @return 
     */
    virtual bool markSupported();

    /**
     * Using the parent's read.
     */
    using InputStream::read;

    /**
     * Reads the next unsigned char of data from the input stream.
     * 
     * @return 
     */
    virtual int read();

    /**
     * Repositions this stream to the position at the time the mark method was 
     * last called on this input stream.
     */
    virtual void reset();

    /**
     * Seeks to the desired position.
     *
     * @param pos The position we want to point to.
     */
    virtual void seek(unsigned int pos);
};

#endif /* __OZEROIO_IO_BYTE_ARRAY_INPUT_STREAM_H__ */
