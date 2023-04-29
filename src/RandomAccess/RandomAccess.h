/**
 * Ozero IO
 * 
 * RandomAccess
 * 
 * Interface derived from DataInput, DataOutput, Closeable and Seekable.
 */

#ifndef OZEROIO_IO_RANDOM_ACCESS_H
#define OZEROIO_IO_RANDOM_ACCESS_H 1

#include <DataOutput/DataOutput.h>
#include <DataInput/DataInput.h>
#include <Closeable/Closeable.h>
#include <Seekable/Seekable.h>

class RandomAccess : public virtual DataOutput, public virtual DataInput,
                     public virtual Closeable, public virtual Seekable {
};

#endif // OZEROIO_IO_RANDOM_ACCESS_H
