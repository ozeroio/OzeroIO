/**
 * Ozero IO
 */

#ifndef OZEROIO_IO_SEEKABLE_INPUT_STREAM_H
#define OZEROIO_IO_SEEKABLE_INPUT_STREAM_H 1

#include <InputStream/InputStream.h>
#include <Seekable/Seekable.h>

class SeekableInputStream : public virtual Seekable, public virtual InputStream {
public:
};

#endif// OZEROIO_IO_SEEKABLE_INPUT_STREAM_H
