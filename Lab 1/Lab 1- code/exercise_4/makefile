main: main.o lib1.so lib2.so lib.h
	gcc -o main main.o -ldl
main.o: main.c
	gcc -Wall -c main.c

lib1.so: lib1.c
	gcc lib1.c -o lib1.so -ldl -shared -fPIC

lib2.so: lib2.c
	gcc lib2.c -o lib2.so -ldl -shared -fPIC

clean:
	rm main *.so

run:
	./main

