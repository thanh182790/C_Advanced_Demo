CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = app 

# Mục tiêu mặc định
all: $(TARGET)

# Biên dịch chương trình chính
$(TARGET): demo.c
	$(CC) $(CFLAGS) -o $(TARGET) demo.c

# Chạy chương trình sau khi build
run: $(TARGET)
	@echo "=== Chay chuong trinh ==="
	@./$(TARGET)
	@echo "\n=== Xem noi dung file demo.txt ==="
	@cat demo.txt

# Xóa file thực thi và file dữ liệu
clean:
	rm -f $(TARGET) demo.txt

# Giả lập lại từ đầu
fresh: clean all run

.PHONY: all run clean fresh
