/**
 * Ozero IO
 *
 * A class representing the crc16 checksum.
 */

#ifndef OZERO_IO_CYCLIC_REDUNDANCY_CHECKSUM_H
#define OZERO_IO_CYCLIC_REDUNDANCY_CHECKSUM_H 1

#include <Checksum/Checksum.h>
#include <inttypes.h>

class CyclicRedundancyChecksum : public virtual Checksum {
protected:
	/*
	 * CRC value.
	 */
	uint16_t crc;

public:
	/*
	 * Public constructor.
	 */
	CyclicRedundancyChecksum();

	/**
	 * Updates the current CRC16 checksum with the specified array of bytes.
	 *
	 * @param b the byte array to update the CRC16 checksum with
	 * @param off the start offset of the data
	 * @param len the number of bytes to use for the update
	 */
	void update(unsigned char *b, int off, int len);

	/**
	 * Resets the crc to its initial value.
	 */
	void reset();

	/**
	 * Resets the crc to its initial value.
	 */
	int getValue();
};

#endif /* OZERO_IO_CYCLIC_REDUNDANCY_CHECKSUM_H */
