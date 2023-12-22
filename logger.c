/**
 * @file        logger.c
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

#include "logger.h"                                                                                                                                                                                          
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LOG_QUEUE_SIZE 10
#define LOG_MSG_MAX_LEN 256

#define MAX_LINE_LENGTH 1024
#define MAX_LINES 1000

// Mutex for thread-safe file access
static pthread_mutex_t file_mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    LogLevel level;
    char message[LOG_MSG_MAX_LEN];
} LogMessage;

static FILE *log_file = NULL;
static LogLevel current_level;
static pthread_t log_thread;
static LogMessage log_queue[LOG_QUEUE_SIZE];
static int queue_start = 0;
static int queue_end = 0;
static pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t log_cond = PTHREAD_COND_INITIALIZER;
static int running = 1;


void read_log_reverse_thread_safe(const char *filename) {
    char *lines[MAX_LINES];
    int line_count = 0;
    char buffer[MAX_LINE_LENGTH];

    pthread_mutex_lock(&file_mutex);

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        pthread_mutex_unlock(&file_mutex);
        return;
    }

    // Read lines into an array
    while (fgets(buffer, MAX_LINE_LENGTH, file) && line_count < MAX_LINES) {
        lines[line_count] = strdup(buffer);
        if (lines[line_count] == NULL) {
            perror("Memory allocation error");
            for (int i = 0; i < line_count; ++i) {
                free(lines[i]);
            }
            fclose(file);
            pthread_mutex_unlock(&file_mutex);
            return;
        }
        line_count++;
    }
    fclose(file);

    pthread_mutex_unlock(&file_mutex);

    // Print lines in reverse order
    for (int i = line_count - 1; i >= 0; i--) {
        printf("%s", lines[i]);
        free(lines[i]);
    }
}


// Thread function for processing log messages
void *log_thread_func(void *args) {
    printf("logging thread started");
    while (1) {
        pthread_mutex_lock(&log_mutex);

        // Wait for messages if queue is empty and still running
        while (queue_start == queue_end && running) {
            pthread_cond_wait(&log_cond, &log_mutex);
        }

        // Exit the loop if not running and queue is empty
        if (!running && queue_start == queue_end) {
            pthread_mutex_unlock(&log_mutex);
            break;
        }

        LogMessage msg = log_queue[queue_start];
        queue_start = (queue_start + 1) % LOG_QUEUE_SIZE;

        pthread_mutex_unlock(&log_mutex);

        // Lock the file mutex before writing to the log file
        pthread_mutex_lock(&file_mutex);

        // Write the log message to the file or standard output
        fprintf(log_file, "[%d] %s\n", msg.level, msg.message);
        fflush(log_file);

        // Unlock the file mutex after writing to the log file
        pthread_mutex_unlock(&file_mutex);
    }
    pthread_mutex_unlock(&log_mutex);
    return NULL;
}

int log_init(const char *filename, LogLevel level) {
    log_file = fopen(filename, "a");
    if (log_file == NULL) {
        printf("failed ot open file\n");
        return -1;
    }

    current_level = level;
    if (pthread_create(&log_thread, NULL, &log_thread_func, NULL) != 0) {
        fclose(log_file);
        return -1;
    }

    return 0;
}

void log_write(LogLevel level, const char *message) {
//    if (level < current_level) {
//        return;
//    }

    pthread_mutex_lock(&log_mutex);

    strncpy(log_queue[queue_end].message, message, LOG_MSG_MAX_LEN - 1);
    log_queue[queue_end].message[LOG_MSG_MAX_LEN - 1] = '\0';
    log_queue[queue_end].level = level;
    queue_end = (queue_end + 1) % LOG_QUEUE_SIZE;

    pthread_cond_signal(&log_cond);
    pthread_mutex_unlock(&log_mutex);
}

void log_close() {
    // Signal the logging thread to shut down
    pthread_mutex_lock(&log_mutex);
    running = 0;
    pthread_cond_signal(&log_cond);
    pthread_mutex_unlock(&log_mutex);

    // Wait for the logging thread to finish
    pthread_join(log_thread, NULL);

    fclose(log_file);
}


