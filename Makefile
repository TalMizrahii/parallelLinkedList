# Compiler settings - adjust as needed
CC=gcc
CFLAGS=-std=c99 -Wall -fopenmp

# Project files
SRC=main.c linkedList.c
OBJ=$(SRC:.c=.o)
EXEC=a.out  # Name of the executable file

# Default target
all: build

# Build the program
build: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Individual file targets
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Run the program
run: build
	./$(EXEC)

# Clean up build files
clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all build run clean
