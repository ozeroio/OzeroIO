# BufferedInputStream::fillBuffer() Bug Test Suite

## Overview

This test suite validates the fix for the critical bug in `BufferedInputStream::fillBuffer()` identified during code review.

## The Bug

**Location:** [src/BufferedInputStream/BufferedInputStream.cpp](../src/BufferedInputStream/BufferedInputStream.cpp#L87-L92)

**Issue:** The `fillBuffer()` function has two critical problems:

1. **Wrong buffer offset:** Reads into `buf` at offset `pos` instead of `head`
2. **Lost byte count:** Sets `head = n` instead of `head += n`, losing accumulated bytes

```cpp
// BUGGY VERSION
void BufferedInputStream::fillBuffer() {
	shiftBuffer();
	const int space = size - head;
	const int n = inputStream->read(buf, pos, space);  // ❌ WRONG: 'pos' offset
	head = n;  // ❌ WRONG: overwrites head instead of accumulating
}
```

**Impact:**
- Data corruption when buffer refill is triggered
- Loss of buffered data that was shifted by `shiftBuffer()`
- Incorrect buffer state tracking leading to reads beyond buffer bounds

## The Fix

```cpp
// FIXED VERSION
void BufferedInputStream::fillBuffer() {
	shiftBuffer();
	const int space = size - head;
	const int n = inputStream->read(buf, head, space);  // ✅ CORRECT: read at 'head' offset
	head += n;  // ✅ CORRECT: accumulate bytes
}
```

## Test Cases

### 1. testFillBufferDataIntegrity()
**Purpose:** Verify that data read through the buffered stream matches the source data exactly

**Scenario:**
- Source: 128 sequential bytes (0x00, 0x01, ..., 0x7F)
- Buffer size: 16 bytes
- Test: Read data in chunks (5, 12, then remaining bytes)
- Expected: All 128 bytes read correctly without corruption

**Why it catches the bug:**
- With the bug, the second refill reads into wrong offset, corrupting previously buffered data
- The sequential source pattern makes corruption immediately visible

### 2. testFillBufferMultipleCycles()
**Purpose:** Stress test multiple buffer refill cycles

**Scenario:**
- Source: 128 sequential bytes
- Buffer size: 16 bytes
- Test: Read with varying chunk sizes (1, 3, 7, 20+ bytes) forcing multiple refills
- Expected: All data remains coherent across refills

**Why it catches the bug:**
- Each refill with wrong offset or lost byte count causes cumulative data loss
- Testing across multiple cycles amplifies the bug's effect

### 3. testFillBufferHeadPosition()
**Purpose:** Validate that the buffer head pointer is correctly maintained

**Scenario:**
- Source: 128 sequential bytes
- Buffer size: 16 bytes
- Test: 
  1. Read exactly BUFFER_SIZE bytes
  2. Read BUFFER_SIZE + 10 bytes (forces refill)
  3. Verify both chunks match source
- Expected: Head pointer correctly reflects available data

**Why it catches the bug:**
- Bug #2 (head = n instead of head += n) causes head to be underestimated
- This test verifies the head value is correct after refill

### 4. testFillBufferBoundaryConditions()
**Purpose:** Test edge cases at stream boundaries

**Scenario:**
- Source: 128 sequential bytes
- Test:
  1. Read LEN - 1 bytes
  2. Read the last byte
  3. Try to read beyond stream end
- Expected: Clean handling of all boundary conditions

**Why it catches the bug:**
- Bug's data loss effects become visible at boundaries
- Tests the interaction between stream end and buffer refill

## Running the Tests

### Option 1: Using PlatformIO (Recommended)

```bash
# ESP32
pio run -c platformio_fillbuffer_test.ini -e espressif32-fillbuffer-test -t upload -t monitor

# Arduino Uno
pio run -c platformio_fillbuffer_test.ini -e uno-fillbuffer-test -t upload -t monitor
```

### Option 2: Modify platformio.ini

Replace the `[platformio]` and `[env:*]` sections in your main `platformio.ini` with:

```ini
[platformio]
src_dir = test/BufferedInputStream
include_dir = src

# Use the test_fillBuffer_bug.cpp as main.cpp
```

Then run:
```bash
pio run -t upload -t monitor
```

### Option 3: Manual Compilation

1. Include the test file in your Arduino IDE project:
   - Copy [test_fillBuffer_bug.cpp](test_fillBuffer_bug.cpp)
   - Copy [test.cpp](../test.cpp) and [test.h](../test.h)
   - Copy all necessary source files from `src/`

2. Ensure `BUFFER_SIZE` is appropriate for your platform

3. Compile and upload

## Expected Output

### With Bug (Unfixed)

```
================================================
BufferedInputStream fillBuffer() Bug Fix Tests
================================================
=== testFillBufferDataIntegrity ===
Testing that fillBuffer correctly repositions and refills the buffer
Read 5 bytes
Read 12 bytes
Data integrity check: FAILED
Differences found:
Position 16: expected 0x10, got 0x??  # Data corruption visible here
Position 17: expected 0x11, got 0x??
...
```

### After Fix

```
================================================
BufferedInputStream fillBuffer() Bug Fix Tests
================================================
=== testFillBufferDataIntegrity ===
Testing that fillBuffer correctly repositions and refills the buffer
Read 5 bytes
Read 12 bytes
Data integrity check: PASSED
<< PASSED >>
=== testFillBufferMultipleCycles ===
Testing fillBuffer across multiple buffer refill cycles
Multiple cycle test: PASSED
<< PASSED >>
=== testFillBufferHeadPosition ===
Testing that head position is correctly maintained
First read (buffer size):
  Requested: 16
  Read: 16
Second read (beyond buffer size):
  Requested: 26
  Read: 26
Total read so far: 42
Head position test: PASSED
<< PASSED >>
=== testFillBufferBoundaryConditions ===
Testing buffer boundary conditions and edge cases
Read 127 bytes (up to boundary)
Read 1 byte (last byte)
Try read beyond end: -1
Boundary conditions test: PASSED
<< PASSED >>
================================================
All tests completed
================================================
```

## Test Configuration

| Parameter | Value | Notes |
|-----------|-------|-------|
| Source buffer size (LEN) | 128 bytes | Enough to test multiple refills |
| Buffer size (BUFFER_SIZE) | 16 bytes | Small enough to force refills, large enough to be realistic |
| Test coverage | 4 test cases | Data integrity, cycles, head tracking, boundaries |

## How to Apply the Fix

Edit [src/BufferedInputStream/BufferedInputStream.cpp](../src/BufferedInputStream/BufferedInputStream.cpp) at lines 87-92:

```diff
  void BufferedInputStream::fillBuffer() {
  	shiftBuffer();
  	const int space = size - head;
- 	const int n = inputStream->read(buf, pos, space);
- 	head = n;
+ 	const int n = inputStream->read(buf, head, space);
+ 	head += n;
  }
```

## Verification Checklist

- [ ] Apply the fix to BufferedInputStream.cpp
- [ ] Run the test suite on your target platform (ESP32, Uno, etc.)
- [ ] All 4 tests should PASS
- [ ] No data corruption errors in output
- [ ] Existing BufferedInputStream tests still pass (from main.cpp)

## Additional Notes

- The test uses `compareBuffers()` utility from [test.cpp](../test.cpp) which provides detailed mismatch reporting
- Buffer size (16 bytes) was chosen to force multiple refills within reasonable memory constraints
- Test data is sequential (0x00, 0x01, ...) to make corruption immediately visible
- The bug severity justifies multiple test cases covering different access patterns

## Related Issues

See [CODE_REVIEW.md](../CODE_REVIEW.md) for:
- Issue #1: BufferedInputStream::fillBuffer() detailed analysis
- Issue #2: BufferedInputStream::mark() related bug
- Complete list of all identified bugs and improvements
