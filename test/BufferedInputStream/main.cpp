#include <Arduino.h>
#include <BufferedInputStream/BufferedInputStream.cpp>
#include <ByteArrayInputStream/ByteArrayInputStream.cpp>
#include <FilterInputStream/FilterInputStream.cpp>
#include <InputStream/InputStream.cpp>

#include "../test.cpp"

#ifdef ARDUINO_ARCH_ESP32
#include <freertos/FreeRTOS.h>
#define LEN 1000
#else
#define LEN 128
#endif

#define BUFFER_SIZE 32


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
// 	for (int i = 0; i < LEN; i++) {
// 		readData[i] = 0x0;
// 	}
// 	int totalRead = 0;

// 	// First, read 5 bytes (partially fills buffer from underlying stream)
// 	int n1 = bis.read(&readData[0], 5);
// 	totalRead += n1;

// 	logBuffer(sourceData, 0, LEN);
// 	logBuffer(bufferStorage, 0, BUFFER_SIZE);
// 	logBuffer(readData, 0, LEN);
// 	Serial.println(bis.head);
// 	Serial.println(bis.pos);
// 	bis.fillBuffer();
// 	logBuffer(sourceData, 0, LEN);
// 	logBuffer(bufferStorage, 0, BUFFER_SIZE);
// 	logBuffer(readData, 0, LEN);
// 	Serial.println(bis.head);
// 	Serial.println(bis.pos);


// 	if (n1 != 5) {
// 		log("Error: Expected to read 5 bytes");
// 		assertTrue(false);
// 		return;
// 	}
// 	log("Read 5 bytes");

// 	// Then read 12 bytes (should trigger shiftBuffer and fillBuffer)
// 	int n2 = bis.read(&readData[5], 12);
// 	totalRead += n2;
// 	if (n2 != 12) {
// 		log("Error: Expected to read 12 bytes");
// 		assertTrue(false);
// 		return;
// 	}
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


/**
 * Test that fillBuffer() correctly preserves unread data during buffer refill.
 *
 * BUG: Old code reads at `pos` (overwriting shifted data) and uses `head = n` (losing previous data).
 * This test specifically checks that partially-read data survives a buffer refill.
 */
/**
 * CRITICAL TEST: This MUST fail with buggy code.
 * BUG: fillBuffer() uses `head = n` instead of `head += n`
 * This causes unread buffered data to be lost when refilling.
 */
void testFillBufferPreservesPartialData() {
	log("=== testFillBufferPreservesPartialData ===");
	log("CRITICAL: Testing unread data survival during refill");

	// 50-byte source with distinct sequential bytes
	uint8_t sourceData[50];
	for (int i = 0; i < 50; i++) {
		sourceData[i] = i;
	}

	ByteArrayInputStream bais(sourceData, 50);
	uint8_t bufferStorage[8];// TINY buffer (8 bytes)
	BufferedInputStream bis(&bais, bufferStorage, 8);

	uint8_t readData[50];
	memset(readData, 0xFF, 50);

	// === CRITICAL SEQUENCE ===
	// Step 1: Read 5 bytes
	// Buffer fills with [0-7], we read 0-4, leaves [5,6,7] unread (pos=5, head=8)
	int n1 = bis.read(&readData[0], 5);
	logPair("Step 1 - Read ", n1);
	if (n1 != 5) {
		logPair("FAILED step 1: expected 5, got ", n1);
		return;
	}

	// Causes the buffer to be shifted and wrongly refilled
	bis.mark();

	// Step 2: Read 10 bytes
	// This triggers: shiftBuffer() moves [5,6,7] to [0,1,2]
	// Then fillBuffer() reads bytes 8-14 into buffer[3-9]
	// BUGGY CODE: head = n (=7) loses the fact that we had 3 bytes already!
	// Result: available becomes only 7 instead of 10
	// CORRECT CODE: head += n (head = 3 + 7 = 10)
	// Result: available correctly becomes 10

	int n2 = bis.read(&readData[5], 10);
	logPair("Step 2 - Read ", n2);
	if (n2 != 10) {
		logPair("CRITICAL FAIL: Expected 10, got ", n2);
		log(">>> BUG CONFIRMED: fillBuffer() overwrites head instead of accumulating!");
		return;
	}

	// Verify continuity: bytes 0-14 must be 0-14
	bool allGood = true;
	for (int i = 0; i < 15; i++) {
		if (readData[i] != i) {
			logPair("Mismatch at ", i);
			logPair("  Expected: 0x", (uint8_t) i);
			logPair("  Got: 0x", readData[i]);
			allGood = false;
			break;
		}
	}

	if (allGood) {
		log("PASSED: fillBuffer correctly accumulates head");
	} else {
		log("FAILED: Data corruption - likely head was overwritten");
	}
}

/**
 * Test that mark() correctly saves the current read position, not position 0.
 *
 * BUG: Old code uses `markPos = 0` instead of `markPos = pos`.
 * This test marks at a specific position and verifies reset goes to that position.
 */
