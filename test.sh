#! /bin/sh

if [ "$1" = "O2" ]; then
	./run.sh O2 | tee res_raw.txt
else
	./run.sh | tee res_raw.txt
fi

make res
./res res_raw.txt | tee res.txt

