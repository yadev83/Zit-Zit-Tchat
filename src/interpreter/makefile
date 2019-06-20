interpreter: interpreter.o
	gcc -Wall interpreter.o -o interpreter

interpreter.o: interpreter.c interpreter.h
	gcc -Wall -c -g interpreter.c

clean:
	rm -f *~ *.o