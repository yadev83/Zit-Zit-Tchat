exec: out/main.o
	gcc out/main.o -o exec

out/main.o: src/main.c
	gcc -c -Wall src/main.c -o out/main.o