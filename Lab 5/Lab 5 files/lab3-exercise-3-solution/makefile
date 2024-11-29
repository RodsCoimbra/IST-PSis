all: player server display-client

player: human-client.c
	gcc human-client.c -o player -lzmq -lncurses
	
server: server-exercise-3.c
	gcc server-exercise-3.c -o server -lzmq -lncurses

display-client: remote-display-client.c
	gcc remote-display-client.c -o display-client -lzmq -lncurses

clean:
	rm player server display-client
