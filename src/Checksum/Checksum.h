/**
 * Ozero IO
 *
 * A class representing a checksum.
 */

#ifndef OZERO_IO_CHECKSUM_H
#define OZERO_IO_CHECKSUM_H 1

#include <inttypes.h>

class Checksum {
public:
	/**
	 * Updates the current checksum with the specified byte.
	 *
	 * @param b the byte to update the checksum with
	 */
	void update(unsigned char b);

	/**
	 * Updates the current checksum with the specified array of bytes.
	 *
	 * @param b the array of bytes to update the checksum with
	 * @param len the number of bytes to use for the update
	 */
	void update(unsigned char *b, int len);

	/**
	 * Updates the current checksum with the specified array of bytes.
	 *
	 * @param b the byte array to update the checksum with
	 * @param off the start offset of the data
	 * @param len the number of bytes to use for the update
	 */
	virtual void update(unsigned char *b, int off, int len) = 0;

	/**
	 * Resets the checksum to its initial value.
	 */
	virtual void reset() = 0;
};

#endif /* OZERO_IO_CHECKSUM_H */
