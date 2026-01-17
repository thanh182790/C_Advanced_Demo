A = hello
B := $(A) world

A = hi

B := NOOOO
all:
	@echo A = $(A)
	@echo B = $(B)

# Make TÍNH giá trị biến NGAY khi gán bằng :=
#
# Giai đoạn 1 – Đọc Makefile
#   - Make gặp: B := $(A) world
#   - Lúc này A = hello
#   - => B được tính ngay = "hello world"
#
# Giai đoạn 2 – Thực thi target
#   - A đã bị đổi thành "hi"
#   - B KHÔNG thay đổi nữa

