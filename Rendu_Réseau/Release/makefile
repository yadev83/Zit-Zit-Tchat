server: out/server/ZZTs.o out/interpreter/interpreter.o
	gcc $^ -o out/ZZTs

client: out/client/ZZTc.o 
	gcc $^ -o out/ZZTc -lpthread

out/client/ZZTc.o: src/client/client.c src/client/client.h
	gcc -c src/client/client.c -o out/client/ZZTc.o

out/server/ZZTs.o: src/server/server.c src/server/server.h
	gcc -c src/server/server.c -o out/server/ZZTs.o

out/sockets/ZZTs.o: src/sockets/testServ.c src/sockets/socket.h
	gcc -c -Wall src/sockets/testServ.c -o out/sockets/ZZTs.o

out/sockets/ZZTc.o: src/sockets/testClient.c
	gcc -c -Wall src/sockets/testClient.c -o out/sockets/ZZTc.o

out/interpreter/interpreter.o: src/interpreter/interpreter.c src/interpreter/interpreter.h
	gcc -c -Wall src/interpreter/interpreter.c -o out/interpreter/interpreter.o
