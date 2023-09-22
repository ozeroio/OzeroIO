#include <Arduino.h>
#include <OutputStream/OutputStream.h>
#include <InputStream/InputStream.h>
#include <DataOutput/DataOutput.h>
#include <DataInput/DataInput.h>

#ifndef TEST_H
#define TEST_H 1

uint32_t prevTime = 0;

void assertTrue(bool expression);
void assertTrueThat(const char *that, bool expression);
bool compareBuffers(uint8_t *a, uint8_t *b, const int len);
void initializeBuffer(uint8_t *buffer, const int len, const bool rand);
void measureTimeBegin();
void measureTimeEnd();
void log(const char *msg);
void logPair(const char *key, uint32_t value);

// Common tests

// OutputStream
void testWhenSendingEntireBufferSize(OutputStream *bos, uint8_t *streamBuffer, uint8_t *sourceBuffer, int32_t size);
void testWhenSendingParts(OutputStream *bos, uint8_t *streamBuffer, uint8_t *sourceBuffer, int32_t size);
void testWhenSendingOneByOne(OutputStream *bos, uint8_t *streamBuffer, uint8_t *sourceBuffer, int32_t size);
void testNullPointerOrLen0(OutputStream *bos, uint8_t *streamBuffer, uint8_t *sourceBuffer, int32_t size);
void testWriteBeyondLimit(OutputStream *bos, uint8_t *streamBuffer, uint8_t *sourceBuffer, int32_t size);
void testMark(OutputStream *bos, uint8_t *streamBuffer, uint8_t *sourceBuffer, int32_t size);

// InputStream
void testWhenReadingFully(InputStream *is, uint8_t *streamBuffer, uint8_t *destinationBuffer, int32_t size);
void testWhenReadingParts(InputStream *is, uint8_t *streamBuffer, uint8_t *destinationBuffer, int32_t size);
void testNullPointerOrLen0(InputStream *is, uint8_t *streamBuffer, uint8_t *destinationBuffer, int32_t size);
void testReadBeyondLimit(InputStream *is, uint8_t *streamBuffer, uint8_t *destinationBuffer, int32_t size);
void testAvailable(InputStream *is, uint8_t *streamBuffer, uint8_t *destinationBuffer, int32_t size);
void testComparingBuffers(InputStream *is, uint8_t *streamBuffer, uint8_t *destinationBuffer, int32_t size, void (*testFunction)(InputStream *, uint8_t *, uint8_t *, int32_t));

// DataOutput
void testWriteSupportedTypes(DataOutput *out, uint8_t *streamBuffer, int32_t size);


#endif// TEST_H