// #include <Arduino.h>
// #include <BufferedInputStream/BufferedInputStream.cpp>
// #include <ByteArrayInputStream/ByteArrayInputStream.cpp>
// #include <FilterInputStream/FilterInputStream.cpp>
// #include <InputStream/InputStream.cpp>

// #include "../test.cpp"
// #include "test_fillBuffer_bug.h"

// #define LEN 128
// #define BUFFER_SIZE 16

// /**
//  * Test to validate the BufferedInputStream::fillBuffer() bug fix.
//  *
//  * The bug: fillBuffer() reads into buf at offset 'pos' instead of 'pos' being reset to 0
//  * after shiftBuffer(). This causes:
//  * 1. Data to be read into the wrong position in the buffer
//  * 2. The head to be set to the number of bytes read, losing accumulated count
//  *
//  * Scenario: When the buffer is depleted and refilled, subsequent reads should
//  * continue from the correct position without data corruption.
//  */

// void testFillBufferDataIntegrity() {
// 	log("=== testFillBufferDataIntegrity ===");
// 	log("Testing that fillBuffer correctly repositions and refills the buffer");

// 	// Create a byte array with sequential data: 0x00, 0x01, 0x02, ..., 0x7F
// 	uint8_t sourceData[LEN];
// 	for (int i = 0; i < LEN; i++) {
// 		sourceData[i] = i & 0xFF;
// 	}

// 	// Create streams
// 	ByteArrayInputStream bais(sourceData, LEN);
// 	uint8_t bufferStorage[BUFFER_SIZE];
// 	BufferedInputStream bis(&bais, bufferStorage, BUFFER_SIZE);

// 	// Read data in chunks smaller than the buffer
// 	uint8_t readData[LEN];
// 	int totalRead = 0;

// 	// First, read 5 bytes (partially fills buffer from underlying stream)
// 	int n1 = bis.read(&readData[0], 5);
// 	totalRead += n1;
// 	log("Read 5 bytes");

// 	// Then read 12 bytes (should trigger shiftBuffer and fillBuffer)
// 	int n2 = bis.read(&readData[5], 12);
// 	totalRead += n2;
// 	log("Read 12 bytes");

// 	// Read remaining data
// 	while (totalRead < LEN) {
// 		int remaining = LEN - totalRead;
// 		int toRead = (remaining > 10) ? 10 : remaining;
// 		int n = bis.read(&readData[totalRead], toRead);
// 		if (n <= 0) break;
// 		totalRead += n;
// 	}

// 	// Verify that the data matches the original source
// 	bool match = compareBuffers(sourceData, readData, LEN);

// 	if (match) {
// 		log("Data integrity check: PASSED");
// 		assertTrue(true);
// 	} else {
// 		log("Data integrity check: FAILED");
// 		log("Differences found:");
// 		for (int i = 0; i < LEN; i++) {
// 			if (sourceData[i] != readData[i]) {
// 				Serial.print("Position ");
// 				Serial.print(i);
// 				Serial.print(": expected 0x");
// 				Serial.print(sourceData[i], HEX);
// 				Serial.print(", got 0x");
// 				Serial.println(readData[i], HEX);
// 			}
// 		}
// 		assertTrue(false);
// 	}
// }

// void testFillBufferMultipleCycles() {
// 	log("=== testFillBufferMultipleCycles ===");
// 	log("Testing fillBuffer across multiple buffer refill cycles");

// 	// Create source with repeating pattern
// 	uint8_t sourceData[LEN];
// 	for (int i = 0; i < LEN; i++) {
// 		sourceData[i] = (i % 256);
// 	}

// 	ByteArrayInputStream bais(sourceData, LEN);
// 	uint8_t bufferStorage[BUFFER_SIZE];
// 	BufferedInputStream bis(&bais, bufferStorage, BUFFER_SIZE);

// 	uint8_t readData[LEN];

// 	// Read with various chunk sizes to force multiple buffer refills
// 	int pos = 0;

// 	// Read 1 byte
// 	int n = bis.read(&readData[pos], 1);
// 	pos += n;

// 	// Read 3 bytes
// 	n = bis.read(&readData[pos], 3);
// 	pos += n;

// 	// Read 7 bytes
// 	n = bis.read(&readData[pos], 7);
// 	pos += n;

// 	// Read 20 bytes (forces buffer refill since 20 > BUFFER_SIZE)
// 	n = bis.read(&readData[pos], 20);
// 	pos += n;

