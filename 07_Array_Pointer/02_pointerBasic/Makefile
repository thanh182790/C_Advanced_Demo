CC = gcc
CFLAGS = 

TARGETS = pointer_1n pointer_2n virtualAddress

all: $(TARGETS)

pointer_1n: pointer_1n.c
	$(CC) $(CFLAGS) -o pointer_1n pointer_1n.c

pointer_2n: pointer_2n.c
	$(CC) $(CFLAGS) -o pointer_2n pointer_2n.c

virtualAddress: virtualAddress.c
	$(CC) $(CFLAGS) -o virtualAddress virtualAddress.c

clean:
	rm -f $(TARGETS)

