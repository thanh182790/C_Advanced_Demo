TARGET := logger_demo

CC := gcc
CFLAGS := -Wall -Wextra -std=c11 -O2
LDFLAGS := 

SRCS := main.c logger.c
OBJS := $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) *.o *.log

run: all
	./$(TARGET)

.PHONY: all clean run

