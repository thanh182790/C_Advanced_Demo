CC = gcc

CFLAGS = -Wall -Wextra -std=c11

TARGETS = stack queue

all: $(TARGETS)

stack: 01_stack.c
	$(CC) $(CFLAGS) 01_stack.c -o stack
	@echo "--- Build stack: DONE ---"

queue: 02_queue.cpp
	$(CC) $(CFLAGS) 02_queue.c -o queue
	@echo "--- Build queue: DONE ---"

clean:
	rm -f $(TARGETS)
	@echo "--- Cleaned up all executables ---"

.PHONY: all clean
