CC = gcc
CFLAGS = -Wall -Werror -std=c17

# Compile all C files in the src, src/* and src/*/* directories
EXCLUDE_DRIVER_FILES = %driver.c %driver_string.c %driver_file.c %driver_trie.c %driver_inbox.c

build:
	$(CC) $(CFLAGS) $(filter-out $(EXCLUDE_DRIVER_FILES), $(wildcard src/*.c src/modules/*/*.c src/modules/*/*/*.c)) -o bin/main

# Run the compiled program
run:
	./bin/main

# Compile and run the program
all: build run

# Clean up the compiled program
clean:
	rm bin/main