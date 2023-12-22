/**
 * @file        logger.h
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

#ifndef LOGGER_H
#define LOGGER_H

#include <pthread.h>

/*
 * Enumeration for different levels of logging.
 * LOG_LEVEL_DEBUG: Used for detailed debugging messages.
 * LOG_LEVEL_INFO:  Used for general informational messages.
 * LOG_LEVEL_WARN:  Used for warning messages.
 * LOG_LEVEL_ERROR: Used for error messages.
 */
typedef enum {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR
} LogLevel;

/*
 * Initializes the logging system.
 * Parameters:
 *   filename - Name of the file to write log messages to.
 *   level - Minimum level of log messages to be written to the file.
 * Returns:
 *   0 on success, non-zero on failure.
 */
int log_init(const char *filename, LogLevel level);

/*
 * Writes a log message to the log file.
 * Only writes messages that are of a level equal to or higher than the current log level.
 * Parameters:
 *   level - Level of the log message.
 *   message - The log message to write.
 */
void log_write(LogLevel level, const char *message);

/*
 * Closes the logging system and releases any allocated resources.
 */
void log_close();

/*
 * Prints the log in reverse order from file. 
 */
void read_log_reverse_thread_safe(const char *filename);

#endif // LOGGER_H

