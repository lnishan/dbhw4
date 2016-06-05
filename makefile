.PHONY: clean
all: test test_O0 test_O1 test_O2 test_O3 res
test: main.cpp db.cpp db.h
	g++ -std=c++11 main.cpp db.cpp -o test

test_O0: main.cpp db.cpp db.h
	g++ -std=c++11 -O0 main.cpp db.cpp -o test_O0

test_O1: main.cpp db.cpp db.h
	g++ -std=c++11 -O1 main.cpp db.cpp -o test_O1

test_O2: main.cpp db.cpp db.h
	g++ -std=c++11 -O2 main.cpp db.cpp -o test_O2

test_O3: main.cpp db.cpp db.h
	g++ -std=c++11 -O3 main.cpp db.cpp -o test_O3

res: res.cpp
	g++ res.cpp -o res

clean:
	rm test || true
	rm test_O0 || true
	rm test_O1 || true
	rm test_O2 || true
	rm test_O3 || true
	rm res || true
