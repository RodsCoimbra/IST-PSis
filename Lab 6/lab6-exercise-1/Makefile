#sudo apt install protobuf-c-compiler
#sudo apt install libprotobuf-c-dev
all: balls.pb-c.c remote-display-client


balls.pb-c.c: balls.proto
	protoc-c --c_out=. balls.proto

remote-display-client: remote-display-client.c ../balls.pb-c.c
	gcc remote-display-client/remote-display-client.c ../balls.pb-c.c -o remote-display-client -g -lzmq -lncurses -lprotobuf-c