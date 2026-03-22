CC = gcc
CFLAGS = -Ifactory \
	-Itemperature \
	-Ihumidity \
	-Ilight \
	-Ipressure

TARGET = factory_demo

SRC = \
	main.c \
	factory/sensor-factory.c \
	temperature/temperature-sensor.c \
	humidity/humidity-sensor.c \
	light/light-sensor.c \
	pressure/pressure-sensor.c

OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

