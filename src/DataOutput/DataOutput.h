/**
 * Ozero IO
 *
 * DataOutput
 *
 * The DataOutput interface provides for converting data from any of the
 * primitive types to a series of bytes and writing these bytes to a binary stream.
 */

#ifndef OZEROIO_IO_DATA_OUTPUT_H
#define OZEROIO_IO_DATA_OUTPUT_H 1

class DataOutput {
public:
	/**
	 * Writes len bytes from the specified unsigned char array starting at offset off.
	 *
	 * @param b
	 * @param off
	 * @param len
	 */
	virtual void write(unsigned char *b, int off, int len) = 0;

	/**
	 * Writes an array of bytes into the stream.
	 *
	 * @param b         The array of bytes.
	 * @param len       The length of such array.
	 */
	virtual void write(unsigned char *b, int len);

	/**
	 * Writes a unsigned char into the stream.
	 *
	 * @param b         The unsigned char to be written.
	 */
	virtual void write(unsigned char b) = 0;

	/**
	 * Writes a unsigned char into the stream.
	 *
	 * @param b         The unsigned char to be written.
	 */
	virtual void writeByte(unsigned char b);

	/**
	 * Writes a bool into the stream.
	 *
	 * @param v         The bool to be written.
	 */
	virtual void writeBoolean(bool v);

	/**
	 * Writes a char into the stream.
	 *
	 * @param c         The char to be written.
	 */
	virtual void writeChar(char c);

	/**
	 * Writes an unsigned char into the stream.
	 *
	 * @param c         The unsigned char to be written.
	 */
	virtual void writeUnsignedChar(unsigned char c);

	/**
	 * Writes a short into the stream.
	 *
	 * @param v         The short to be written.
	 */
	virtual void writeShort(short v);

	/**
	 * Writes an unsigned short into the stream.
	 *
	 * @param v         The unsigned short to be written.
	 */
	virtual void writeUnsignedShort(unsigned short v);

	/**
	 * Writes an int into the stream.
	 *
	 * @param v         The int to be written.
	 */
	virtual void writeInt(int v);

	/**
	 * Writes an unsigned int into the stream.
	 *
	 * @param v         The unsigned int to be written.
	 */
	virtual void writeUnsignedInt(unsigned int v);

	/**
	 * Writes a long into the stream.
	 *
	 * @param v         The long to be written.
	 */
	virtual void writeLong(long v);

	/**
	 * Writes a unsigned long into the stream.
	 *
	 * @param v         The unsigned long to be written.
	 */
	virtual void writeUnsignedLong(unsigned long v);

	/**
	 * Writes a float into the stream.
	 *
	 * @param v         The float to be written.
	 */
	virtual void writeFloat(float v);

	/**
	 * Writes a double into the stream.
	 *
	 * @param v         The double to be written.
	 */
	virtual void writeDouble(double v);
};

#endif// OZEROIO_IO_DATA_OUTPUT_H
