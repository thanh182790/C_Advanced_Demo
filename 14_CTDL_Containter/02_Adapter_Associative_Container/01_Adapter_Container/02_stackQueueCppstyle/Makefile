CC = g++

CFLAGS = -Wall -Wextra -std=c++11

TARGETS = stack queue priQueue


all: $(TARGETS)

stack: 01_stack.cpp
	$(CC) $(CFLAGS) 01_stack.cpp -o stack
	@echo "--- Build stack: DONE ---"

queue: 02_queue.cpp
	$(CC) $(CFLAGS) 02_queue.cpp -o queue
	@echo "--- Build queue: DONE ---"

priQueue: 03_prioryQueuee.cpp
	$(CC) $(CFLAGS) 03_prioryQueuee.cpp -o priQueue
	@echo "--- Build priQueue: DONE ---"

clean:
	rm -f $(TARGETS)
	@echo "--- Cleaned up all executables ---"

.PHONY: all clean
