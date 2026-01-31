/**
 * Ozero IO
 *
 * Seekable class is an abstract class that defines seek.
 */

#ifndef OZERO_IO_SEEKABLE_H
#define OZERO_IO_SEEKABLE_H 1

class Seekable {
public:
	virtual ~Seekable() = default;

	/**
	 * Seeks to the desired position in the stream.
	 *
	 * @param pos The position to seek to
	 */
	virtual void seek(int pos) = 0;
};

#endif// OZERO_IO_SEEKABLE_H
