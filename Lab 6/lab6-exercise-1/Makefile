#sudo apt install protobuf-c-compiler
#sudo apt install libprotobuf-c-dev
all: balls remote-display-client server machine-client human-client


balls: balls.proto
	protoc-c --c_out=. balls.proto

remote-display-client: remote-display-client/remote-display-client.c balls.pb-c.c
	gcc remote-display-client/remote-display-client.c balls.pb-c.c -o remote_disp -g -lzmq -lncurses -lprotobuf-c

server: server/server.c balls.pb-c.c
	gcc server/server.c balls.pb-c.c  -o main_server -g -lzmq -lncurses -lprotobuf-c

machine-client: machine-client/machine-client.c balls.pb-c.c
	gcc machine-client/machine-client.c balls.pb-c.c -o machine -g -lzmq -lprotobuf-c

human-client: human-client/human-client.c balls.pb-c.c
	gcc human-client/human-client.c balls.pb-c.c -o human -g -lzmq -lncurses -lprotobuf-c

