FLAGS = -g -Wall -Werror -ansi

all: cargs-tests
 
cargs-tests: lib
	g++ $(FLAGS) -static main.cpp -o cargs-tests -L. -lcargs

cargs.o:
	g++ $(FLAGS) -c cargs.cpp -o cargs.o

lib: cargs.o
	ar rcs libcargs.a cargs.o

clean:
	rm cargs-tests cargs.o libcargs.a
