# Project name
TARGET = ascii_art

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lm

# Source and object files
SRC = img2asciiart.c

# Default target
all: 
	$(CC) -o $(TARGET) $(SRC) $(LDFLAGS) $(CFLAGS)

# Clean up build files
clean:
	rm -f $(TARGET)

# Phony targets so they don't get confused with files
.PHONY: all clean