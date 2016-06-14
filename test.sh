#! /bin/sh

if [ -n "$1" ]; then
	binary="test_$1"
else
	binary="test"
fi

printf "* Building binaries ... "
make $binary > last_build.log 2>&1
if [ ! $? -eq 0 ]; then
	echo "Error"
	cat last_build.log
	echo "* An error has occurred! Aborting ..."
	exit
else
	echo "Done"
fi


if [ -z "$2" ]; then
	echo "* Starting dry-runs ..."
	printf "1 ... "
	./$binary > /dev/null 2>&1
	printf "2 ... "
	./$binary > /dev/null 2>&1
	echo "OK"
fi


echo "* Starting test ..."
if [ -n "$1" ]; then
	./run.sh $1 | tee res_raw.txt
else
	./run.sh | tee res_raw.txt
fi

make res > /dev/null 2>&1
./res res_raw.txt | tee res.txt

