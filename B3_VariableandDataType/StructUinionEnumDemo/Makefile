# Makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
SRC = src/main.c src/demo_struct.c src/demo_union.c src/demo_system.c

struct:
	$(CC) $(CFLAGS) -DSTAGE_STRUCT src/main.c src/demo_struct.c -o ./demo_struct

union:
	$(CC) $(CFLAGS) -DSTAGE_UNION src/main.c src/demo_struct.c src/demo_union.c -o ./demo_union

enum:
	$(CC) $(CFLAGS) -DSTAGE_ENUM src/main.c src/demo_struct.c src/demo_union.c src/demo_system.c -o ./demo_system

clean:
	rm -rf demo*