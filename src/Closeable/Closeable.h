/**
 * Ozero IO
 *
 * A Closeable is a source or destination of data that can be closed.
 */

#ifndef OZERO_IO_CLOSEABLE_H
#define OZERO_IO_CLOSEABLE_H 1

class Closeable {
public:
	virtual ~Closeable() = default;
	virtual void close() = 0;
};

#endif// OZERO_IO_CLOSEABLE_H
