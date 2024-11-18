make: client server

client: client.o
	gcc -o client client.o

client.o: client.c
	gcc -c client.c

server: server.o funcs.so funcs.h
	gcc -g -o server server.o -ldl

server.o: server.c
	gcc -c -g server.c

funcs.so: funcs.c
	gcc funcs.c -o funcs.so -ldl -shared -fPIC

clean:
	rm client server *.so *.o