CC = gcc
CFLAGS = -Wall -Wextra -std=c99

TARGET = uart_builder_demo

SRC = \
	main.c \
	uart-builder.c

OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

