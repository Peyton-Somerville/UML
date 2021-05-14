CC = g++
CFLAGS = -Wall -Werror -ansi -pedantic -std=c++11
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
BOOST = -lboost_unit_test_framework
OBJECTS = ED.o main.o

all: ED

ED: $(OBJECTS)
	$(CC) $(OBJECTS) -o ED $(LFLAGS)

ED.o:ED.cpp ED.hpp
	$(CC) -c ED.cpp $(CFLAGS)

main.o:main.cpp ED.hpp
	$(CC) -c main.cpp ED.hpp $(LFLAGS)

clean:
	rm $(OBJECTS) ED *\~
