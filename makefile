run: all
	./run

all: fractal.o
	gcc -o run fractal.o 

fractal.o: fractal.c
	gcc -c fractal.c

clean:
	rm -rf *~
	rm -rf *.o
	rm -rf *.ppm
	rm -rf run
