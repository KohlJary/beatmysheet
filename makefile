CC = gcc
CFLAGS = -lncurses -I./include/
SOURCES = ./src/*.c

all: build run clean

build:
	$(CC) $(SOURCES) $(CFLAGS)  -o beatmysheet

run:
	./beatmysheet

clean:
	rm beatmysheet
