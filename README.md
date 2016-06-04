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

**21604865** rows (21134119 valid), **29** columns


## Requirements

* Test Environment: 2GB RAM, gcc 4.8.4, Ubuntu 14.04 LTS
* No custom makefiles
* No parallelization
* No pre-calculations
* No data can be stored in memory before queries


## Optimizations

* A specialized and highly-optimized hash map  
➔ Simple tabulation hashing  
➔ Linear probing  

* An extra-large read buffer  
➔ Applicable to both import and indexing
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

> **Date:** 3:30 AM (UTC+8), June 5, 2016  
> **Hardware:** 16GB SSD, 3.75GB RAM, 2.5GHz Xeon E5 v2 (Google Compute Engine n1-standard-1)  
> **Environment:** gcc 5.3.1, Ubuntu 16.04 LTS

| # | Import | Dry-Queries | Indexing | Queries |
| --- | --- | --- | --- | --- |
| 1 | 6.7414 | 3.2953 | 2.2090 | 0.0140 |
| 2 | 6.9793 | 3.2584 | 2.1799 | 0.0127 |
| 3 | 6.5395 | 3.2409 | 2.1548 | 0.0127 |
| 4 | 6.4859 | 3.2570 | 2.1941 | 0.0128 |
| 5 | 7.0782 | 3.3148 | 2.2021 | 0.0135 |
| **Avg.** | **6.76486** | **3.27328** | **2.18798** | **0.01314** |

---

> **Date:** 3:30 AM (UTC+8), June 5, 2016  
> **Hardware:** 1TB SSHD, 16GB RAM, i7-3770  
> **Environment:** Cygwin-gcc 5.3.0, Windows 10 Enterprise 64-bit (Desktop)

| # | Import | Dry-Queries | Indexing | Queries |
| --- | --- | --- | --- | --- |
| 1 | 5.2660 | 2.6250 | 1.4840 | 0.0160 |
| 2 | 5.2500 | 2.6100 | 1.4680 | 0.0160 |
| 3 | 5.2030 | 2.6090 | 1.4840 | 0.0160 |
| 4 | 5.1880 | 2.6090 | 1.4840 | 0.0160 |
| 5 | 5.1880 | 2.6240 | 1.4700 | 0.0300 |
| **Avg.** | **5.21900** | **2.61540** | **1.47800** | **0.01880** |

---

> **Date:** 3:30 AM (UTC+8), June 5, 2016  
> **Hardware:** 256GB SSD, 16GB RAM, i5-4260U  
> **Environment:** gcc 5.3.0, OS X El Capitan (MacBook Air Early 2014)

| # | Import | Dry-Queries | Indexing | Queries |
| --- | --- | --- | --- | --- |
| 1 | 7.8163 | 3.8534 | 2.5339 | 0.0248 |
| 2 | 7.8578 | 3.7656 | 2.4520 | 0.0250 |
| 3 | 7.8902 | 3.8387 | 2.4401 | 0.0250 |
| 4 | 7.9061 | 3.7831 | 2.4521 | 0.0302 |
| 5 | 7.8536 | 3.7653 | 2.4195 | 0.0286 |
| **Avg.** | **7.86480** | **3.80122** | **2.45952** | **0.02672** |

---
