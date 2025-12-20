CC      := gcc
CFLAGS  := -g -O0 -Wall -Wextra
SRC     := demo.c

.PHONY: all clean

all:
	@echo "Available targets:"
	@echo "  make uninit_local"
	@echo "  make uninit_heap"
	@echo "  make out_of_bound"
	@echo "  make use_after_free"
	@echo "  make leak"

uninit_local:
	$(CC) $(CFLAGS) -DDEMO_UNINIT_LOCAL $(SRC) -o demo_uninit_local
	valgrind --tool=memcheck --track-origins=yes ./demo_uninit_local

uninit_heap:
	$(CC) $(CFLAGS) -DDEMO_UNINIT_HEAP $(SRC) -o demo_uninit_heap
	valgrind --tool=memcheck --track-origins=yes ./demo_uninit_heap

out_of_bound:
	$(CC) $(CFLAGS) -DDEMO_OUT_OF_BOUND $(SRC) -o demo_oob
	valgrind --tool=memcheck --track-origins=yes --show-leak-kinds=all ./demo_oob

use_after_free:
	$(CC) $(CFLAGS) -DDEMO_USE_AFTER_FREE $(SRC) -o demo_uaf
	valgrind --tool=memcheck ./demo_uaf

leak:
	$(CC) $(CFLAGS) -DDEMO_LEAK $(SRC) -o demo_leak
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./demo_leak

clean:
	rm -f demo_*

