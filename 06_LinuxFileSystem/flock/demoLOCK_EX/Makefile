CC = gcc

all: writer_ex reader_try howto

writer_ex: writer_ex.c
	$(CC) writer_ex.c -o writer_ex

reader_try: reader_try.c
	$(CC) reader_try.c -o reader_try

howto:
	@echo "===== DEMO LOCK_EX =====" > howtodemo
	@echo "Terminal A – writer EX (blocking)" >> howtodemo
	@echo "    ./writer_ex" >> howtodemo
	@echo "" >> howtodemo
	@echo "Terminal B – reader try SH" >> howtodemo
	@echo "    ./reader_try SH" >> howtodemo
	@echo "" >> howtodemo
	@echo "Terminal C – reader try EX" >> howtodemo
	@echo "    ./reader_try EX" >> howtodemo
	@echo "" >> howtodemo
	@echo "Terminal D – writer non-block" >> howtodemo
	@echo "    ./writer_ex -n" >> howtodemo

clean:
	rm -f writer_ex reader_try howtodemo demo.txt

