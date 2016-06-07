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

Tested on `Windows`, `Mac OSX`, `Ubuntu` and `FreeBSD`

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

* A specialized and highly-optimized `hash map`  
➔ Simple tabulation hashing  
➔ Linear probing  

* An extra-large `read buffer`  
➔ Applicable to both import and indexing  
➔ Reduce system call overheads

* An extra-large `write buffer`  
➔ No need to write to the file before queries  
➔ Reduce system call overheads

* Compact and uniform file format  
➔ Simple decoding to boost input efficiency  

* High reserves on `std::vectors`  
➔ Reduce the number of memory reallocations  
➔ Trade memory for speed  

* Use mostly C library  
➔ C library is oftentimes more efficient  
➔ Some C++ STLs are incredibly slow, especially `std::string` and related I/O functions

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

### Efficiency

All the results below were tested with no optimizations

> **Date:** 12:48 PM (UTC+8), June 6, 2016  
> **Hardware:** 50GB Vmware Disk, 4GB RAM, 1 vCore (Guest VM, Host: 1TB SSHD, 16GB RAM, i7-3770)  
> **Environment:** gcc 6.1.1, Kubuntu 16.04 LTS

| # | Import | Dry-Queries | Indexing | Queries |
| --- | --- | --- | --- | --- |
| 1 | 4.0196 | 2.5405 | 1.5406 | 0.0103 |
| 2 | 4.0280 | 2.5240 | 1.5234 | 0.0105 |
| 3 | 4.0153 | 2.5587 | 1.5363 | 0.0104 |
| 4 | 4.0175 | 2.5426 | 1.5262 | 0.0103 |
| 5 | 4.0180 | 2.5267 | 1.5267 | 0.0102 |
| **Avg.** | **4.01968** | **2.53850** | **1.53064** | **0.01034** |

---

> **Date:** 6:15 PM (UTC+8), June 6, 2016  
> **Hardware:** 30GB Vmware Disk, 4GB RAM, 1 vCore (Guest VM, Host: 1TB SSHD, 16GB RAM, i7-3770)  
> **Environment:** gcc 6.0.0, FreeBSD 10.3-RELEASE

| # | Import | Dry-Queries | Indexing | Queries |
| --- | --- | --- | --- | --- |
| 1 | 4.2734 | 2.6953 | 1.7109 | 0.0156 |
| 2 | 4.2891 | 2.6875 | 1.6406 | 0.0078 |
| 3 | 4.3203 | 2.6797 | 1.6172 | 0.0156 |
| 4 | 4.2656 | 2.6875 | 1.5938 | 0.0156 |
| 5 | 4.2812 | 2.6797 | 1.5938 | 0.0078 |
| **Avg.** | **4.28592** | **2.68594** | **1.63126** | **0.01248** |

---

> **Date:** 3:00 PM (UTC+8), June 6, 2016  
> **Hardware:** 16GB Persistent Disk, 3.75GB RAM, 1 HyperThread on 2.5GHz Xeon E5 v2 (Google Compute Engine n1-standard-1)  
> **Environment:** gcc 6.1.1, Ubuntu 16.04 LTS

| # | Import | Dry-Queries | Indexing | Queries |
| --- | --- | --- | --- | --- |
| 1 | 5.2837 | 3.2539 | 2.1433 | 0.0146 |
| 2 | 5.3988 | 3.3728 | 2.1925 | 0.0137 |
| 3 | 5.8694 | 3.3713 | 2.2950 | 0.0144 |
| 4 | 5.6308 | 3.3184 | 2.2064 | 0.0130 |
| 5 | 5.2643 | 3.2700 | 2.1723 | 0.0134 |
| **Avg.** | **5.48940** | **3.31728** | **2.20190** | **0.01382** |

---

> **Date:** 4:09 PM (UTC+8), June 6, 2016  
> **Hardware:** 1TB SSHD, 16GB RAM, i7-3770 (Desktop)  
> **Environment:** Cygwin-gcc 5.3.0, Windows 10 Enterprise 64-bit

| # | Import | Dry-Queries | Indexing | Queries |
| --- | --- | --- | --- | --- |
| 1 | 4.2180 | 2.6100 | 1.4060 | 0.0310 |
| 2 | 4.1720 | 2.6250 | 1.4380 | 0.0160 |
| 3 | 4.1880 | 2.5940 | 1.4380 | 0.0160 |
| 4 | 4.2190 | 2.5940 | 1.4370 | 0.0150 |
| 5 | 4.2190 | 2.6250 | 1.4380 | 0.0150 |
| **Avg.** | **4.20320** | **2.60960** | **1.43140** | **0.01860** |

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

> **Date:** 4:13 PM (UTC+8), June 6, 2016  
> **Hardware:** 1TB SSHD, 16GB RAM, i7-3770 (Desktop)  
> **Environment:** Visual Studio 2015, Windows 10 Enterprise 64-bit

| # | Import | Dry-Queries | Indexing | Queries |
| --- | --- | --- | --- | --- |
| 1 | 5.3940 | 2.6460 | 0.5550 | 0.0680 |
| 2 | 5.3290 | 2.6230 | 0.5600 | 0.0690 |
| 3 | 5.2600 | 2.6130 | 0.5550 | 0.0660 |
| 4 | 5.2900 | 2.6140 | 0.5340 | 0.0660 |
| 5 | 5.2760 | 2.6160 | 0.5530 | 0.0670 |
| **Avg.** | **5.30980** | **2.62240** | **0.55140** | **0.06720** |

---
