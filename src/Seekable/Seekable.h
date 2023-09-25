/**
 * Ozero IO
 *
 * Seekable class is an abstract class that defines seek.
 */

#ifndef OZEROIO_IO_SEEKABLE_H
#define OZEROIO_IO_SEEKABLE_H 1

class Seekable {
public:
	virtual void seek(int pos) = 0;
};

#endif// OZEROIO_IO_SEEKABLE_H
