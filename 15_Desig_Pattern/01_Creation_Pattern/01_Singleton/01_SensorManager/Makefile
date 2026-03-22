# ===============================
# Project configuration
# ===============================

TARGET  := sensor_manager_demo
CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -O2
LDFLAGS := 

SRCS := main.c sensor_manager.c
OBJS := $(SRCS:.c=.o)

# ===============================
# Build rules
# ===============================

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) *.o

run: all
	./$(TARGET)

.PHONY: all clean run

