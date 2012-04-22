all:
	g++ parser.cpp main.cpp -o parser-tests 

clean:
	rm parser-tests
