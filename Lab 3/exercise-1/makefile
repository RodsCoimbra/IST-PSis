make: human-client server machine-client

human-client: human-control-client.o fifo.o 
	gcc -o human-client human-control-client.o fifo.o -lncurses

human-control-client.o: human-control-client.c remote-char.h
	gcc -g -c human-control-client.c

machine-client: machine-control-client.o fifo.o 
	gcc -o machine-client machine-control-client.o fifo.o

machine-control-client.o: machine-control-client.c remote-char.h
	gcc -g -c machine-control-client.c

server: server.o fifo.o
	gcc -o server server.o fifo.o -lncurses

server.o: server.c remote-char.h
	gcc -g -c server.c

fifo.o: fifo.c fifo.h
	gcc -g -c fifo.c -o fifo.o

clean:
	rm human-client server machine-client *.o