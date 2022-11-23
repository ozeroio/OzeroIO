/**
 * Ozero IO
 * 
 * RandomAccess
 * 
 * Interface derived from DataInput, DataOutput, Closeable and Seekable.
 */

#ifndef __OZEROIO_IO_RANDOM_ACCESS_H__
#define __OZEROIO_IO_RANDOM_ACCESS_H__ 1

#include <DataOutput/DataOutput.h>
#include <DataInput/DataInput.h>
#include <Closeable/Closeable.h>
#include <Seekable/Seekable.h>

class RandomAccess : public virtual DataOutput, public virtual DataInput,
        public virtual Closeable, public virtual Seekable {
};

#endif /* __OZEROIO_IO_RANDOM_ACCESS_H__ */