void testMarkSavesCurrentPosition() {
	log("=== testMarkSavesCurrentPosition ===");
	log("Testing that mark() saves current position, not always 0");

	// Create source with distinct byte patterns
	uint8_t sourceData[256];
	for (int i = 0; i < 256; i++) {
		sourceData[i] = (i ^ 0xAA) & 0xFF;// Distinctive pattern
	}

	ByteArrayInputStream bais(sourceData, 256);
	uint8_t bufferStorage[32];
	BufferedInputStream bis(&bais, bufferStorage, 32);

	uint8_t readData1[256];
	uint8_t readData2[256];
	memset(readData1, 0xFF, 256);
	memset(readData2, 0xFF, 256);

	// Read 20 bytes
	int n1 = bis.read(&readData1[0], 20);
	if (n1 != 20) {
		logPair("FAILED: Expected first read of 20, got ", n1);
		return;
	}
	log("Read 20 bytes");

	// Mark at position 20
	bis.mark();
	logPair("Marked at position: ", 20);

	// Read 15 more bytes (now at position 35)
	int n2 = bis.read(&readData1[20], 15);
	if (n2 != 15) {
		logPair("FAILED: Expected second read of 15, got ", n2);
		return;
	}
	log("Read 15 more bytes (at position 35)");

	// Reset should go back to position 20
	bis.reset();
	log("Reset called - should go to position 20");

	// Read 15 bytes again from the marked position
	// With the bug: we'd read from position 0 instead
	// With the fix: we read from position 20 and get the same data
	int n3 = bis.read(&readData2[0], 15);
	if (n3 != 15) {
		logPair("FAILED: Expected read after reset of 15, got ", n3);
		return;
	}

	// Verify we got the same data as positions 20-34
	bool match = true;
	for (int i = 0; i < 15; i++) {
		if (readData1[20 + i] != readData2[i]) {
			logPair("Mismatch at position ", i);
			logPair("  Expected (from original[20+i]): 0x", readData1[20 + i]);
			logPair("  Got: 0x", readData2[i]);
			match = false;
			break;
		}
	}

	if (match) {
		log("PASSED: Mark correctly saved the position");
	} else {
		log("FAILED: Reset went to wrong position (likely 0 instead of 20)");
	}
}

/**
 * Test buffer refill with very small reads followed by large read.
 * This stresses the head accumulation logic.
 */
void testBufferRefillHeadAccumulation() {
	log("=== testBufferRefillHeadAccumulation ===");
	log("Testing head accumulation across multiple small reads");

	uint8_t sourceData[256];
	for (int i = 0; i < 256; i++) {
		sourceData[i] = i;
	}

	ByteArrayInputStream bais(sourceData, 256);
	uint8_t bufferStorage[32];
	BufferedInputStream bis(&bais, bufferStorage, 32);

	uint8_t readData[256];
	memset(readData, 0xFF, 256);

	int totalRead = 0;

	// Series of small reads
	for (int i = 0; i < 5; i++) {
		int n = bis.read(&readData[totalRead], 3);
		if (n <= 0) {
			logPair("FAILED: Read attempt ", i);
			return;
		}
		totalRead += n;
	}
	logPair("Read 5 x 3 bytes: ", totalRead);

	// Medium read (will trigger refill)
	int n = bis.read(&readData[totalRead], 16);
	if (n <= 0) {
		log("FAILED: Medium read failed");
		return;
	}
	totalRead += n;
	logPair("Read 16 bytes: ", totalRead);

	// Large read (bigger than buffer)
	n = bis.read(&readData[totalRead], 50);
	if (n <= 0) {
		log("FAILED: Large read failed");
		return;
	}
	totalRead += n;
	logPair("Total read: ", totalRead);

	// Verify continuous sequence
	bool dataOk = true;
	for (int i = 0; i < totalRead; i++) {
		if (readData[i] != (i & 0xFF)) {
			logPair("Data mismatch at ", i);
			logPair("  Expected: 0x", (uint8_t) (i & 0xFF));
			logPair("  Got: 0x", readData[i]);
			dataOk = false;
			break;
		}
	}

	if (dataOk) {
		log("PASSED: Head accumulation works across reads");
	} else {
		log("FAILED: Data corruption in head accumulation");
	}
}

void setup() {
	// Serial.begin(115200);
	// log("Initializing...");

	// auto *streamBuffer = new uint8_t[LEN];
	// auto *destinationBuffer = new uint8_t[LEN];
	// auto *buffer = new uint8_t[BUFFER_SIZE];

	// ByteArrayInputStream is(streamBuffer, LEN);
	// BufferedInputStream bis(&is, buffer, BUFFER_SIZE);

	// is.reset();
	// testInputStreamComparingBuffers(&bis, streamBuffer, destinationBuffer, LEN, testWhenReadingFully);
	// is.reset();
	// testInputStreamComparingBuffers(&bis, streamBuffer, destinationBuffer, LEN, testWhenReadingParts);
	// is.reset();
	// testNullPointerOrLen0(&bis, streamBuffer, destinationBuffer, LEN);
	// is.reset();
	// testReadBeyondLimit(&bis, streamBuffer, destinationBuffer, LEN);
	// is.reset();
	// testAvailable(&bis, streamBuffer, destinationBuffer, LEN);

	// free(destinationBuffer);
	// free(streamBuffer);

	Serial.begin(115200);
	log("================================================");
	log("BufferedInputStream fillBuffer() Bug Fix Tests");
	log("================================================");

	delay(1000);

	testFillBufferPreservesPartialData();
	delay(500);

	// testMarkSavesCurrentPosition();
	// delay(500);

	// testBufferRefillHeadAccumulation();
	// delay(500);

	log("================================================");
	log("All tests completed");
	log("================================================");
}

void loop() {

#ifdef ARDUINO_ARCH_ESP32
	logPair("Free heap: ", xPortGetFreeHeapSize());
#endif
	delay(10000);
}