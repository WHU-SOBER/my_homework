main: main.o ai.o file.o game.o view.o
	gcc -o main main.o ai.o file.o game.o view.o

file_test: file_test.o file.o game.o
	gcc -o file_test file_test.o file.o game.o

game_test: game_test.o game.o
	gcc -o game_test game_test.o  game.o

main.o: main.c ai.h file.h game.h view.h
	gcc -c main.c file.h game.h view.h

file_test.o: file_test.c file.h game.h
	gcc -c file_test.c file.h game.h -lm

game_test.o: game_test.c game.h
	gcc -c game_test.c game.h

file.o: file.c file.h game.h
	gcc -c file.c file.h game.h

game.o: game.c game.h
	gcc -c game.c game.h

ai.o: ai.c ai.h
	gcc -c  ai.c ai.h

view.o: view.c view.h
	gcc -c view.c view.h
clean:
	rm *.o *.gch
