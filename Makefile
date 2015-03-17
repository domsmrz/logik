
CFLAGS+= -W -Wall -g

logik: game.o mefisto.o mastermind.o readint.o
	g++ -o logik game.o mefisto.o mastermind.o readint.o

game.o: game.cpp mefisto.h readint.h
	g++ -c game.cpp $(CFLAGS)

mefisto.o: mefisto.cpp mefisto.h readint.h
	g++ -c mefisto.cpp $(CFLAGS)

mastermind.o: mastermind.cpp mastermind.h readint.h
	g++ -c mastermind.cpp $(CFLAGS)

readint.o: readint.cpp
	g++ -c readint.cpp $(CFLAGS)

clean:
	rm -f *.o logik
