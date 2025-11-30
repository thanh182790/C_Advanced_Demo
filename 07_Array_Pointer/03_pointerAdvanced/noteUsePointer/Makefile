CC = gcc
CFLAGS =

TARGETS = pointerSense pointer2Array wrongPointer

all: $(TARGETS)

pointerSense: pointerSense.c
	$(CC) $(CFLAGS) -o pointerSense pointerSense.c

pointer2Array: pointer2Array.c
	$(CC) $(CFLAGS) -o pointer2Array pointer2Array.c

wrongPointer: wrongPointer.c
	$(CC) $(CFLAGS) -o wrongPointer wrongPointer.c

clean:
	rm -f $(TARGETS)
