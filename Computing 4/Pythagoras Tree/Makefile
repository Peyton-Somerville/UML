CC = g++
CFLAGS = -Wall -Werror -ansi -pedantic
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
BOOST = -lboost_unit_test_framework
OBJECTS = PTree.o main.o

all: tree

tree: $(OBJECTS)
	$(CC) $(OBJECTS) -o tree $(LFLAGS)

PTree.o:PTree.cpp PTree.hpp
	$(CC) -c PTree.cpp $(CFLAGS)

main.o:main.cpp PTree.hpp
	$(CC) -c main.cpp PTree.hpp $(LFLAGS)

clean:
	rm $(OBJECTS) tree *\~
