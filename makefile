
10cc:
	cp ~/compiler/10cc .

tmp.s: mandelbrot.c 10cc
	./10cc mandelbrot.c > tmp.s

tmp.o: tmp.s 10cc
	gcc -static -o tmp.o tmp.s

all: 10cc tmp.o
	./tmp.o
