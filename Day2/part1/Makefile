CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=gnu99 -g
LDFLAGS=-lm
PROGRAMS=main
TESTS=..

.PHONY: all test clean ../src.zip

all: $(PROGRAMS)

main: main.o 
	gcc -o $@ $^ $(LDFLAGS)

clean: 
	rm -rf $(PROGRAMS)  *.o core