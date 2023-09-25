#include <Arduino.h>
#include <DataInput/DataInput.h>
#include <DataOutput/DataOutput.h>
#include <ExternalEeprom/ExternalEeprom.h>
#include <InputStream/InputStream.h>
#include <OutputStream/OutputStream.h>

#ifndef TEST_H
#define TEST_H 1

uint32_t prevTime = 0;

void assertTrue(bool expression);
void assertTrueThat(const char *that, bool expression);
void initializeEeprom(ExternalEeprom *eeprom, int32_t len, bool rand);
bool compareBufferToEeprom(uint8_t *a, ExternalEeprom *eeprom, int32_t len);
bool compareBuffers(uint8_t *a, uint8_t *b, int32_t len);
void initializeBuffer(uint8_t *buffer, int32_t len, bool rand);
void measureTimeBegin();
void measureTimeEnd();
void log(const char *msg);
void logPair(const char *key, uint32_t value);

// Common tests

// OutputStream
void testWhenSendingEntireBufferSize(OutputStream *os, uint8_t *streamBuffer, uint8_t *sourceBuffer, int32_t size);
void testWhenSendingParts(OutputStream *os, uint8_t *streamBuffer, uint8_t *sourceBuffer, int32_t size);
void testWhenSendingOneByOne(OutputStream *os, uint8_t *streamBuffer, uint8_t *sourceBuffer, int32_t size);
void testNullPointerOrLen0(OutputStream *os, uint8_t *streamBuffer, uint8_t *sourceBuffer, int32_t size);
void testWriteBeyondLimit(OutputStream *os, uint8_t *streamBuffer, uint8_t *sourceBuffer, int32_t size);
void testMark(OutputStream *os, uint8_t *streamBuffer, uint8_t *sourceBuffer, int32_t size);

// Eeprom
void testEepromWhenSendingEntireBufferSize(OutputStream *os, ExternalEeprom *eeprom, uint8_t *sourceBuffer, int32_t size);
void testEepromWhenSendingParts(OutputStream *os, ExternalEeprom *eeprom, uint8_t *sourceBuffer, int32_t size);
void testEepromWhenSendingOneByOne(OutputStream *os, uint8_t *streamBuffer, uint8_t *sourceBuffer, int32_t size);
void testEepromNullPointerOrLen0(OutputStream *os, uint8_t *streamBuffer, uint8_t *sourceBuffer, int32_t size);
void testEepromWriteBeyondLimit(OutputStream *os, uint8_t *streamBuffer, uint8_t *sourceBuffer, int32_t size);
void testEepromMark(OutputStream *os, uint8_t *streamBuffer, uint8_t *sourceBuffer, int32_t size);

// InputStream
void testWhenReadingFully(InputStream *is, uint8_t *streamBuffer, uint8_t *destinationBuffer, int32_t size);
void testWhenReadingParts(InputStream *is, uint8_t *streamBuffer, uint8_t *destinationBuffer, int32_t size);
void testNullPointerOrLen0(InputStream *is, uint8_t *streamBuffer, uint8_t *destinationBuffer, int32_t size);
void testReadBeyondLimit(InputStream *is, uint8_t *streamBuffer, uint8_t *destinationBuffer, int32_t size);
void testAvailable(InputStream *is, uint8_t *streamBuffer, uint8_t *destinationBuffer, int32_t size);
void testInputStreamComparingBuffers(InputStream *is, uint8_t *streamBuffer, uint8_t *destinationBuffer, int32_t size, void (*testFunction)(InputStream *, uint8_t *, uint8_t *, int32_t));

// DataOutput
void testWriteSupportedTypes(DataOutput *out, uint8_t *streamBuffer, int32_t size);
void testEepromWriteSupportedTypes(DataOutput *out, ExternalEeprom *eeprom, int32_t size);

// DataInput
void testReadSupportedTypes(DataInput *in, uint8_t *streamBuffer, int32_t size);
void testEepromReadSupportedTypes(DataInput *in, ExternalEeprom *eeprom, int32_t size);

#endif// TEST_H