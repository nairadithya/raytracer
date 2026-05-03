build: main.c
	gcc -O2 main.c
	./a.out > image.ppm
