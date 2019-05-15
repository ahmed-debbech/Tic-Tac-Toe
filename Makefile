all : prog excute clean
excute:
	 @echo "excuting..."
	./Tic-Tac-Toe-2.0
prog : main.o graphics.o core.o
	@echo "building..."
	gcc main.c graphics.c core.c -o Tic-Tac-Toe-2.0 -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
clean:
	@echo "cleaning up..."
	rm *.o
