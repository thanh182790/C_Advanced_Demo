CC       = gcc
TARGET   = if_switch_demo
SRC      = demoControlFlow.c
ASM_FILE = demoControlFlow.s

all: $(TARGET)

$(TARGET): clean $(SRC)
	$(CC) -o $(TARGET) $(SRC)

# Generate assembly output to inspect jump table
asm:
	$(CC) -S $(SRC) -o $(ASM_FILE)
	@echo "Assembly generated in $(ASM_FILE)"
clean:
	rm -f $(TARGET) $(ASM_FILE)
