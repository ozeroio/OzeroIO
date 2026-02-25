/**
 * Ozero Stream
 *
 * Checksum
 *
 * A class representing a checksum.
 */

#include "Checksum.h"

void Checksum::update(unsigned char *b, int len) {
	update(b, 0, len);
}

void Checksum::update(unsigned char b) {
	update((unsigned char *) &b, 0, 1);
}
