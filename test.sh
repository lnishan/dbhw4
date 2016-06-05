#! /bin/sh

if [ -n "$1" ]; then
	./run.sh $1 | tee res_raw.txt
else
	./run.sh | tee res_raw.txt
fi

make res
./res res_raw.txt | tee res.txt

