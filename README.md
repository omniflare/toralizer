# SOCKS4 Proxy Client Implementation

A lightweight SOCKS4 proxy client implementation in C that allows for proxied network connections through a SOCKS4 server. This implementation follows the SOCKS4 protocol specification and demonstrates fundamental networking concepts.

## Overview

This project implements a SOCKS4 proxy client that:
- Establishes connections through a SOCKS4 proxy server
- Handles protocol-specific request and response formats
- Supports basic HTTP requests through the proxy
- Implements proper memory management and error handling

## Technical Details

### Protocol Implementation
The implementation follows the SOCKS4 protocol specification as documented in the [OpenSSH SOCKS4 Protocol Specification](https://www.openssh.com/txt/socks4.protocol). The protocol uses a simple request-response format:

Request format:
```c
struct proxy_request {
    int8 vn;         // Version number: 4
    int8 cd;         // Command code: 1 for connect
    int16 dstport;   // Destination port
    int32 dstIP;     // Destination IP
    char userID[8];  // User ID field
};
```

Response format:
```c
struct proxy_response {
    int8 vn;        // Version number: 0 for reply
    int8 cd;        // Command code: 90 for success
    int16 _;        // Unused
    int32 __;       // Unused
};
```

### Key Features
- Built with standard C libraries
- Clean and documented code structure
- Error handling for network operations
- Support for basic HTTP requests
- Memory-safe implementation

## Dependencies
- Standard C libraries
- POSIX-compliant operating system
- C compiler (gcc recommended)

## Building and Running

1. Compile the code:
```bash
gcc -o socks4client main.c
```

2. Run the client:
```bash
./socks4client <destination_host> <destination_port>
```

## Implementation Details

The client follows these steps:
1. Establishes a connection to the SOCKS4 proxy server
2. Formats and sends the SOCKS4 request
3. Receives and validates the proxy response
4. If successful, handles the proxied connection
5. Performs cleanup and proper resource management

## Academic References

This implementation was inspired by and builds upon concepts from:
- Network Technology" by Dr. Jonas Birch
- Basic HTTP protocol specifications
- SOCKS4 protocol documentation

## Contributing

Feel free to submit issues and pull requests for improvements or bug fixes.
