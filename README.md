# ThreadSafeCLogger

A high-performance, thread-safe logging library for C applications, designed to provide reliable and concurrent log handling with minimal performance overhead.

## Features

- **Multi-threaded Logging:** Efficiently handles log writing in a separate thread, ensuring minimal impact on application performance.
- **Thread Safety:** Synchronized access to log files, making it safe for use in multi-threaded applications.
- **In-memory Queueing:** Queues log messages in memory for efficient batch processing.
- **Reverse Order Log Reading:** Provides functionality to read logs in reverse order, showing the most recent entries first.
- **Customizable Log Levels:** Supports different log levels (DEBUG, INFO, WARN, ERROR) for detailed logging control.

## Getting Started

### Prerequisites

- GCC compiler or any standard C compiler with support for the POSIX Threads (pthreads) library.
- Basic knowledge of C programming and multi-threaded concepts.

### Installing

Clone the repository to your local machine:

```bash
git clone https://github.com/harshithsunku/ThreadSafeCLogger.git
```

Navigate to the cloned directory:

```bash
cd ThreadSafeCLogger
```

Compile the library:

```bash
gcc -o logger main.c logger.c -lpthread
```

### Building the Project with Makefile

You can build the project using the provided Makefile:

```bash
make
```

This will create an executable named `logger`.

To clean up the build (remove the compiled output), run:

```bash
make clean
```


### Usage

Here's a simple example of how to use ThreadSafeCLogger in your C application:

```c
#include "logger.h"

int main() {
    // Initialize the logger
    log_init("log.txt", LOG_LEVEL_DEBUG);

    // Write log messages
    log_write(LOG_LEVEL_INFO, "Application started");
    // Your application code here
    log_write(LOG_LEVEL_INFO, "Application ending");

    // Close the logger
    log_close();

    return 0;
}
```

## Documentation

- **`log_init`:** Initializes the logging system.
- **`log_write`:** Writes a log message to the queue.
- **`log_close`:** Closes the logging system, ensuring all messages are processed.

For more detailed documentation, see [docs/documentation.md](docs/documentation.md).

## Contributing

Contributions to ThreadSafeCLogger are welcome! Please read our [Contributing Guidelines](CONTRIBUTING.md) for more information on how to contribute.

## License

This project is licensed under the [GNU General Public License v3 (GPLv3)](LICENSE).

![GPLv3 License](https://img.shields.io/badge/License-GPLv3-blue.svg)


## Acknowledgements

- Thanks to all contributors who have helped with the development and improvement of ThreadSafeCLogger.
