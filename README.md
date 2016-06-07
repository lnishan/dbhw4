# dbhw4

Introduction to Database, Spring 2016. Assignment 4 (Final Project)

[![Build Status](https://travis-ci.com/lnishan/dbhw4.svg?token=zyWYRz96q11zafMJcoGG&branch=master)](https://travis-ci.com/lnishan/dbhw4)

---


## Goals

Implement an on-disk DBMS (Database Management System)

Perform the following query on a set of .csv files:

```sql
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


## Installation

Dependencies: 

* g++ 4.8.4 or newer  
* make

Tested on Windows, Mac OSX, Ubuntu and FreeBSD

```bash
# Clone the repo
git clone https://github.com/lnishan/dbhw4.git
cd dbhw4

# Download dataset
# Prerequisites: wget, bzip2
./download.sh

# Build and run
# O0 - O3 are all supported
# O0, if no argument is passed in
./run.sh O2

# Build, run and organize results
# O0 - O3 are all supported
# O0, if no argument is passed in
./test.sh O2
```


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
➔ C library is oftentimes more efficient  
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

> **Date:** 10:04 PM (UTC+8), June 5, 2016  
> **Hardware:** 50GB Vmware Disk, 4GB RAM, 1 vCore (Guest VM, Host: 1TB SSHD, 16GB RAM, i7-3770)  
> **Environment:** gcc 6.1.1, Kubuntu 16.04 LTS

| # | Import | Dry-Queries | Indexing | Queries |
| --- | --- | --- | --- | --- |
| 1 | 5.0591 | 2.5504 | 1.5239 | 0.0102 |
| 2 | 5.0596 | 2.5819 | 1.5379 | 0.0109 |
| 3 | 5.0173 | 2.5818 | 1.5377 | 0.0102 |
| 4 | 5.0464 | 2.5667 | 1.5388 | 0.0106 |
| 5 | 5.0428 | 2.5797 | 1.5409 | 0.0104 |
| **Avg.** | **5.04504** | **2.57210** | **1.53584** | **0.01046** |

---

> **Date:** 10:20 PM (UTC+8), June 5, 2016  
> **Hardware:** 30GB Vmware Disk, 4GB RAM, 1 vCore (Guest VM, Host: 1TB SSHD, 16GB RAM, i7-3770)  
> **Environment:** gcc 6.0.0, FreeBSD 10.3-RELEASE

| # | Import | Dry-Queries | Indexing | Queries |
| --- | --- | --- | --- | --- |
| 1 | 6.1250 | 2.8438 | 4.4141 | 0.0156 |
| 2 | 6.6094 | 2.8750 | 2.8438 | 0.0156 |
| 3 | 6.1328 | 2.8047 | 2.0469 | 0.0078 |
| 4 | 5.6172 | 2.8828 | 1.8750 | 0.0078 |
| 5 | 5.6094 | 2.8750 | 1.9688 | 0.0156 |
| **Avg.** | **6.01876** | **2.85626** | **2.62972** | **0.01248** |

---

> **Date:** 9:27 PM (UTC+8), June 5, 2016  
> **Hardware:** 16GB Persistent Disk, 3.75GB RAM, 1 HyperThread on 2.5GHz Xeon E5 v2 (Google Compute Engine n1-standard-1)  
> **Environment:** gcc 6.1.1, Ubuntu 16.04 LTS

| # | Import | Dry-Queries | Indexing | Queries |
| --- | --- | --- | --- | --- |
| 1 | 7.5888 | 3.3500 | 2.2967 | 0.0142 |
| 2 | 6.5242 | 3.3196 | 2.1399 | 0.0138 |
| 3 | 6.4446 | 3.2704 | 2.1605 | 0.0132 |
| 4 | 7.1480 | 3.2698 | 2.2136 | 0.0133 |
| 5 | 6.8839 | 3.2607 | 2.1868 | 0.0132 |
| **Avg.** | **6.91790** | **3.29410** | **2.19950** | **0.01354** |

---

> **Date:** 1:51 PM (UTC+8), June 5, 2016  
> **Hardware:** 1TB SSHD, 16GB RAM, i7-3770 (Desktop)  
> **Environment:** Cygwin-gcc 5.3.0, Windows 10 Enterprise 64-bit

| # | Import | Dry-Queries | Indexing | Queries |
| --- | --- | --- | --- | --- |
| 1 | 5.2660 | 2.5940 | 1.4520 | 0.0160 |
| 2 | 5.2340 | 2.6260 | 1.4690 | 0.0150 |
| 3 | 5.1410 | 2.5930 | 1.4530 | 0.0320 |
| 4 | 5.2500 | 2.5930 | 1.4530 | 0.0150 |
| 5 | 5.2660 | 2.6240 | 1.4540 | 0.0160 |
| **Avg.** | **5.23140** | **2.60600** | **1.45620** | **0.01880** |

---

> **Date:** 8:04 PM (UTC+8), June 6, 2016  
> **Hardware:** 256GB SSD, 16GB RAM, i5-4260U (MacBook Air Early 2014)  
> **Environment:** gcc 6.1.0, OS X El Capitan

| # | Import | Dry-Queries | Indexing | Queries |
| --- | --- | --- | --- | --- |
| 1 | 7.0012 | 3.7901 | 2.2860 | 0.0244 |
| 2 | 6.5074 | 3.8640 | 2.3244 | 0.0246 |
| 3 | 6.4885 | 3.8454 | 2.3501 | 0.0243 |
| 4 | 6.4507 | 3.8420 | 2.3081 | 0.0297 |
| 5 | 6.3784 | 3.8894 | 2.3294 | 0.0247 |
| **Avg.** | **6.56524** | **3.84618** | **2.31960** | **0.02554** |

---

> **Date:** 10:33 PM (UTC+8), June 5, 2016  
> **Hardware:** 1TB SSHD, 16GB RAM, i7-3770 (Desktop)  
> **Environment:** Visual Studio 2015, Windows 10 Enterprise 64-bit

| # | Import | Dry-Queries | Indexing | Queries |
| --- | --- | --- | --- | --- |
| 1 | 5.5300 | 2.6540 | 0.5610 | 0.0680 |
| 2 | 5.5040 | 2.6500 | 0.5600 | 0.0670 |
| 3 | 5.5570 | 2.6350 | 0.5390 | 0.0680 |
| 4 | 5.5470 | 2.6480 | 0.5610 | 0.0670 |
| 5 | 5.5220 | 2.6550 | 0.5590 | 0.0670 |
| **Avg.** | **5.53200** | **2.64840** | **0.55600** | **0.06740** |

---
