CC = gcc

CFLAGS = -Wall -Wextra -std=c11

TARGETS = singleList doubleList

all: $(TARGETS)

singleList: 01_singleList.c
	$(CC) $(CFLAGS) 01_singleList.c -o 01_singleList
	@echo "--- Build Single Linked List: DONE ---"

doubleList: 02_doubleList.c
	$(CC) $(CFLAGS) 02_doubleList.c -o 02_doubleList
	@echo "--- Build Double Linked List: DONE ---"

clean:
	rm -f $(TARGETS)
	@echo "--- Cleaned up all executables ---"

.PHONY: all clean
