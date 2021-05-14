CC = g++
CFLAGS = -Wall -Werror -ansi -pedantic
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
BOOST = -lboost_unit_test_framework
OBJECTS = NBody.o main.o

all: NBody

NBody: $(OBJECTS)
	$(CC) $(OBJECTS) -o NBody $(LFLAGS)

NBody.o:NBody.cpp NBody.hpp
	$(CC) -c NBody.cpp $(CFLAGS)

main.o:main.cpp NBody.hpp
	$(CC) -c main.cpp NBody.hpp $(LFLAGS)

clean:
	rm $(OBJECTS) tree *\~
