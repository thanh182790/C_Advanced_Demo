CC := gcc
CFLAGS := -Wall -Wextra -g

# (1) FILE DISCOVERY – filesystem wildcard
SRCS := $(wildcard *.c)

# (2) FILE MAPPING – pattern (%) replacement
OBJS := $(SRCS:.c=.o) 

# Final target
app: $(OBJS)  # main.o util.o
	@echo "Gia tri cua $^"
	echo "Linking: $^ -> $@"
	$(CC) $^ -o $@

# (3) PATTERN RULE – stem (%) + automatic variables
%.o: %.c
	echo "Compiling: source=$< target=$@"
	$(CC) $(CFLAGS) -c $< -o $@

info:
	echo "SRCS = $(SRCS)"
	echo "OBJS = $(OBJS)"

clean:
	rm -f *.o app
.PHONY: app info clean
