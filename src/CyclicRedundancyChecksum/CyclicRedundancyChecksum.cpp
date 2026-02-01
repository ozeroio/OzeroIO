/**
 * Ozero Stream
 *
 * CyclicRedundancyChecksum
 *
 * A class representing the crc16 checksum.
 */

#include "CyclicRedundancyChecksum.h"

CyclicRedundancyChecksum::CyclicRedundancyChecksum() : crc(0) {
}

void CyclicRedundancyChecksum::update(unsigned char *b, int off, int len) {
	int end = off + len;
	for (int i = off; i < end; i++) {
		crc ^= b[i];
		for (uint8_t k = 0; k < 8; k++) {
			if (crc & 1) {
				crc = (crc >> 1) ^ 0xA001;
			} else {
				crc = (crc >> 1);
			}
		}
	}
}

void CyclicRedundancyChecksum::reset() {
	crc = 0;
}

int CyclicRedundancyChecksum::getValue() {
	return crc;
}
