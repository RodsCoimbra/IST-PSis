prog1: prog1.o lib1.o
	gcc -o prog1 prog1.o lib1.o

prog1.o: prog1.c lib.h
	gcc -c prog1.c

lib1.o: lib1.c 
	gcc -c lib1.c

clean:
	rm prog1 *.o 

run:
	./prog1
