#Makefile for parser.cc
#Bart Michalak
#CSE 109
#Spring 2013

OBJ= lex.o token.o silc.o parser.o

silc: $(OBJ)
	g++ -o silc $(OBJ)
silc.o: silc.cc lex.h parser.h token.h
	g++ -c -Wall -Werror silc.cc
lex.o: lex.cc lex.h token.h
	g++ -c -Wall -Werror lex.cc
parser.o: parser.h token.h lex.h
	g++ -c -Wall -Werror parser.cc
token.o: token.cc token.h
	g++ -c -Wall -Werror token.cc
clean:
	rm -f *~ *.o silc
