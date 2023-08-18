/**
 * Ozero IO
 *
 * RandomAccessExternalEeprom
 *
 * Instances of this class support both reading and writing to a random access
 * externalEeprom. A random access externalEeprom behaves like a large array of bytes
 * stored in the externalEeprom system.
 */

#if OZEROIO_IO_EXTERNAL_EEPROM_SUPPORT_ENABLED == 1

#ifndef OZEROIO_IO_RANDOM_ACCESS_EXTERNAL_EEPROM_H
#define OZEROIO_IO_RANDOM_ACCESS_EXTERNAL_EEPROM_H 1

#include <Closeable/Closeable.h>
#include <ExternalEeprom/ExternalEeprom.h>
#include <RandomAccess/RandomAccess.h>

class RandomAccessExternalEeprom : public RandomAccess, public virtual Closeable {

	/**
	 * The external eeprom to be used.
	 */
	ExternalEeprom *externalEeprom;

	/**
	 * Current position.
	 */
	unsigned int pos;

public:
	/**
	 * Public constructor.
	 *
	 * @param externalEeprom    The external eeprom instance to be used.
	 */
	explicit RandomAccessExternalEeprom(ExternalEeprom *externalEeprom);

	/**
	 * Seeks the stream at the position.
	 *
	 * @param pos       The position.
	 */
	void seek(unsigned int pos) override;

	/**
	 * Returns the length of the stream.
	 *
	 * @return          The length.
	 */
	unsigned int length();

	/**
	 * Closing a external eeprom has no effect.
	 */
	void close() override;

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
	 * Writes a short into the stream.
	 *
	 * @param v         The short to be written.
	 */
	void writeShort(short v) override;

	/**
	 * Writes an unsigned short into the stream.
	 *
	 * @param v         The unsigned short to be written.
	 */
	void writeUnsignedShort(unsigned short v) override;

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

	/**
	 * Reads a unsigned char from the stream.
	 *
	 * @return unsigned char
	 */
	unsigned char readByte() override;

	/**
	 * Reads a bool from the stream.
	 *
	 * @return bool
	 */
	bool readBoolean() override;

	/**
	 * Reads a char from the stream.
	 *
	 * @return char
	 */
	char readChar() override;

	/**
	 * Reads an unsigned char from the stream.
	 *
	 * @return unsigned char
	 */
	unsigned char readUnsignedChar() override;

	/**
	 * Reads a short from the stream.
	 *
	 * @return short
	 */
	short readShort() override;

	/**
	 * Reads an unsigned short from the stream.
	 *
	 * @return unsigned short
	 */
	unsigned short readUnsignedShort() override;

	/**
	 * Reads an int from the stream.
	 *
	 * @return int
	 */
	int readInt() override;

	/**
	 * Reads an unsigned int from the stream.
	 *
	 * @return unsigned int
	 */
	unsigned int readUnsignedInt() override;

	/**
	 * Reads a long from the stream.
	 *
	 * @return long
	 */
	long readLong() override;

	/**
	 * Reads a unsigned long from the stream.
	 *
	 * @return unsigned long
	 */
	unsigned long readUnsignedLong() override;

	/**
	 * Reads a float from the stream.
	 *
	 * @return float
	 */
	float readFloat() override;

	/**
	 * Reads a double from the stream.
	 *
	 * @return double
	 */
	double readDouble() override;

	/**
	 * Reads a array of bytes from the stream.
	 *
	 * @param b
	 * @param len
	 */
	void readFully(unsigned char *b, int len) override;

	/**
	 * Skips n bytes of the stream.
	 *
	 * @param n
	 * @return unsigned int The number of skipped bytes.
	 */
	unsigned int skipBytes(unsigned int n) override;
};

#endif// OZEROIO_IO_RANDOM_ACCESS_EXTERNAL_EEPROM_H

#endif// OZEROIO_IO_EXTERNAL_EEPROM_SUPPORT_ENABLED
