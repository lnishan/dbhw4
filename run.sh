#! /bin/sh

make
make test_O2

if [ "$1" = "O2" ]; then
	
	echo "#1"
	./test_O2;
	echo ""
	
	sleep 20;
	
	echo "#2"
	./test_O2;
	echo ""
	
	sleep 20;

	echo "#3"
	./test_O2;
	echo ""
	
	sleep 20;

	echo "#4"
	./test_O2;
	echo ""
	
	sleep 20;

	echo "#5"
	./test_O2;
	echo ""

else
	
	echo "#1"
	./test;
	echo ""
	
	sleep 20;
	
	echo "#2"
	./test;
	echo ""
	
	sleep 20;

	echo "#3"
	./test;
	echo ""
	
	sleep 20;

	echo "#4"
	./test;
	echo ""
	
	sleep 20;

	echo "#5"
	./test;
	echo ""

fi

