chess: piece.o main.o
    g++ -std=c++98 -static piece.o main.o -o chess

piece.o: piece.cpp piece.h
    g++ -c -std=c++98 -static piece.cpp

main.o: main.cpp piece.h
    g++ -c -std=c++98 -static main.cpp

run: chess
	./chess

clean:
    rm *.o chess
