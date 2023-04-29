/**
 * Ozero IO
 * 
 * SeekableInputStream
 */

#ifndef OZEROIO_IO_SEEKABLE_INPUT_STREAM_H
#define OZEROIO_IO_SEEKABLE_INPUT_STREAM_H 1

#include <Seekable/Seekable.h>
#include <InputStream/InputStream.h>

class SeekableInputStream : public virtual Seekable, public virtual InputStream {
public:

};

#endif // OZEROIO_IO_SEEKABLE_INPUT_STREAM_H
