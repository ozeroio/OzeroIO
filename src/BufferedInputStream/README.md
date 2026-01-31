# BufferedInputStream

## Overview

`BufferedInputStream` is a filtering input stream that adds buffering functionality to another input stream. It improves performance by reading data in chunks from the underlying stream and buffering them internally, rather than reading one byte at a time. It also provides support for the `mark()` and `reset()` methods to allow repositioning within the buffered data.

This implementation is similar to Java's `BufferedInputStream` class and is particularly useful in embedded systems where minimizing I/O operations is critical for performance.

## Class Hierarchy

```
InputStream
    ↑
    |
FilterInputStream
    ↑
    |
BufferedInputStream
```

## Constructor
[text](.)
### `BufferedInputStream(InputStream *inputStream, unsigned char *buf, int size)`

Creates a new buffered input stream that filters the specified input stream with a provided buffer.

**Parameters:**
- `inputStream`: The underlying input stream to buffer (pointer to `InputStream` object)
- `buf`: External buffer array for storing buffered data (pointer to `unsigned char`)
- `size`: The size of the buffer in bytes

**Example:**
```cpp
InputStream *baseStream = ...;  // Your underlying stream
unsigned char buffer[1024];      // 1KB buffer
BufferedInputStream bis(baseStream, buffer, sizeof(buffer));
```

## Public Methods

### `int available()`

Returns the number of bytes that can be read from this input stream without blocking.

**Returns:** Number of available bytes, or `INT_MAX` if overflow would occur.

**Example:**
```cpp
int bytesAvailable = bis.available();
if (bytesAvailable > 0) {
    // Data is ready to read
}
```

### `void close()`

Closes this input stream and releases system resources by closing the underlying stream.

**Example:**
```cpp
bis.close();
```

### `int read()`

Reads the next byte of data from the input stream.

**Returns:** The next byte as an integer (0-255), or `-1` if end of stream is reached.

**Example:**
```cpp
int byte = bis.read();
if (byte != -1) {
    unsigned char data = (unsigned char)byte;
    // Process data
}
```

### `int read(unsigned char *b, int len)`

Reads up to `len` bytes from the input stream into the buffer array.

**Parameters:**
- `b`: Destination buffer array
- `len`: Maximum number of bytes to read

**Returns:** Number of bytes actually read, or `-1` if end of stream is reached immediately.

**Example:**
```cpp
unsigned char data[256];
int bytesRead = bis.read(data, sizeof(data));
if (bytesRead > 0) {
    // Process bytesRead bytes from data array
}
```

### `int read(unsigned char *b, int off, int len)`

Reads up to `len` bytes from the input stream into the buffer array at offset `off`.

**Parameters:**
- `b`: Destination buffer array
- `off`: Offset in the destination buffer where data starts
- `len`: Maximum number of bytes to read

**Returns:** Number of bytes actually read, or `-1` if end of stream is reached immediately.

**Example:**
```cpp
unsigned char data[512];
int bytesRead = bis.read(data, 256, 100);  // Read 100 bytes starting at offset 256
```

### `void mark()`

Marks the current position in this input stream.

A subsequent call to `reset()` will reposition the stream to this marked point. The mark is only valid within the current buffer.

**Example:**
```cpp
bis.mark();
// Read some data
unsigned char byte1 = bis.read();
unsigned char byte2 = bis.read();
// Reset to marked position
bis.reset();  // Can now re-read byte1 and byte2
```

### `bool markSupported()`

Tests if this input stream supports the `mark()` and `reset()` methods.

**Returns:** Always `true` for `BufferedInputStream`.

**Example:**
```cpp
if (bis.markSupported()) {
    bis.mark();
}
```

### `void reset()`

Repositions this stream to the position at the time the `mark()` method was last called.

The mark is only supported within the current buffer. If the buffer has been shifted (due to internal operations), the mark may be invalidated.

**Example:**
```cpp
bis.mark();
// Read data...
bis.reset();  // Return to marked position
```

### `int skip(int n)`

Skips over and discards `n` bytes of data from this input stream.

**Parameters:**
- `n`: Number of bytes to skip

**Returns:** Number of bytes actually skipped.

**Example:**
```cpp
int skipped = bis.skip(100);  // Skip 100 bytes
```

## Usage Example

```cpp
#include <BufferedInputStream/BufferedInputStream.h>
#include <SerialInputStream/SerialInputStream.h>

// Create underlying serial input stream
SerialInputStream sis(&Serial);

// Create buffer and buffered stream
unsigned char buffer[512];
BufferedInputStream bis(&sis, buffer, sizeof(buffer));

void setup() {
    Serial.begin(9600);
}

void loop() {
    // Check if data is available
    if (bis.available() > 0) {
        // Read a single byte
        int byte = bis.read();
        if (byte != -1) {
            Serial.print("Read byte: ");
            Serial.println((unsigned char)byte);
        }
    }
    
    // Or read multiple bytes
    unsigned char data[64];
    int bytesRead = bis.read(data, sizeof(data));
    if (bytesRead > 0) {
        // Process data...
        for (int i = 0; i < bytesRead; i++) {
            Serial.print(data[i]);
            Serial.print(" ");
        }
        Serial.println();
    }
}
```

## Performance Considerations

1. **Buffer Size**: Choose an appropriate buffer size based on your application needs:
   - Larger buffers reduce I/O operations but use more memory
   - Typical sizes: 256 bytes to 4KB for embedded systems

2. **External Buffer**: The buffer is provided externally, allowing you to manage memory and reuse buffers across multiple streams.

3. **Single Pass Reading**: The buffer is shifted on demand, moving unread data to the beginning and discarding read data.

## Known Issues

⚠️ **Critical Bugs Identified:**

1. **Overflow vulnerability in `available()`**: When `underliningAvailable` is negative, the overflow check `INT_MAX - underliningAvailable` can itself overflow.

2. **Buffer overflow in `readWithBuffer()`**: The `memcpy` call has no bounds checking on the destination buffer `b`. If `off` is negative or larger than the buffer size, this causes undefined behavior and potential memory corruption.

3. **Parameter validation**: The `readWithBuffer` method doesn't validate input parameters (`off`, `len`) for negative or out-of-bounds values.

These issues should be addressed before using this class in production systems.

## See Also

- [InputStream](../InputStream/) - Base input stream interface
- [FilterInputStream](../FilterInputStream/) - Filter stream base class
- [SerialInputStream](../SerialInputStream/) - Serial port input stream
- [ByteArrayInputStream](../ByteArrayInputStream/) - In-memory input stream
