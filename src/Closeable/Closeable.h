/**
 * Ozero IO
 *
 * A Closeable is a abstract source or destination of
 * data that can be closed. After closing, further operations
 * on the resource may fail.
 */

#ifndef OZERO_IO_CLOSEABLE_H
#define OZERO_IO_CLOSEABLE_H 1

class Closeable {
public:
	virtual ~Closeable() = default;

	/**
	 * Closes this resource, relinquishing any underlying resources.
	 */
	virtual void close() = 0;
};

#endif// OZERO_IO_CLOSEABLE_H
