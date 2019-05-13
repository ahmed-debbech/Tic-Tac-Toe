all : prog excute clean
excute:
	 @echo "excuting..."
	./tictactoe
prog : main.o graphics.o core.o
	@echo "building..."
	gcc main.c graphics.c core.c -o tictactoe -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
clean:
	@echo "cleaning up..."
	rm *.o
