#! /bin/sh

make
make O2

if [ "$1" = "O2" ]; then
	./test_O2; sleep 20; ./test_O2; sleep 20; ./test_O2; sleep 20; ./test_O2; sleep 20; ./test_O2; sleep 20;
else
	./test; sleep 20; ./test; sleep 20; ./test; sleep 20; ./test; sleep 20; ./test; sleep 20;
fi

