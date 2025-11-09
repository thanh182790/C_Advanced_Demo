# ======================
# SmartController Project
# ======================
CC = gcc
CXX = g++
CFLAGS = -Wall -Icommon/inc -ICore/inc -IDrivers/inc -IRegisters/inc -IMiddleware/inc
CXXFLAGS = -std=c++17 $(CFLAGS)

BUILD_DIR = build

# ---- Source files grouped by layer ----
SRC_COMMON = common/src/utils.c
SRC_REGISTERS = Registers/src/registers.c
SRC_DRIVERS = Drivers/src/adc.c Drivers/src/gpio.c Drivers/src/uart.c
SRC_MIDDLEWARE = Middleware/src/controller.c Middleware/src/error.c Middleware/src/sensors.c
SRC_CORE = Core/src/system.c
SRC_APP = App/main.cpp

# ---- Flattened object file names (strip folder structure) ----
OBJ_COMMON = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SRC_COMMON)))
OBJ_REGISTERS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SRC_REGISTERS)))
OBJ_DRIVERS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SRC_DRIVERS)))
OBJ_MIDDLEWARE = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SRC_MIDDLEWARE)))
OBJ_CORE = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SRC_CORE)))

OBJ_ALL = $(OBJ_COMMON) $(OBJ_REGISTERS) $(OBJ_DRIVERS) $(OBJ_MIDDLEWARE) $(OBJ_CORE)

# ======================
# Default target
# ======================
.PHONY: all clean build_storage_class build_full build_asm

all: build_full

# ======================
# Generic rule to build .o from any .c (flattened)
# ======================
$(BUILD_DIR)/%.o:
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(filter %/$(notdir $*).c,$(SRC_COMMON) $(SRC_REGISTERS) $(SRC_DRIVERS) $(SRC_MIDDLEWARE) $(SRC_CORE)) -o $@

# ======================
# Phase 1 demo (static / extern / volatile)
# ======================
build_storage_class: CFLAGS += -DDEMO_STORAGE_CLASS
build_storage_class: clean $(OBJ_COMMON) $(OBJ_REGISTERS) $(OBJ_DRIVERS) $(OBJ_CORE)
	$(CXX) $(CXXFLAGS) $(OBJ_COMMON) $(OBJ_REGISTERS) $(OBJ_DRIVERS) $(OBJ_CORE) $(SRC_APP) -o demoStorageClass.out

# ======================
# Full demo (add struct / union / enum)
# ======================
build_full: $(OBJ_ALL)
	$(CXX) $(CXXFLAGS) $(OBJ_ALL) $(SRC_APP) -o demoFullApp.out

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
	rm -rf $(BUILD_DIR) asm demoFullApp.out demoStorageClass.out
