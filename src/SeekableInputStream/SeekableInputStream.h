/**
 * Ozero IO
 * 
 * SeekableInputStream
 */

#ifndef __OZEROIO_IO_SEEKABLE_INPUT_STREAM_H__
#define __OZEROIO_IO_SEEKABLE_INPUT_STREAM_H__ 1

#include <Seekable/Seekable.h>
#include <InputStream/InputStream.h>

class SeekableInputStream : public virtual Seekable, public virtual InputStream {
public:

};

#endif /* __OZEROIO_IO_SEEKABLE_INPUT_STREAM_H__ */
