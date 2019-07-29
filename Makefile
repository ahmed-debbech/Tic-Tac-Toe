all : prog excute clean
excute:
	 @echo "excuting..."
	./Tic-Tac-Toe
prog : main.o graphics.o core.o store.o
	@echo "building..."
	gcc main.c graphics.c core.c store.c -o Tic-Tac-Toe -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
clean:
	@echo "cleaning up..."
	rm *.o
