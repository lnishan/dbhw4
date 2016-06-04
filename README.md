# dbhw4

Introduction to Database, Spring 2016. Assignment 4 (Final Project)

[![Build Status](https://travis-ci.com/lnishan/dbhw4.svg?token=zyWYRz96q11zafMJcoGG&branch=master)](https://travis-ci.com/lnishan/dbhw4)

---


## Goals

Implement an on-disk DBMS (Database Management System).

Perform the following query on a set of .csv files:

```SQL
SELECT AVG(ArrDelay) FROM ontime WHERE Origin = {QueryAirport1} AND Dest = {QueryAirport2};
```


## Datasets

Data expo '09, *ASA Sections on Statistical Computing* 

* [2006.csv](http://stat-computing.org/dataexpo/2009/2006.csv.bz2)  
* [2007.csv](http://stat-computing.org/dataexpo/2009/2007.csv.bz2)  
* [2008.csv](http://stat-computing.org/dataexpo/2009/2008.csv.bz2)

`2160486` rows, `29` columns


## Requirements

* 2GB RAM
* gcc 4.8.4
* No custom makefiles
* No parallelization
* No pre-calculations
* No data can be stored in memory before queries


## Optimizations

* A specialized and highly-optimized hash map  
➔ Simple tabulation hashing  
➔ Linear probing  

* An extra-large read buffer  
➔ Reduce system call overheads

* An extra-large write buffer  
➔ No need to write to the file before queries  
➔ Reduce system call overheads

* Compact and uniform file format  
➔ Simple decoding to boost input efficiency  

* High reserves on std::vectors  
➔ Reduce the number of memory reallocations  
➔ Trade memory for speed  

* Use mostly C library  
➔ C library is oftentimes more efficient.  
➔ Some C++ STLs are incredibly slow, especially std::string and related I/O functions

* C++11 features  
➔ Use newer functions with underlying move semantics to prevent unnecessary data copying  

* Reduction of branch instructions  
➔ Eliminate branch misprediction penalties  

* Generally robust codes throughout


## Test Results

### Queries

```cpp
double result1 = mydb.query("IAH", "JFK");
double result2 = mydb.query("IAH", "LAX");
double result3 = mydb.query("JFK", "LAX");
double result4 = mydb.query("JFK", "IAH");
double result5 = mydb.query("LAX", "IAH");
```

---

> **Date:** 10:00 PM (UTC+8), June 4, 2016  
> **Hardware:** 16GB Persistent Disk, 3.75GB RAM, 2.5GHz Xeon E5 v2 (Google Compute Engine n1-standard-1)  
> **Environment:** gcc 5.3.1, Ubuntu 16.04 LTS

| # | Import | Indexing | Dry-Queries | Queries |
| --- | --- | --- | --- | --- |
| 1 | 7.6948 | 3.9534 | 3.3412 | 0.0128 |
| 2 | 6.7874 | 4.0147 | 3.3852 | 0.0130 |
| 3 | 6.4664 | 3.9750 | 3.3857 | 0.0128 |
| 4 | 6.2885 | 3.9403 | 3.3141 | 0.0129 |
| 5 | 6.3292 | 3.9159 | 3.3592 | 0.0129 |
| **Avg.** | **6.71326** | **3.95986** | **3.35708** | **0.01288** |

---

> **Date:** 10:00 PM (UTC+8), June 4, 2016  
> **Hardware:** 1TB SSHD, 16GB RAM, i7-3770  
> **Environment:** Cygwin-gcc 5.3.0, Windows 10 Enterprise 64-bit

| # | Import | Indexing | Dry-Queries | Queries |
| --- | --- | --- | --- | --- |
| 1 | 5.0160 | 4.5470 | 10.3590 | 0.0320 |
| 2 | 5.0470 | 4.5480 | 10.3740 | 0.0150 |
| 3 | 5.0470 | 4.5620 | 10.3280 | 0.0320 |
| 4 | 5.0930 | 4.5620 | 10.3760 | 0.0160 |
| 5 | 5.0160 | 4.5630 | 10.3900 | 0.0150 |
| **Avg.** | **5.04380** | **4.55640** | **10.36540** | **0.02200** |

---

