CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS =

SRC = \
src/main.c \
src/sensor/sensor_parser.c \
src/sensor/sensor_buffer.c \
src/rule/rule_parser.c \
src/rule/rule_engine.c \
src/rule/rule_condition.c \
src/action/action_dispatcher.c

OBJ = $(SRC:.c=.o)

TARGET = gateway

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean

