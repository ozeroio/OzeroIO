/**
 * Ozero IO
 * 
 * SeekableOutputStream
 */

#ifndef __OZEROIO_IO_SEEKABLE_OUTPUT_STREAM_H__
#define __OZEROIO_IO_SEEKABLE_OUTPUT_STREAM_H__ 1

#include <Seekable/Seekable.h>
#include <OutputStream/OutputStream.h>

class SeekableOutputStream : public virtual Seekable, public virtual OutputStream {
public:

};

#endif /* __OZEROIO_IO_SEEKABLE_OUTPUT_STREAM_H__ */
