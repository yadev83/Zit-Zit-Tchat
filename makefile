exec: out/main.o out/sockets/socket.o
	gcc $^ -o exec

out/sockets/socket.o: src/sockets/socket.c src/sockets/socket.h
	gcc -c -Wall src/sockets/socket.c -o out/sockets/socket.o

out/main.o: src/main.c
	gcc -c -Wall src/main.c -o out/main.o