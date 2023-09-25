#include "DataOutputStream.h"

DataOutputStream::DataOutputStream(OutputStream *outputStream) : FilterOutputStream(outputStream) {
}

void DataOutputStream::write(unsigned char *b, int off, int len) {
	FilterOutputStream::write(b, off, len);
}

void DataOutputStream::write(unsigned char b) {
	FilterOutputStream::write(b);
}
