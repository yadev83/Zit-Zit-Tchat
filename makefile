debug/ZZTc: out/main.o out/sockets/socket.o
	gcc $^ -o debug/ZZTc

debug/ZZTs: debug/ZZTs.o out/sockets/socket.o
	gcc $^ -o debug/ZZTs

debug/ZZTs.o: src/sockets/testServ.c src/sockets/socket.h
	gcc -c -Wall src/sockets/testServ.c -o debug/ZZTs.o

out/sockets/socket.o: src/sockets/socket.c src/sockets/socket.h
	gcc -c -Wall src/sockets/socket.c -o out/sockets/socket.o

out/main.o: src/main.c
	gcc -c -Wall src/main.c -o out/main.o
