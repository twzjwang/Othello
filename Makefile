all: main.c game.o
	gcc -o main main.c game.o

game.o: game.c game.h
	gcc -c game.c

clean:
	rm *.o main
