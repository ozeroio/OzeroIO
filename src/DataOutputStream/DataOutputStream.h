/**
 * Ozero IO
 *
 * A data output stream lets an application write types to an OutputStream.
 */

#ifndef OZERO_IO_DATA_OUTPUT_STREAM_H
#define OZERO_IO_DATA_OUTPUT_STREAM_H 1

#include <DataOutput/DataOutput.h>
#include <FilterOutputStream/FilterOutputStream.h>
#include <OutputStream/OutputStream.h>

class DataOutputStream : public virtual FilterOutputStream, public virtual DataOutput {

public:
	/**
	 * Public constructor.
	 *
	 * @param outputStream      The stream to be used.
	 */
	explicit DataOutputStream(OutputStream *outputStream);

	/**
	 * Writes len bytes from the specified unsigned char array starting at offset off.
	 *
	 * @param b
	 * @param off
	 * @param len
	 */
	void write(unsigned char *b, int off, int len) override;

	/**
	 * Writes a unsigned char into the stream.
	 *
	 * @param b         The unsigned char to be written.
	 */
	void write(unsigned char b) override;
};

#endif// OZERO_IO_DATA_OUTPUT_STREAM_H
