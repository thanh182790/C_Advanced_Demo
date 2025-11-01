CC       := gcc
TARGET   := memoryLayout
SRC      := memoryLayout.c
OBJ      := $(SRC:.c=.o) #replace all .c in SRC to .o
MAPFILE  := $(TARGET).map

# Compiler flags
CFLAGS   := -Wall -Wextra -g -O0
# Linker flags: create .map file
LDFLAGS  := -Wl,-Map=$(MAPFILE)

# ======================================================
# Default target: build and generate map file
# ======================================================
all: $(TARGET) 

# Link target (produce .map via LDFLAGS)
$(TARGET): $(OBJ)
	@echo "Linking $(TARGET)..."
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET) $(LDFLAGS)
	@echo "Build complete: $(TARGET)"

# Compile .c -> .o
%.o: %.c
	@echo "Compiling $< ..."
	$(CC) $(CFLAGS) -c $< -o $@

# ======================================================
# Run program
# ======================================================
run: $(TARGET)
	@echo "Running $(TARGET)..."
	./$(TARGET)

# ======================================================
# Clean up
# ======================================================
clean:
	@echo "Cleaning build files..."
	rm -f $(TARGET) $(OBJ) $(MAPFILE)

.PHONY: all clean run 

