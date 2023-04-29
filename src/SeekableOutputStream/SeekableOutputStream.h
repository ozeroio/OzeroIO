/**
 * Ozero IO
 * 
 * SeekableOutputStream
 */

#ifndef OZEROIO_IO_SEEKABLE_OUTPUT_STREAM_H
#define OZEROIO_IO_SEEKABLE_OUTPUT_STREAM_H 1

#include <Seekable/Seekable.h>
#include <OutputStream/OutputStream.h>

class SeekableOutputStream : public virtual Seekable, public virtual OutputStream {
public:

};

#endif // OZEROIO_IO_SEEKABLE_OUTPUT_STREAM_H
