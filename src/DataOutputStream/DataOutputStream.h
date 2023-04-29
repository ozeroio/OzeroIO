/**
 * Ozero IO
 * 
 * DataOutputStream
 *
 * A data output stream lets an application write types to an OutputStream.
 */

#ifndef OZEROIO_IO_DATA_OUTPUT_STREAM_H
#define OZEROIO_IO_DATA_OUTPUT_STREAM_H 1

#include <OutputStream/OutputStream.h>
#include <DataOutput/DataOutput.h>

class DataOutputStream : public DataOutput {

    /**
     * The stream to be used.
     */
    OutputStream *outputStream;

public:

    /**
     * Public constructor.
     * 
     * @param outputStream      The stream to be used.
     */
    explicit DataOutputStream(OutputStream *outputStream);

    /**
     * Writes an array of bytes into the stream.
     * 
     * @param b         The array of bytes.
     * @param len       The length of such array.
     */
    void write(unsigned char *b, int len) override;

    /**
     * Writes a unsigned char into the stream.
     * 
     * @param b         The unsigned char to be written.
     */
    void write(unsigned char b) override;

    /**
     * Writes a unsigned char into the stream.
     * 
     * @param b         The unsigned char to be written.
     */
    void writeByte(unsigned char b) override;

    /**
     * Writes an array of bytes into the stream.
     * 
     * @param b         The array of bytes.
     * @param len       The length of such array.
     */
    void writeBytes(unsigned char *b, int len) override;

    /**
     * Writes a bool into the stream.
     * 
     * @param v         The bool to be written.
     */
    void writeBoolean(bool v) override;

    /**
     * Writes a char into the stream.
     * 
     * @param c         The char to be written.
     */
    void writeChar(char c) override;

    /**
     * Writes an unsigned char into the stream.
     * 
     * @param c         The unsigned char to be written.
     */
    void writeUnsignedChar(unsigned char c) override;

    /**
     * Writes an int into the stream.
     * 
     * @param v         The int to be written.
     */
    void writeInt(int v) override;

    /**
     * Writes an unsigned int into the stream.
     * 
     * @param v         The unsigned int to be written.
     */
    void writeUnsignedInt(unsigned int v) override;

    /**
     * Writes a long into the stream.
     * 
     * @param v         The long to be written.
     */
    void writeLong(long v) override;

    /**
     * Writes a unsigned long into the stream.
     * 
     * @param v         The unsigned long to be written.
     */
    void writeUnsignedLong(unsigned long v) override;

    /**
     * Writes a float into the stream.
     * 
     * @param v         The float to be written.
     */
    void writeFloat(float v) override;

    /**
     * Writes a double into the stream.
     * 
     * @param v         The double to be written.
     */
    void writeDouble(double v) override;
};

#endif // OZEROIO_IO_DATA_OUTPUT_STREAM_H
