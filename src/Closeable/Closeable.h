/**
 * Ozero IO
 *
 * Closeable
 *
 * A Closeable is a source or destination of data that can be closed.
 */

#ifndef OZEROIO_IO_CLOSEABLE_H
#define OZEROIO_IO_CLOSEABLE_H 1

class Closeable {
public:
	virtual void close() = 0;
};

#endif// OZEROIO_IO_CLOSEABLE_H
