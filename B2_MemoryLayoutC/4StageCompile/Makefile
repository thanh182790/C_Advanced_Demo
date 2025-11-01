# === Compiler & Flags ===
CC = gcc 
CFLAGS = -Wall -Werror

# === Project Name ===
TARGET = main

# === Source files ===
SRC = main.c math_utils.c

# === Build directories ===
BUILD_DIR = build
PRE_DIR = $(BUILD_DIR)/preprocess
ASM_DIR = $(BUILD_DIR)/compile
OBJ_DIR = $(BUILD_DIR)/assemble
OUT_DIR = $(BUILD_DIR)/output

# === Derived file lists ===
PRE = $(SRC:%.c=$(PRE_DIR)/%.i)
ASM = $(SRC:%.c=$(ASM_DIR)/%.s)
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

# === Default target ===
all: dirs $(OUT_DIR)/$(TARGET)

# === Create directories ===
dirs:
	@mkdir -p $(PRE_DIR) $(ASM_DIR) $(OBJ_DIR) $(OUT_DIR)

# === STEP 1: Preprocessing ===
$(PRE_DIR)/%.i: %.c | dirs
	@echo "[STEP 1] Preprocessing $< → $@"
	$(CC) -E $< -o $@

preprocess: $(PRE)

# === STEP 2: Compilation (C → Assembly) ===
$(ASM_DIR)/%.s: $(PRE_DIR)/%.i | dirs
	@echo "[STEP 2] Compiling $< → $@"
	$(CC) -S $< -o $@

compile: $(ASM)

# === STEP 3: Assembly (Assembly → Object code) ===
$(OBJ_DIR)/%.o: $(ASM_DIR)/%.s | dirs
	@echo "[STEP 3] Assembling $< → $@"
	$(CC) -c $< -o $@

assemble: $(OBJ)

# === STEP 4: Linking (Object → Executable) ===
$(OUT_DIR)/$(TARGET): $(OBJ) | dirs
	@echo "[STEP 4] Linking object files → $@"
	$(CC) $(OBJ) -o $@
	cp $@ $(BUILD_DIR)/../$(TARGET)

linking: $(OUT_DIR)/$(TARGET)

# === Utility targets ===
run: $(OUT_DIR)/$(TARGET)
	@echo "[RUNNING PROGRAM]"
	@./$(OUT_DIR)/$(TARGET)

clean:
	@echo "[CLEANING BUILD FILES]"
	rm -f $(BUILD_DIR)/../$(TARGET)
	rm -rf $(BUILD_DIR)

.PHONY: all dirs preprocess compile assemble linking run clean

