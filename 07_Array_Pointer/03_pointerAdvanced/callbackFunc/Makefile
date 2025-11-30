CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRCS = main.c app.c uart_driver.c
OBJS = $(SRCS:.c=.o)
TARGET = uart_demo

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

