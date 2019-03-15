TicTacToe1.3.0: main.o implement.o
	gcc main.o implement.o -o TicTacToe1.3.0
main.o : main.c
	gcc -c main.c
implement.o : implement.c
	gcc -c implement.c