# Makefile - Biên dịch 2 chương trình minh họa race condition
CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGETS = writeA writeB

# Mục tiêu mặc định
all: $(TARGETS)

# Biên dịch writeA
writeA: writeA.c
	$(CC) $(CFLAGS) -o writeA writeA.c

# Biên dịch writeB
writeB: writeB.c
	$(CC) $(CFLAGS) -o writeB writeB.c

# Xóa file thực thi và file dữ liệu để thử lại từ đầu
clean:
	rm -f $(TARGETS) data.txt

# Chạy thử nhanh (dùng & để chạy song song)
run:
	./writeA & ./writeB

.PHONY: all clean run
