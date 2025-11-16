# ======================
# SmartController Project
# ======================
CC = gcc
CXX = g++
CFLAGS = -Wall -Icommon/inc -ICore/inc -IDrivers/inc -IRegisters/inc
CXXFLAGS = -std=c++17 $(CFLAGS)

BUILD_DIR = build

# ---- Source files grouped by layer ----
SRC_COMMON = common/src/utils.c
SRC_DRIVERS = Drivers/src/adc.c Drivers/src/uart.c
SRC_CORE = Core/src/system.c
SRC_APP = App/main.cpp

# ---- Flattened object file names (strip folder structure) ----
OBJ_COMMON = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SRC_COMMON)))
OBJ_DRIVERS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SRC_DRIVERS)))
OBJ_CORE = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SRC_CORE)))

OBJ_ALL = $(OBJ_COMMON) $(OBJ_REGISTERS) $(OBJ_DRIVERS) $(OBJ_MIDDLEWARE) $(OBJ_CORE)

# ======================
# Default target
# ======================
.PHONY: all clean build_storage_class  build_asm

all: build_storage_class

# ======================
# Generic rule to build .o from any .c (flattened)
# ======================
$(BUILD_DIR)/%.o:
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(filter %/$(notdir $*).c,$(SRC_COMMON) $(SRC_DRIVERS) $(SRC_CORE)) -o $@

# ======================
# Phase 1 demo (static / extern / volatile)
# ======================
build_storage_class: $(OBJ_COMMON) $(OBJ_DRIVERS) $(OBJ_CORE)
	$(CXX) $(CXXFLAGS) $(OBJ_COMMON) $(OBJ_DRIVERS) $(OBJ_CORE) $(SRC_APP) -o demoStorageClass.out

# ======================
# Build Assembly demo (for volatile optimization)
# ======================
build_asm:
	@mkdir -p asm
	$(CC) $(CFLAGS) -S common/src/utils.c -o asm/utils.s -O3
	@echo "Generated asm/utils.s "

# ======================
# Cleanup
# ======================
clean:
	rm -rf $(BUILD_DIR) asm demoStorageClass.out
