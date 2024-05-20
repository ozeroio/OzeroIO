/**
 * Ozero IO
 *
 * The DataInput interface provides for reading bytes from a binary
 * stream and reconstructing from them data in any of the primitive
 * arduino types.
 */

#ifndef OZERO_IO_DATA_INPUT_H
#define OZERO_IO_DATA_INPUT_H 1

class DataInput {
public:
	virtual ~DataInput() = default;

	/**
	 * Reads the next unsigned char.
	 */
	virtual int read() = 0;

	/**
	 * Reads len of bytes and stores them into the buffer array b.
	 *
	 * @param b
	 * @param len
	 * @return
	 */
	virtual int read(unsigned char *b, int len);

	/**
	 * Reads len of bytes and stores them into the buffer array b with offset.
	 *
	 * @param b
	 * @param off
	 * @param len
	 * @return
	 */
	virtual int read(unsigned char *b, int off, int len) = 0;

	/**
	 * Reads a unsigned char from the stream.
	 *
	 * @return unsigned char
	 */
	virtual unsigned char readByte();

	/**
	 * Reads a bool from the stream.
	 *
	 * @return bool
	 */
	virtual bool readBoolean();

	/**
	 * Reads a char from the stream.
	 *
	 * @return char
	 */
	virtual char readChar();

	/**
	 * Reads an unsigned char from the stream.
	 *
	 * @return unsigned char
	 */
	virtual unsigned char readUnsignedChar();

	/**
	 * Reads a short from the stream.
	 *
	 * @return short
	 */
	virtual short readShort();

	/**
	 * Reads an unsigned short from the stream.
	 *
	 * @return unsigned short
	 */
	virtual unsigned short readUnsignedShort();

	/**
	 * Reads an int from the stream.
	 *
	 * @return int
	 */
	virtual int readInt();

	/**
	 * Reads an unsigned int from the stream.
	 *
	 * @return unsigned int
	 */
	virtual unsigned int readUnsignedInt();

	/**
	 * Reads a long from the stream.
	 *
	 * @return long
	 */
	virtual long readLong();

	/**
	 * Reads a unsigned long from the stream.
	 *
	 * @return unsigned long
	 */
	virtual unsigned long readUnsignedLong();

	/**
	 * Reads a float from the stream.
	 *
	 * @return float
	 */
	virtual float readFloat();

	/**
	 * Reads a double from the stream.
	 *
	 * @return double
	 */
	virtual double readDouble();
};

#endif// OZERO_IO_DATA_INPUT_H
