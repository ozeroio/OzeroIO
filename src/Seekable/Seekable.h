/**
 * Ozero IO
 * 
 * Seekable
 */

#ifndef OZEROIO_IO_SEEKABLE_H
#define OZEROIO_IO_SEEKABLE_H 1

class Seekable {
public:

    virtual void seek(unsigned int pos) = 0;
};

#endif // OZEROIO_IO_SEEKABLE_H
