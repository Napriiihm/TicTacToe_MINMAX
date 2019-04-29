tictactoe.o: tictactoe.h tictactoe.c 
	gcc -Wall -g -c tictactoe.c -std=c99

TP4: tictactoe.o
	gcc -Wall -g -o TP4 tictactoe.o -std=c99

all: TP4

clear:
	rm -rf *.o