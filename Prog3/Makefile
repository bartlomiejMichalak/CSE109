#Makefile for lex.cc
#Bart Michalak
#CSE 109
#Spring 2013

OBJ= lex.o token.o myMain.o
myMain: $(OBJ)
	g++ -o myMain $(OBJ)

myMain.o: myMain.cc lex.h token.h
	g++ -c -Wall -Werror myMain.cc
lex.o: lex.cc lex.h token.h
	g++ -c -Wall -Werror lex.cc
token.o: token.cc token.h
	g++ -c -Wall -Werror token.cc
clean:
	rm -f *~ *.o main
