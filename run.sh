#! /bin/sh

if [ -n "$1" ]; then
	
	make test_$1
	
	if [ $? -eq 0 ]; then
		echo "#1"
		sudo nice -n -20 ./test_$1;
		echo ""
		
		sleep 20;
		
		echo "#2"
		sudo nice -n -20 ./test_$1;
		echo ""
		
		sleep 20;
	
		echo "#3"
		sudo nice -n -20 ./test_$1;
		echo ""
		
		sleep 20;
	
		echo "#4"
		sudo nice -n -20 ./test_$1;
		echo ""
		
		sleep 20;
	
		echo "#5"
		sudo nice -n -20 ./test_$1;
		echo ""
	fi

else

	make test

	if [ $? -eq 0 ]; then
		echo "#1"
		sudo nice -n -20 ./test;
		echo ""
		
		sleep 20;
		
		echo "#2"
		sudo nice -n -20 ./test;
		echo ""
		
		sleep 20;
	
		echo "#3"
		sudo nice -n -20 ./test;
		echo ""
		
		sleep 20;
	
		echo "#4"
		sudo nice -n -20 ./test;
		echo ""
		
		sleep 20;
	
		echo "#5"
		sudo nice -n -20 ./test;
		echo ""
	fi

fi

