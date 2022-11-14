/**
 * Ozero IO
 * 
 * Seekable
 */

#ifndef __OZEROIO_IO_SEEKABLE_H__
#define __OZEROIO_IO_SEEKABLE_H__ 1

class Seekable {
public:

    virtual void seek(unsigned int pos) = 0;
};

#endif /* __OZEROIO_IO_SEEKABLE_H__ */
