CC = gcc
CFLAGS = -I./inc -g

SRC = main.c \
	   $(wildcard src/*.c)\

TARGET = music-player

all: $(TARGET)
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean