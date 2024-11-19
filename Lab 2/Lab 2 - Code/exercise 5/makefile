make: client server

client: client.o
	gcc -o client client.o

client.o: client.c funcs-ex5.h
	gcc -c client.c

server: server.o funcs-ex5.so funcs-ex5.h
	gcc -g -o server server.o -ldl

server.o: server.c
	gcc -c -g server.c

funcs-ex5.so: funcs-ex5.c
	gcc funcs-ex5.c -o funcs-ex5.so -ldl -shared -fPIC

clean:
	rm client server *.so *.o