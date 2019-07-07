search-cli: main.o stats.o search.o mytools.o
	cc -o search-cli main.o stats.o search.o mytools.o

main.o: main.c stats.h search.h mytools.h
	cc -c main.c search.h stats.h mytools.h

stats.o: stats.c stats.h mytools.h
	cc -c stats.c stats.h mytools.h

search.o: search.c search.h mytools.h
	cc -c search.c search.h mytools.h

mytools.o: mytools.c mytools.h
	cc -c mytools.c mytools.h

clean:
	rm *.o *.gch
