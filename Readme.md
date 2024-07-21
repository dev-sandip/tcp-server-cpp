
# TCP Server Using C++ 

## Overview

This project implements a basic TCP server in C++. The server listens for incoming connections on a specified IP address and port, processes client requests, and responds with a fixed HTTP response containing a simple HTML page.

## Features

- Handles incoming TCP connections.
- Reads and logs client requests.
- Sends a static HTTP response with an HTML page.

## Directory Structure

```
.
├── http_tcpServer_linux.cpp    # Implementation of the TcpServer class
├── http_tcpServer_linux.h      # Header file for the TcpServer class
├── main.cpp                    # Main file to run the server
└── README.md                   # This README file
```

## Prerequisites

- g++ compiler

## Building the Project

1. **Clone the repository**:

   ```sh
   git clone <repository_url>
   cd <repository_directory>
   ```

2. **Compile the source files**:

   ```sh
   g++ -c http_tcpServer_linux.cpp -o http_tcpServer_linux.o
   g++ -c main.cpp -o main.o
   g++ http_tcpServer_linux.o main.o -o server
   ```

   This will generate an executable named `server`.

## Running the Server

To run the server, execute the following command from the project directory:

```sh
./server
```

By default, the server listens on IP address `0.0.0.0` and port `8080`.

## Code Overview

### Header File: `http_tcpServer_linux.h`

This file declares the `TcpServer` class and its methods:

- **TcpServer**: Constructor and destructor.
- **startListening**: Starts the server and listens for incoming connections.
- **initializeServer**: Initializes server settings and creates the socket.
- **shutdownServer**: Closes the server socket.
- **acceptClientConnection**: Accepts new client connections.
- **buildHttpResponse**: Builds the HTTP response message.
- **sendHttpResponse**: Sends the HTTP response to the client.

### Implementation File: `http_tcpServer_linux.cpp`

This file contains the implementation of the `TcpServer` class, including methods for:
- Initializing the server (`initializeServer`)
- Accepting client connections (`acceptClientConnection`)
- Building and sending HTTP responses (`buildHttpResponse`, `sendHttpResponse`)

### Main File: `main.cpp`

Contains the `main` function that:
- Creates an instance of `TcpServer`
- Calls `startListening` to begin accepting connections and processing requests.

## Team Members

- **Sandip Sapkota**
  - Roll Number :PUR079BCT076
  - Contact: 079bct076@ioepc.edu.np

- **Subhakar Pant**
   - Roll Number :PUR079BCT084
   - Contact: 079bct084@ioepc.edu.np

- **Raghav Updhayay**
   - Roll Number :PUR079BCT057
   - Contact: 079bct057@ioepc.edu.np

- **Sulav Poudel**
  - Roll Number :PUR079BCT087
  - Contact: 079bct087@ioepc.edu.np

- **Samir Basnet**
   - Roll Number :PUR079BCT071
   - Contact: 079bct071@ioepc.edu.np

## Contributing

This project is a collaborative effort involving multiple contributors. If you would like to contribute:
- Fork the repository.
- Make improvements or fixes in your fork.
- Submit a pull request.

Please follow best practices for code quality and documentation.

## Contact

For any questions or feedback, please contact [here](mailto:sandipsapkota@duck.com).
