# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -I.  # -I. to include headers from the current dir

# Source files
LIB_SRC = msocket.c
EXAMPLE_SRC = examples/example.c

# Output binary
EXAMPLE_BIN = examples/example

# Default target
all: $(EXAMPLE_BIN)

# Link example binary with mysocket object
$(EXAMPLE_BIN): $(EXAMPLE_SRC) $(LIB_SRC)
	$(CC) $(CFLAGS) -o $@ $(EXAMPLE_SRC) $(LIB_SRC)

# Clean up
clean:
	rm -f $(EXAMPLE_BIN)

