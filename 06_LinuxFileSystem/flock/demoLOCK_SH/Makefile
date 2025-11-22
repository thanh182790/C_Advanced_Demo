CC = gcc
CFLAGS = 
all: reader writer init howto

reader: reader.c
	$(CC) $(CFLAGS) reader.c -o reader

writer: writer.c
	$(CC) $(CFLAGS) writer.c -o writer

init:
	@echo -n "HELLO\n" > demo.txt
	@echo "Created demo.txt with initial content."

howto:
	@echo "Terminal A – reader A"        >  howtodemo
	@echo "    ./reader A"               >> howtodemo
	@echo "Terminal B – reader B"        >> howtodemo
	@echo "    ./reader B"               >> howtodemo
	@echo "Terminal C – writer (blocking)" >> howtodemo
	@echo "    ./writer"                 >> howtodemo
	@echo "Terminal C – writer -n (non blocking)" >> howtodemo
	@echo "    ./writer -n"              >> howtodemo
	@echo "Created howtodemo file."

clean:
	rm -f reader writer demo.txt howtodemo

