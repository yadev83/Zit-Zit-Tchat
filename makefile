all: debug/ZZTc debug/ZZTs

debug/ZZTc: out/sockets/ZZTc.o out/sockets/socket.o out/tools/input.o out/gfx/gfx.o
	gcc $^ -o debug/ZZTc -lpthread -lncurses

debug/ZZTs: out/sockets/ZZTs.o out/sockets/socket.o out/interpreter/interpreter.o
	gcc $^ -o debug/ZZTs

server: out/server/ZZTs.o out/interpreter/interpreter.o
	gcc $^ -o out/ZZTs

client: out/client/ZZTc.o out/gfx/gfx.o
	gcc $^ -o out/ZZTc -lpthread -lncurses

out/client/ZZTc.o: src/client/client.c src/client/client.h
	gcc -c src/client/client.c -o out/client/ZZTc.o -lpthread -lncurses

out/server/ZZTs.o: src/server/server.c src/server/server.h
	gcc -c src/server/server.c -o out/server/ZZTs.o

out/sockets/ZZTs.o: src/sockets/testServ.c src/sockets/socket.h
	gcc -c -Wall src/sockets/testServ.c -o out/sockets/ZZTs.o

out/sockets/ZZTc.o: src/sockets/testClient.c
	gcc -c -Wall src/sockets/testClient.c -o out/sockets/ZZTc.o

out/tools/input.o: src/tools/input.c
	gcc -c -Wall src/tools/input.c -o out/tools/input.o

out/sockets/socket.o: src/sockets/socket.c src/sockets/socket.h
	gcc -c -Wall src/sockets/socket.c -o out/sockets/socket.o

out/gfx/gfx.o: src/gfx/gfx.c src/gfx/gfx.h
	gcc -c -Wall src/gfx/gfx.c -o out/gfx/gfx.o

out/interpreter/interpreter.o: src/interpreter/interpreter.c src/interpreter/interpreter.h
	gcc -c -Wall src/interpreter/interpreter.c -o out/interpreter/interpreter.o
