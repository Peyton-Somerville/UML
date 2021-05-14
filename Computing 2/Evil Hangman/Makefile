CC = gcc
CFLAGS = -Wall --std = c99
OBJECTS = main.o my_string.o generic_vector.o associative_array.o

all : string_driver unit_test

string_driver : $(OBJECTS)
	$(CC) $(CFLAGS) - o string_driver $(OBJECTS)
main.o : generic.h main.c
	$(CC) $(CFLAGS) - o generic.h - c main.c - o main.o
unit_test : my_string.o unit_test.o test_def.o
	$(CC) $(CFLAGS) - o unit_test unit_test.o test_def.o my_string.o
my_string.o : my_string.h my_string.c
	$(CC) $(CFLAGS) - o my_string.h - c my_string.c - o my_string.o
generic_vector.o : generic_vector.h generic_vector.c
	$(CC) $(CFLAGS) - o generic_vector.h - c generic_vector.c - o generic_vector.o
associative_array.o : associativearray.h associativearray.c
	$(CC) $(CFLAGS) - o associativearray.h - c associativearray.c - o associative_array.o
unit_test.o : unit_test.c
	$(CC) $(CFLAGS) - c unit_test.c - o unit_test.o
test_def.o : unit_test.h test_def.c
	$(CC) $(CFLAGS) - o unit_test.h - c test_def.c - o test_def.o
clean :
	rm string_driver unit_test unit_test.o test_def.o $(OBJECTS)
