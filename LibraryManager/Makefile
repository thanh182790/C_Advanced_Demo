CC=gcc
CFLAGS=-I./Book -I./User -I./Management -I./Ultils -Wall -Wextra

SRC = main.c \
      Book/book.c \
      User/user.c \
      Management/management.c \
      Ultils/ultils.c

BUILD_DIR = build
OBJ = $(addprefix $(BUILD_DIR)/,$(notdir $(SRC:.c=.o)))
$(info ---$(OBJ)---)
TARGET = library_manager

all: $(TARGET)

# Tạo build/ nếu chưa có
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Build tất cả .c ra build/.o
$(BUILD_DIR)/%.o: */%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: main.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
