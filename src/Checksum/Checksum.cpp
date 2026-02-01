/**
 * Ozero Stream
 *
 * Checksum
 *
 * A class representing a checksum.
 */

#include "Checksum.h"

void Checksum::update(uint8_t *b, int32_t len) {
	update(b, 0, len);
}

void Checksum::update(uint8_t b) {
	update((uint8_t *) &b, 0, 1);
}
