CC=gcc
CFLAGS=-lpthread -Wall
TARGET=logger
SRCS=main.c logger.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS) $(CFLAGS)

clean:
	rm -f $(TARGET)

