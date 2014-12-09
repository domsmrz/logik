
CFLAGS+= -W -Wall

logik: game.o mefisto.o mastermind.o
	g++ -o logik game.o mefisto.o mastermind.o

game.o: game.cpp mefisto.h
	g++ -c game.cpp $(CFLAGS)

mefisto.o: mefisto.cpp mefisto.h
	g++ -c mefisto.cpp $(CFLAGS)

mastermind.o: mastermind.cpp mastermind.h
	g++ -c mastermind.cpp $(CFLAGS)

clean:
	rm -f *.o
