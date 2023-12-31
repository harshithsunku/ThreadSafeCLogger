/**
 * @file        main.c
 * @brief       ThreadSafeCLogger: A high-performance, thread-safe logging library for C applications.
 * @author      Harshith Sunku
 * @date        [12/22/2023]
 * @version     1.0
 * @website     https://www.harshith.in/ | https://harshithsunku.in/
 * @repository  https://github.com/harshithsunku/ThreadSafeCLogger
 *
 * @note        This file is part of ThreadSafeCLogger, which provides multi-threaded 
 *              logging capabilities in a thread-safe manner.
 * @details     Further details about the implementation can be found in
 *              the README or the official documentation at the above website/github.
 * 
 * ThreadSafeCLogger is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * ThreadSafeCLogger is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with ThreadSafeCLogger. If not, see <https://www.gnu.org/licenses/>.
 *
 * @bugs        No known bugs at the time of writing.
 * @todo        Features or fixes planned for future versions.
 */

#include <stdio.h>
#include "logger.h"

/*
 * Main function of the application.
 * Initializes the logger, performs application tasks, and then closes the logger.
 */
int main() {
    // Initialize the logger
    if (log_init("log.txt", LOG_LEVEL_INFO) != 0) {
        fprintf(stderr, "Failed to initialize logger\n");
        return 1;
    }

    // Write a log message indicating the application has started
    log_write(LOG_LEVEL_INFO, "Application started");

    // Application code here

    // Write a log message indicating the application is ending
    log_write(LOG_LEVEL_INFO, "Application ending");

    //Function to print the log in reverse order.
    read_log_reverse_thread_safe("log.txt");

    // Close the logger
    log_close();

    return 0;
}
