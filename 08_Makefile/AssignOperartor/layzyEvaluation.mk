all:
	@echo A = $(A)
	@echo B = $(B)

A = hello
B = $(A) world

A = hi














# Make KHÔNG tính giá trị biến ngay khi gán,
# mà chờ đến lúc biến được dùng mới tính.

# Giai đoạn 1 – Đọc Makefile
# 	Make chỉ đọc và ghi nhớ
# 	KHÔNG chạy shell
# 	KHÔNG thay biến
# Giai đoạn 2 – Thực thi target
# 	Khi gặp $(VAR)
# 	Make mới mở rộng (expand) biến
# Với phép gán =, biến chỉ được mở rộng ở giai đoạn 2
