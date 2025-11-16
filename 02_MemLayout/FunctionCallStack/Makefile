# ==========================
# Makefile for Function Call Stack Demo
# ==========================

CC = gcc
CFLAGS = -Wall -g
TARGET = main
SRC = main.c
ASM = $(SRC:.c=.s)

# Default build: compile executable
all: $(TARGET)

# Rule to build executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to generate assembly file
asm: $(ASM)

%.s: %.c
	$(CC) $(CFLAGS) -S -fverbose-asm -o $@ $<

# Clean build files
clean:
	rm -f $(TARGET) $(ASM)

