/**
 * Ozero IO
 * 
 * InternalEepromOutputStream
 *
 * A resource output stream is an output stream for writing data to an 
 * internal EEPROM.
 */

#if __OZEROIO_IO_INTERNAL_EEPROM_SUPPORT_ENABLED__ == 1

#ifndef __OZEROIO_IO_INTERNAL_EEPROM_OUTPUT_STREAM_H__
#define __OZEROIO_IO_INTERNAL_EEPROM_OUTPUT_STREAM_H__ 1

#include <SeekableOutputStream/SeekableOutputStream.h>

class InternalEepromOutputStream: public SeekableOutputStream {

    /**
     * Current eeprom position.
     */
    unsigned int pos;

    /**
     * The currently marked position in the stream.
     */
    unsigned int markpos;

    /**
     * Internal eeprom size.
     */
    unsigned int eepromSize;

public:

    /**
     * Public constructor.
     */
    InternalEepromOutputStream();

    /**
     * Using parent write.
     */
    using OutputStream::write;

    /**
     * Writes the specified unsigned char to this output stream.
     * 
     * @param b
     */
    virtual void write(unsigned char b);

    /**
     * Writes len bytes from the specified unsigned char array starting at offset off to 
     * this output stream.
     * 
     * @param b
     * @param off
     * @param len
     */
    virtual void write(unsigned char* b, int off, int len);

    /**
     * Seeks to the desired position.
     *
     * @param pos The position we want to point to.
     */
    virtual void seek(unsigned int pos);

    /**
     * Marks the current position in this output stream.
     */
    virtual void mark();

    /**
     * Tests if this output stream supports the mark and reset methods.
     */
    virtual bool markSupported();

    /**
     * Repositions this stream to the position at the time the mark method was
     * last called on this output stream.
     */
    virtual void reset();
};

#endif /* __OZEROIO_IO_INTERNAL_EEPROM_OUTPUT_STREAM_H__ */

#endif /* __OZEROIO_IO_INTERNAL_EEPROM_SUPPORT_ENABLED__ */
