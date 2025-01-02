# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra

# Find all .c files in current directory
SRCS = $(wildcard *.c)

# Output executable name
TARGET = inventory

# Default target
all: $(TARGET)

# Directly compile and link all source files
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

# Clean up build files
clean:
	rm -f $(TARGET)

# Print variables for debugging
debug:
	@echo "Source files:"
	@echo $(SRCS)

.PHONY: all clean debug
