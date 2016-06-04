.PHONY: clean
all: test test_O2 res
test: main.cpp db.cpp db.h
	g++ -std=c++11 main.cpp db.cpp -o test

test_O2: main.cpp db.cpp db.h
	g++ -std=c++11 -O2 main.cpp db.cpp -o test_O2

res: res.cpp
	g++ res.cpp -o res

clean:
	rm test
	rm test_O2
