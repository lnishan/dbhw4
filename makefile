.PHONY: clean
all: test
test: main.cpp db.cpp db.h
	g++ -std=c++11 main.cpp db.cpp -o test

O2:
	g++ -std=c++11 -O2 main.cpp db.cpp -o test_O2

clean:
	rm test
	rm test_O2
