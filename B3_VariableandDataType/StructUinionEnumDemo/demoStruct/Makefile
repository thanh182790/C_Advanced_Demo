CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
TARGET = demoStruct
SRC = demoStruct.c

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET)
