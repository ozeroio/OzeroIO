/**
 * Ozero IO
 * 
 * ExternalEepromInputStream
 * 
 * An ExternalEepromInputStream obtains input bytes from a 
 * externalEeprom. 
 */

//#if OZEROIO_IO_EXTERNAL_EEPROM_SUPPORT_ENABLED == 1

#ifndef OZEROIO_IO_EXTERNAL_EEPROM_INPUT_STREAM_H
#define OZEROIO_IO_EXTERNAL_EEPROM_INPUT_STREAM_H 1

#include <SeekableInputStream/SeekableInputStream.h>
#include <ExternalEeprom/ExternalEeprom.h>

class ExternalEepromInputStream : public virtual SeekableInputStream {

protected:

    /**
     * When asking for available, this is the max number to return.
     */
    const int maxAvailableChunk;

    /* 
     * The externalEeprom where data is stored.
     */
    ExternalEeprom* externalEeprom;

    /*
     * Current position
     */
    unsigned int pos;

    /*
     * The currently marked position in the stream.
     */
    unsigned int markpos;

    /*
     * The size of the externalEeprom.
     */
    unsigned int externalEepromSize;

public:

    /**
     * Public constructor.
     * 
     * @param externalEeprom    The externalEeprom where data is stored.
     */
    ExternalEepromInputStream(ExternalEeprom* externalEeprom);

    /**
     * Returns the number of bytes that can be read(or skipped over) from this 
     * input stream without blocking by the next caller of a method for this 
     * input stream.
     * 
     * @return int      The available number of bytes.
     */
    int available() override;

    /**
     * Using the parent read.
     */
    using InputStream::read;

    /**
     * Reads the next unsigned char of data from the input stream.
     * 
     * @return int      The read unsigned char as an int.
     */
    int read() override;

    /**
     * Reads len of bytes from the input stream.
     * 
     * @param b
     * @param off
     * @param len
     * @return 
     */
    int read(unsigned char *b, int off, int len) override;

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

#endif // OZEROIO_IO_EXTERNAL_EEPROM_INPUT_STREAM_H

//#endif // OZEROIO_IO_EXTERNAL_EEPROM_SUPPORT_ENABLED
