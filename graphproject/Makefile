search-cli: main.o stats.o search.o
	cc -o search-cli main.o stats.o search.o

main.o: main.c stats.h search.h
	cc -c main.c search.h stats.h

stats.o: stats.c stats.h
	cc -c stats.c stats.h

search.o: search.c search.h
	cc -c search.c search.h

clean:
	rm *.o *.gch
