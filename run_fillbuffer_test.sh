#!/bin/bash
# Test execution script for BufferedInputStream fillBuffer() bug validation
# This script automates building and running the test suite

set -e

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PROJECT_ROOT="$SCRIPT_DIR"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Default values
PLATFORM="espressif32"
BOARD="esp32doit-devkit-v1"
UPLOAD_PORT="/dev/ttyUSB0"
MONITOR_PORT="/dev/ttyUSB0"
TEST_CONFIG="platformio_fillbuffer_test.ini"

# Function to print colored output
print_header() {
    echo -e "${GREEN}================================================${NC}"
    echo -e "${GREEN}$1${NC}"
    echo -e "${GREEN}================================================${NC}"
}

print_info() {
    echo -e "${YELLOW}[INFO]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

# Function to display usage
usage() {
    cat << EOF
Usage: $0 [OPTIONS]

Runs the BufferedInputStream fillBuffer() bug test suite

OPTIONS:
    -p, --platform PLATFORM    Target platform (espressif32 or uno)
                               Default: espressif32
    -u, --upload PORT          Upload port
                               Default: /dev/ttyUSB0 (espressif32) or /dev/ttyACM0 (uno)
    -m, --monitor PORT         Monitor port
                               Default: same as upload port
    --no-upload                Build only, don't upload
    --no-monitor               Upload but don't monitor
    -h, --help                Display this help message

EXAMPLES:
    # Test on ESP32 with default ports
    $0

    # Test on Arduino Uno with custom upload port
    $0 --platform uno --upload /dev/ttyACM0

    # Build only (no upload/monitor)
    $0 --no-upload

EOF
    exit 1
}

# Parse command line arguments
NO_UPLOAD=false
NO_MONITOR=false

while [[ $# -gt 0 ]]; do
    case $1 in
        -p|--platform)
            PLATFORM="$2"
            shift 2
            ;;
        -u|--upload)
            UPLOAD_PORT="$2"
            shift 2
            ;;
        -m|--monitor)
            MONITOR_PORT="$2"
            shift 2
            ;;
        --no-upload)
            NO_UPLOAD=true
            shift
            ;;
        --no-monitor)
            NO_MONITOR=true
            shift
            ;;
        -h|--help)
            usage
            ;;
        *)
            print_error "Unknown option: $1"
            usage
            ;;
    esac
done

# Set default monitor port if not specified
if [ "$UPLOAD_PORT" != "/dev/ttyUSB0" ] && [ "$UPLOAD_PORT" != "/dev/ttyACM0" ]; then
    MONITOR_PORT="$UPLOAD_PORT"
fi

# Validate platform
case $PLATFORM in
    espressif32)
        ENV_NAME="espressif32-fillbuffer-test"
        if [ "$UPLOAD_PORT" = "/dev/ttyUSB0" ]; then
            UPLOAD_PORT="/dev/ttyUSB0"
        fi
        ;;
    uno)
        ENV_NAME="uno-fillbuffer-test"
        if [ "$UPLOAD_PORT" = "/dev/ttyUSB0" ]; then
            UPLOAD_PORT="/dev/ttyACM0"
        fi
        ;;
    *)
        print_error "Invalid platform: $PLATFORM"
        echo "Valid options: espressif32, uno"
        exit 1
        ;;
esac

# Main execution
print_header "BufferedInputStream fillBuffer() Bug Test Suite"

print_info "Platform: $PLATFORM"
print_info "Environment: $ENV_NAME"
print_info "Upload Port: $UPLOAD_PORT"
print_info "Monitor Port: $MONITOR_PORT"
print_info "Test Config: $TEST_CONFIG"

# Check if test config exists
if [ ! -f "$PROJECT_ROOT/$TEST_CONFIG" ]; then
    print_error "Test configuration file not found: $TEST_CONFIG"
    exit 1
fi

# Check if PlatformIO is installed
if ! command -v pio &> /dev/null; then
    print_error "PlatformIO CLI not found. Please install it:"
    echo "  pip install platformio"
    exit 1
fi

print_header "Step 1: Building Test Suite"

# Build the test
if pio run -c "$TEST_CONFIG" -e "$ENV_NAME"; then
    print_success "Build completed successfully"
else
    print_error "Build failed"
    exit 1
fi

# Upload if requested
if [ "$NO_UPLOAD" = false ]; then
    print_header "Step 2: Uploading Firmware"
    
    # Check if port is accessible
    if [ ! -e "$UPLOAD_PORT" ]; then
        print_error "Upload port not found: $UPLOAD_PORT"
        echo "Available serial ports:"
        ls /dev/tty* 2>/dev/null | grep -E "USB|ACM" || echo "  None found"
        exit 1
    fi
    
    if pio run -c "$TEST_CONFIG" -e "$ENV_NAME" -t upload --upload-port "$UPLOAD_PORT"; then
        print_success "Firmware uploaded successfully"
    else
        print_error "Upload failed"
        exit 1
    fi
    
    # Monitor if requested
    if [ "$NO_MONITOR" = false ]; then
        print_header "Step 3: Monitoring Test Output"
        
        echo ""
        print_info "Waiting 2 seconds for device to restart..."
        sleep 2
        
        print_info "Starting serial monitor (Ctrl+C to exit)..."
        echo "Port: $MONITOR_PORT"
        echo ""
        
        # Monitor the output
        pio device monitor --port "$MONITOR_PORT" --baud 115200
        
        # Check output for test results
        print_header "Test Execution Complete"
        print_success "Check the serial monitor output above for test results"
        print_info "Expected output:"
        echo "  - All 4 tests should show '<< PASSED >>'"
        echo "  - No 'FAILED' messages"
        echo "  - Total summary at the end"
    fi
else
    print_success "Build completed. Firmware ready to upload manually."
    print_info "To upload manually, run:"
    echo "  pio run -c $TEST_CONFIG -e $ENV_NAME -t upload --upload-port $UPLOAD_PORT"
fi

print_header "Done!"
