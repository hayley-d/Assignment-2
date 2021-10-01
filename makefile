 

# target: prerequisite 1 prerequisite 2 prerequisite 3

#<TAB>shell command(s)

 

prac: main.o piece.o board.o

       g++ -o prac main.o piece.o board.o

 

main.o: main.cpp

       g++ -c main.cpp

 

 

piece.o: piece.cpp

       g++ -c piece.cpp

 

 

board.o: board.cpp

       g++ -c board.cpp
 

 

clean:

       @echo "Start afresh.."

       rm -rfv *.o prac

 

 

run:

       ./prac
