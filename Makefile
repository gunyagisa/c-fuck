CC = gcc

%.o: %.c
	$(CC) -c $< -o $@

build: main.o
	$(CC) *.o -o fucc
	./fucc

clean:
	rm -f *.o a.out

PHONY: build

