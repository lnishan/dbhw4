#! /bin/sh

cd data
wget http://stat-computing.org/dataexpo/2009/2006.csv.bz2
wget http://stat-computing.org/dataexpo/2009/2007.csv.bz2
wget http://stat-computing.org/dataexpo/2009/2008.csv.bz2

bzip2 -d *.csv.bz2

rm *.csv.bz2
