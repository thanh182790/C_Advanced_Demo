CC=gcc
CFLAGS=-Wall -O2

OBJS=main.o sensor_parser.o sensor_decoder.o sensor_window.o rule_parser.o rule_engine.o condition_eval.o action_handler.o

all: engine

engine: $(OBJS)
	$(CC) $(CFLAGS) -o engine $(OBJS) -lm

clean:
	rm -f *.o engine

