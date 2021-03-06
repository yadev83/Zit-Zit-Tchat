all: debug/ZZTc debug/ZZTs

debug/ZZTc: out/sockets/ZZTc.o out/sockets/socket.o
	gcc $^ -o debug/ZZTc

debug/ZZTs: out/sockets/ZZTs.o out/sockets/socket.o
	gcc $^ -o debug/ZZTs

out/sockets/ZZTs.o: src/sockets/testServ.c src/sockets/socket.h
	gcc -c -Wall src/sockets/testServ.c -o out/sockets/ZZTs.o

out/sockets/ZZTc.o: src/sockets/testClient.c
	gcc -c -Wall src/sockets/testClient.c -o out/sockets/ZZTc.o

out/sockets/socket.o: src/sockets/socket.c src/sockets/socket.h
	gcc -c -Wall src/sockets/socket.c -o out/sockets/socket.o
