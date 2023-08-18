/**
 * Ozero IO
 *
 * SeekableOutputStream
 */

#ifndef OZEROIO_IO_SEEKABLE_OUTPUT_STREAM_H
#define OZEROIO_IO_SEEKABLE_OUTPUT_STREAM_H 1

#include <OutputStream/OutputStream.h>
#include <Seekable/Seekable.h>

class SeekableOutputStream : public virtual Seekable, public virtual OutputStream {
public:
};

#endif// OZEROIO_IO_SEEKABLE_OUTPUT_STREAM_H
