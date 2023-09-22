#include "DataInputStream.h"

DataInputStream::DataInputStream(InputStream *inputStream) : FilterInputStream(inputStream) {
}

int DataInputStream::read() {
	return FilterInputStream::read();
}

int DataInputStream::read(unsigned char *b, int off, int len) {
	return FilterInputStream::read(b, off, len);
}
