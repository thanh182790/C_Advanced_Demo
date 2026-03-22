CC = gcc
CFLAGS =  -I./base-uart -I./decorators/compression -I./decorators/crc -I./decorators/encryption -I./decorators/logging

SRCS = $(wildcard *.c) \
       $(wildcard ./base-uart/*.c) \
       $(wildcard ./decorators/logging/*.c) \
       $(wildcard ./decorators/encryption/*.c) \
       $(wildcard ./decorators/compression/*.c) \
       $(wildcard ./decorators/crc/*.c)

TARGETS = demoUart

all: $(TARGETS)
$(TARGETS): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGETS) sensor_system.log 

.PHONY: all clean