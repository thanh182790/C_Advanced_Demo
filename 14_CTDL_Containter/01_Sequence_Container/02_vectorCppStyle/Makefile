CC = g++

CFLAGS = -Wall -g

TARGET = sensor_demo
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)
	@echo "------------------------------------------------"
	@echo "Biên dịch thành công! Gõ './$(TARGET)' để chạy."
	@echo "------------------------------------------------"

clean:
	rm -f $(TARGET)
	@echo "Đã dọn dẹp file thực thi."
