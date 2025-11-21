CC = gcc
CFLAGS = -Wall -Wextra -O2
SRC = demoOperator.c
TARGET = demo


$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

float: clean
	$(CC) $(CFLAGS) -DFLOAT_COMPARE -o $(TARGET) $(SRC)

logic: clean
	$(CC) $(CFLAGS) -DLOGIC_TIMING -o $(TARGET) $(SRC)

pointer: clean
	$(CC) $(CFLAGS) -DPTR_INCREMENT -o $(TARGET) $(SRC)

all: $(TARGET)

clean:
	rm -f $(TARGET)

