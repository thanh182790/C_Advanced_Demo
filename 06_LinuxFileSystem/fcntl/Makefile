CC=gcc
CFLAGS=
TARGET=lockdemo
DEMOFILE=demo.txt

all: $(TARGET) $(DEMOFILE) howtodemo

$(TARGET): lockdemo.c
	$(CC) $(CFLAGS) -o $(TARGET) lockdemo.c

# Tạo demo.txt tự động
$(DEMOFILE):
	@echo "Creating demo.txt with sample data..."
	@printf 'ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789\n%.0s' {1..6} > $(DEMOFILE)
	@echo "demo.txt created."

# Hướng dẫn demo
howtodemo:
	@echo "==== HOW TO DEMO fcntl RECORD LOCKING ====" > howtodemo
	@echo "" >> howtodemo
	@echo "1. Terminal A: WRITE LOCK vùng 0–9 (block) với message HELLO" >> howtodemo
	@echo "    ./lockdemo W 0 10 block HELLO" >> howtodemo
	@echo "" >> howtodemo
	@echo "2. Terminal B: READ LOCK vùng 0–9 (nonblock)" >> howtodemo
	@echo "    ./lockdemo R 0 10 nonblock" >> howtodemo
	@echo "" >> howtodemo
	@echo "3. Terminal C: READ LOCK vùng 10–19 (nonblock, vùng khác, đọc bình thường)" >> howtodemo
	@echo "    ./lockdemo R 10 10 nonblock" >> howtodemo
	@echo "" >> howtodemo
	@echo "4. Khi nhấn ENTER ở Terminal A, vùng 0–9 được unlock, Terminal B có thể lock lại và ghi/đọc" >> howtodemo

clean:
	rm -f $(TARGET) $(DEMOFILE) howtodemo
