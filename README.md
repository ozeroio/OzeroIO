# OzeroIO Library

A comprehensive C++ input/output stream library for Arduino and embedded systems, providing abstract interfaces and implementations for reading and writing data across various sources including memory, EEPROM, serial ports, and external devices.

## Overview

OzeroIO is a port-agnostic, modular I/O library that brings Java-like stream abstractions to embedded C++ development. It provides a consistent, composable interface for data I/O operations, similar to Java's `java.io` package. This library is particularly useful for projects that require:

- Reading and writing data from multiple sources (RAM, EEPROM, Serial, External EEPROM)
- Buffering and filtering data streams
- Seeking and random access to data
- Consistent abstractions across different I/O implementations
- Type-safe serialization/deserialization of primitive types

## Key Features

### 🔌 Multiple I/O Sources
- **Memory Streams**: ByteArrayInputStream, ByteArrayOutputStream
- **Serial I/O**: HardwareSerialInputStream/OutputStream, SoftwareSerialInputStream/OutputStream
- **EEPROM Access**: Internal and external EEPROM streams with seeking support
- **Filtered Streams**: Buffered input/output streams for performance optimization

### 🛠️ Core Abstractions
- **InputStream**: Base interface for all input operations
- **OutputStream**: Base interface for all output operations
- **DataInput/DataOutput**: Type-aware reading/writing of primitive types (int, float, double, etc.)
- **Seekable**: Random access positioning support
- **Closeable**: Resource management interface

### ⚡ Performance Features
- **BufferedInputStream**: Efficient buffered reading with mark/reset support
- **BufferedOutputStream**: Efficient buffered writing with async flushing option
- **AsyncBufferedOutputStream**: Non-blocking asynchronous buffer flushing with ring buffer pooling (FreeRTOS)

### 🔄 Flexible Composition
- **FilterInputStream/FilterOutputStream**: Chainable stream decorators
- **DataInputStream/DataOutputStream**: Type conversion layers
- **RandomAccess**: Combined read/write/seek interface

## Installation

### PlatformIO
Add to your `platformio.ini`:
```ini
lib_deps = 
    github.com/ozeroio/OzeroIO#^3.2.0
```

### Manual
Clone or download and add to your project's library folder:
```bash
git clone https://github.com/ozeroio/OzeroIO.git
```

## Quick Start

### Basic Reading from a Buffer

```cpp
#include <ByteArrayInputStream/ByteArrayInputStream.h>
#include <DataInputStream/DataInputStream.h>

unsigned char buffer[] = {0x00, 0x01, 0x02, 0x03};
ByteArrayInputStream bais(buffer, 4);
DataInputStream dis(&bais);

int value = dis.readInt();  // Read a 32-bit integer
```

### Basic Writing to a Buffer

```cpp
#include <ByteArrayOutputStream/ByteArrayOutputStream.h>
#include <DataOutputStream/DataOutputStream.h>

unsigned char buffer[256];
ByteArrayOutputStream baos(buffer, 256);
DataOutputStream dos(&baos);

dos.writeInt(42);           // Write a 32-bit integer
dos.writeFloat(3.14f);      // Write a float
dos.writeBoolean(true);     // Write a boolean
```

### Buffered Serial Reading

```cpp
#include <HardwareSerialInputStream/HardwareSerialInputStream.h>
#include <BufferedInputStream/BufferedInputStream.h>

unsigned char buffer[128];
HardwareSerialInputStream hsir(&Serial);
BufferedInputStream bis(&hsir, buffer, 128);

int byte = bis.read();      // Read with buffering
bis.mark();                 // Mark current position
bis.reset();                // Reset to marked position
```

### Random Access EEPROM

```cpp
#include <RandomAccessInternalEeprom/RandomAccessInternalEeprom.h>

RandomAccessInternalEeprom rae(0, 1024);
rae.seek(100);              // Seek to position 100
rae.write(0xFF);            // Write a byte
rae.seek(100);              // Seek back
int val = rae.read();       // Read the byte
```

## Architecture

### Class Hierarchy

