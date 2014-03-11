#Makefile for p2.cc
#put your name here
#CSE 109
#Spring 2013

OBJ= p2.o hashTable.o hash.o
p2: $(OBJ)
	g++ -o p2 $(OBJ)

p2.o: p2.cc
	g++ -c -Wall -Werror p2.cc
hashTable.o: hashTable.cc hashTable.h
	g++ -c -Wall -Werror hashTable.cc
hash.o: hash.cc hash.h
	g++ -c -Wall -Werror hash.cc
clean:
	rm -f *~ *.o p2
