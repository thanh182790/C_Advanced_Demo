CC=gcc
CFLAGS=-Wall -Wextra -O0 -g

SRC = app/main.c \
      driver/ledDriver.c

TARGET = ledRgbDemo

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

