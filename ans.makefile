.PHONY: clean
all: test_ans
test_ans: main_ans.cpp db.cpp db.h
	g++ -std=c++11 -O2 main_ans.cpp db.cpp -o test_ans

clean:
	rm test_ans
