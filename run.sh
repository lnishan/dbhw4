#! /bin/sh

if [ -n "$1" ]; then
	
	make test_$1
	
	if [ $? -eq 0 ]; then
		echo "#1"
		./test_$1;
		echo ""
		
		sleep 20;
		
		echo "#2"
		./test_$1;
		echo ""
		
		sleep 20;
	
		echo "#3"
		./test_$1;
		echo ""
		
		sleep 20;
	
		echo "#4"
		./test_$1;
		echo ""
		
		sleep 20;
	
		echo "#5"
		./test_$1;
		echo ""
	fi

else

	make test

	if [ $? -eq 0 ]; then
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

fi