```
Closeable
├── InputStream
│   ├── FilterInputStream
│   │   ├── BufferedInputStream
│   │   └── DataInputStream
│   ├── ByteArrayInputStream
│   ├── SeekableInputStream
│   │   └── ByteArrayInputStream
│   └── Serial*/EEPROM* Streams
│
└── OutputStream
    ├── FilterOutputStream
    │   ├── BufferedOutputStream
    │   │   └── AsyncBufferedOutputStream
    │   └── DataOutputStream
    ├── ByteArrayOutputStream
    ├── SeekableOutputStream
    │   └── ByteArrayOutputStream
    └── Serial*/EEPROM* Streams

DataInput (interface)
├── DataInputStream
├── DataInputStream (via InputStreams)
└── RandomAccess*

DataOutput (interface)
├── DataOutputStream
├── DataOutputStream (via OutputStreams)
└── RandomAccess*

Seekable (interface)
├── SeekableInputStream
├── SeekableOutputStream
└── RandomAccess*

RandomAccess (interface - combines all above)
├── RandomAccessByteArray
├── RandomAccessInternalEeprom
└── RandomAccessExternalEeprom
```

## Core Components

### Input Streams

| Class | Purpose | Features |
|-------|---------|----------|
| **InputStream** | Abstract base for all input | available(), mark(), reset(), skip() |
| **FilterInputStream** | Decorator for input streams | Chains to other streams |
| **BufferedInputStream** | Buffered reading | Mark/reset within buffer, reduces I/O |
| **DataInputStream** | Typed data reading | Reads primitives: int, float, double, etc. |
| **ByteArrayInputStream** | In-memory reading | Seeks within byte array |
| **HardwareSerialInputStream** | Serial port reading | Hardware UART interface |
| **SoftwareSerialInputStream** | Software serial reading | Software-emulated serial |
| **ExternalEepromInputStream** | External EEPROM reading | With seeking support |
| **InternalEepromInputStream** | Internal EEPROM reading | With seeking support |

### Output Streams

| Class | Purpose | Features |
|-------|---------|----------|
| **OutputStream** | Abstract base for all output | flush(), mark(), reset() |
| **FilterOutputStream** | Decorator for output streams | Chains to other streams |
| **BufferedOutputStream** | Buffered writing | Reduces I/O operations |
| **AsyncBufferedOutputStream** | Async buffered writing with ring buffer pooling | FreeRTOS task-based flushing, metadata-only queuing, minimal memory overhead |
| **DataOutputStream** | Typed data writing | Writes primitives: int, float, double, etc. |
| **ByteArrayOutputStream** | In-memory writing | Seeks within byte array |
| **HardwareSerialOutputStream** | Serial port writing | Hardware UART interface |
| **SoftwareSerialOutputStream** | Software serial writing | Software-emulated serial |
| **ExternalEepromOutputStream** | External EEPROM writing | With seeking support |
| **InternalEepromOutputStream** | Internal EEPROM writing | With seeking support |

### Data Interfaces

| Interface | Purpose | Methods |
|-----------|---------|---------|
| **DataInput** | Type-aware reading | read(), readInt(), readFloat(), readDouble(), etc. |
| **DataOutput** | Type-aware writing | write(), writeInt(), writeFloat(), writeDouble(), etc. |
| **Seekable** | Position control | seek(pos) |
| **Closeable** | Resource cleanup | close() |
| **RandomAccess** | Combined interface | Reads, writes, seeks, closes |

## Supported Data Types

Both DataInput and DataOutput support the following primitive types:

- **Integers**: byte, short, int, long (signed and unsigned variants)
- **Floating Point**: float, double
- **Boolean**: bool
- **Character**: char
- **Byte**: unsigned char (byte)

## Memory Management

### Stack vs. Heap

The library is designed for embedded systems with limited memory:

- **Stack-allocated streams**: Most streams can be instantiated on the stack
- **Buffer management**: Buffers are passed to streams (not allocated internally)
- **No dynamic allocation**: Most implementations avoid `new`/`delete`

### Example: Proper Buffer Management

```cpp
// DON'T - buffer goes out of scope
ByteArrayInputStream* createStream() {
    unsigned char buffer[32];  // Will be invalid after return
    return new ByteArrayInputStream(buffer, 32);
}

// DO - manage buffer lifetime
unsigned char buffer[32];
ByteArrayInputStream stream(buffer, 32);
// Use stream while buffer is in scope
```

## Build Configuration

Enable/disable features via macros in your project:

```cpp
// Enable/disable optional features
#define OZERO_IO_HARDWARE_SERIAL_SUPPORT_ENABLED 1
#define OZERO_IO_SOFTWARE_SERIAL_SUPPORT_ENABLED 1
#define OZERO_IO_EXTERNAL_EEPROM_SUPPORT_ENABLED 1
#define OZERO_IO_INTERNAL_EEPROM_SUPPORT_ENABLED 1
#define OZERO_IO_ASYNC_STREAM_ENABLED 1  // Requires FreeRTOS
```

## Advanced Usage

### Chaining Streams