// 	// Read remaining
// 	while (pos < LEN) {
// 		int toRead = LEN - pos;
// 		if (toRead > 15) toRead = 15;
// 		n = bis.read(&readData[pos], toRead);
// 		if (n <= 0) break;
// 		pos += n;
// 	}

// 	bool match = compareBuffers(sourceData, readData, pos);
// 	assertTrue(match);
// 	if (match) {
// 		log("Multiple cycle test: PASSED");
// 	}
// }

// void testFillBufferHeadPosition() {
// 	log("=== testFillBufferHeadPosition ===");
// 	log("Testing that head position is correctly maintained");

// 	uint8_t sourceData[LEN];
// 	for (int i = 0; i < LEN; i++) {
// 		sourceData[i] = i & 0xFF;
// 	}

// 	ByteArrayInputStream bais(sourceData, LEN);
// 	uint8_t bufferStorage[BUFFER_SIZE];
// 	BufferedInputStream bis(&bais, bufferStorage, BUFFER_SIZE);

// 	uint8_t readData[LEN];

// 	// Read exactly BUFFER_SIZE bytes
// 	int n1 = bis.read(&readData[0], BUFFER_SIZE);
// 	log("First read (buffer size):");
// 	Serial.print("  Requested: ");
// 	Serial.println(BUFFER_SIZE);
// 	Serial.print("  Read: ");
// 	Serial.println(n1);

// 	// Read more than BUFFER_SIZE bytes (should work correctly after refill)
// 	int n2 = bis.read(&readData[BUFFER_SIZE], BUFFER_SIZE + 10);
// 	log("Second read (beyond buffer size):");
// 	Serial.print("  Requested: ");
// 	Serial.println(BUFFER_SIZE + 10);
// 	Serial.print("  Read: ");
// 	Serial.println(n2);

// 	int totalRead = n1 + n2;
// 	Serial.print("Total read so far: ");
// 	Serial.println(totalRead);

// 	// Verify first chunk
// 	bool match1 = compareBuffers(&sourceData[0], &readData[0], n1);
// 	bool match2 = compareBuffers(&sourceData[BUFFER_SIZE], &readData[BUFFER_SIZE], n2);

// 	assertTrue(match1 && match2);
// 	if (match1 && match2) {
// 		log("Head position test: PASSED");
// 	}
// }

// void testFillBufferBoundaryConditions() {
// 	log("=== testFillBufferBoundaryConditions ===");
// 	log("Testing buffer boundary conditions and edge cases");

// 	uint8_t sourceData[LEN];
// 	for (int i = 0; i < LEN; i++) {
// 		sourceData[i] = i & 0xFF;
// 	}

// 	ByteArrayInputStream bais(sourceData, LEN);
// 	uint8_t bufferStorage[BUFFER_SIZE];
// 	BufferedInputStream bis(&bais, bufferStorage, BUFFER_SIZE);

// 	uint8_t readData[LEN];
// 	int totalRead = 0;

// 	// Test 1: Read up to boundary of underlying stream
// 	int n = bis.read(&readData[0], LEN - 1);
// 	totalRead = n;
// 	Serial.print("Read ");
// 	Serial.print(n);
// 	Serial.println(" bytes (up to boundary)");

// 	// Test 2: Read the last byte
// 	n = bis.read(&readData[totalRead], 1);
// 	totalRead += n;
// 	Serial.print("Read ");
// 	Serial.print(n);
// 	Serial.println(" byte (last byte)");

// 	// Test 3: Try to read beyond end
// 	n = bis.read(&readData[totalRead], 10);
// 	Serial.print("Try read beyond end: ");
// 	Serial.println(n);

// 	bool match = compareBuffers(sourceData, readData, LEN);
// 	assertTrue(match);
// 	if (match) {
// 		log("Boundary conditions test: PASSED");
// 	}
// }

// // void setup() {
// // 	Serial.begin(115200);
// // 	log("================================================");
// // 	log("BufferedInputStream fillBuffer() Bug Fix Tests");
// // 	log("================================================");

// // 	delay(1000);

// // 	testFillBufferDataIntegrity();
// // 	delay(500);

// // 	testFillBufferMultipleCycles();
// // 	delay(500);

// // 	testFillBufferHeadPosition();
// // 	delay(500);

// // 	testFillBufferBoundaryConditions();
// // 	delay(500);

// // 	log("================================================");
// // 	log("All tests completed");
// // 	log("================================================");
// // }

// // void loop() {
// // 	delay(10000);
// // }
