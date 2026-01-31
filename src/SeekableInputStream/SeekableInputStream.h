/**
 * Ozero IO
 *
 * A SeekableInputStream is an input stream that also supports seeking to a specific position
 * in the stream. This interface combines the functionality of InputStream and Seekable.
 */

#ifndef OZERO_IO_SEEKABLE_INPUT_STREAM_H
#define OZERO_IO_SEEKABLE_INPUT_STREAM_H 1

#include <InputStream/InputStream.h>
#include <Seekable/Seekable.h>

class SeekableInputStream : public virtual Seekable, public virtual InputStream {
public:
};

#endif// OZERO_IO_SEEKABLE_INPUT_STREAM_H