```cpp
#include <DataInputStream/DataInputStream.h>
#include <BufferedInputStream/BufferedInputStream.h>
#include <HardwareSerialInputStream/HardwareSerialInputStream.h>

unsigned char buffer[256];
HardwareSerialInputStream serial(&Serial);
BufferedInputStream buffered(&serial, buffer, 256);
DataInputStream data(&buffered);

// Read typed data from buffered serial input
int myInt = data.readInt();
float myFloat = data.readFloat();
```

### Async Output with FreeRTOS

```cpp
#include <AsyncBufferedOutputStream/AsyncBufferedOutputStream.h>

unsigned char buffer[1024];
HardwareSerialOutputStream serial(&Serial);

// Creates ring buffer pool with 2 buffers for async flushing
AsyncBufferedOutputStream async(&serial, buffer, 1024);

// Writes are buffered and flushed asynchronously in a FreeRTOS task
async.write((unsigned char*)"Hello", 5);
// Returns immediately without blocking

// Flush and wait for all pending operations to complete
async.flush();  // Blocks until all queued writes finish
```

**Key Features:**
- **Ring Buffer Pooling**: Uses N buffers (default 2) to enable concurrent async operations
- **Metadata-Only Queuing**: Only 8-byte metadata items queued, not full buffers (87% memory reduction)
- **Counting Semaphore**: Allows up to N concurrent pending flushes
- **Proper Synchronization**: Semaphore given back before writing to allow pending writes during slow stream operations
- **Explicit Flush Control**: `flush()` method waits for all pending async operations to complete

### Random Access with Seeking

```cpp
#include <RandomAccessByteArray/RandomAccessByteArray.h>

unsigned char data[256];
RandomAccessByteArray rab(data, 256);

rab.seek(50);
rab.write(0xFF);
rab.seek(50);
int value = rab.read();  // Should be 0xFF
```

## Documentation

Comprehensive inline documentation is provided for all classes and methods:

- **Method Documentation**: Every method includes `@param` and `@return` tags
- **Class Overview**: Each class has detailed overview comments
- **Usage Examples**: Many classes include example code in comments

### API Reference

See individual class headers in `src/` directory for complete API documentation.

## Requirements

- **C++11** or later
- **Arduino framework** compatible microcontroller
- **Arduino IDE** 1.8.0+ or **PlatformIO**

### Optional Dependencies

- **FreeRTOS**: Required for AsyncBufferedOutputStream
- **External EEPROM library**: For external EEPROM streams

## Testing

The library includes comprehensive unit tests for all components:

```bash
# Run tests with PlatformIO
pio test
```

Test files are located in the `test/` directory, organized by component.

## License

This project is licensed under the GNU Lesser General Public License v3 (LGPL-3.0).
See the LICENSE file for full details.

## Contributing

Contributions are welcome! Please ensure:

1. All public methods are fully documented
2. Code follows the existing style and conventions
3. Tests are included for new functionality
4. Documentation is updated

## Author

**OzeroIO** was created by **Dalmir da Silva** <dalmirdasilva@gmail.com>

## Changelog

### Version 3.2.0
- Complete documentation unification across all methods
- Enhanced parameter and return value documentation
- Improved class overview documentation

### Earlier Versions
See git history for complete changelog.

## Release Notes

### v3.4.0 - January 31, 2026

#### New Features
- **CyclicRedundancyChecksum**:
  - Added a new class for CRC16 checksum calculation.
  - Provides methods to update, reset, and retrieve the checksum value.

#### Enhancements
- **RandomAccessExternalEeprom**:
  - Improved handling of offsets for read and write operations.
  - Enhanced code comments for clarity.
- **BufferedInputStream**:
  - Added validation for negative skip values.
  - Improved code comments for better readability.
- **ByteArrayInputStream**:
  - Ensured position validation within the valid range.
  - Enhanced code comments for clarity.
- **RandomAccessByteArray**:
  - Added support for seeking within the valid range, including EOF.
  - Improved code comments for better readability.

---

## Support & Feedback

For issues, feature requests, or questions:
- **GitHub Issues**: [ozeroio/OzeroIO](https://github.com/ozeroio/OzeroIO/issues)
- **Email**: dalmirdasilva@gmail.com

## Related Projects

- [EEPROM](https://github.com/arduino/Arduino/tree/master/libraries/EEPROM) - Arduino EEPROM library
- [SoftwareSerial](https://github.com/arduino/Arduino/tree/master/libraries/SoftwareSerial) - Software serial emulation
- [FreeRTOS](https://www.freertos.org/) - Real-time operating system for embedded systems

