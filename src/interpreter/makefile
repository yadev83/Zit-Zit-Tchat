interpreter: interpreter.o
	gcc -Wall interpreter.o -o interpreter -lm -lglut -lGL -lX11

interpreter.o: interpreter.c interpreter.h
	gcc -Wall -c -g interpreter.c

clean:
	rm -f *~ *.o