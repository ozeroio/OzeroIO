/**
 * Ozero IO
 *
 * A SeekableOutputStream is an output stream that also supports seeking to a specific position
 * in the stream. This interface combines the functionality of OutputStream and Seekable.
 */

#ifndef OZERO_IO_SEEKABLE_OUTPUT_STREAM_H
#define OZERO_IO_SEEKABLE_OUTPUT_STREAM_H 1

#include <OutputStream/OutputStream.h>
#include <Seekable/Seekable.h>

class SeekableOutputStream : public virtual Seekable, public virtual OutputStream {
public:
};

#endif// OZERO_IO_SEEKABLE_OUTPUT_STREAM_H
