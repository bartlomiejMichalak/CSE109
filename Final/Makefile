#makefile for final
#Bart Michalak
#CSE109.133
#summer2 2013

OBJ= node.o link.o vault.o
OPTS= -g -c -Wall -Werror

run: node
	./node
node: $(OBJ)
	g++ -o node $(OBJ)
node.o: node.cc node.h link.h vault.h
	g++ $(OPTS) node.cc
link.o: link.cc link.h vault.h node.h
	g++ $(OPTS) link.cc
vault.o: vault.cc vault.h node.h link.h
	g++ $(OPTS) vault.cc
clean:
	rm -f *.o node *~
