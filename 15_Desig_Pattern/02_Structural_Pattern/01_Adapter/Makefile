CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -std=c11 -g

INC_DIR = \
    -Iinterface \
    -Ifactory \
    -Inew_uart \
    -Ilegacy_uart \
    -Ilegacy_adapter

SRC_COMMON = \
    app.c \
    factory/uart_factory.c

SRC_NEW = \
    new_uart/new_uart.c

SRC_LEGACY = \
    legacy_uart/legacy_uart.c \
    legacy_adapter/legacy_uart_adapter.c

# chọn driver: new | legacy
DRIVER ?= new

ifeq ($(DRIVER),legacy)
CFLAGS += -DUSE_LEGACY_UART
SRC = $(SRC_COMMON) $(SRC_LEGACY)
else
CFLAGS += -DUSE_NEW_UART
SRC = $(SRC_COMMON) $(SRC_NEW)
endif

OBJ = $(SRC:.c=.o)
TARGET = uart_demo

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

