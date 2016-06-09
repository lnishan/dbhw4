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
➔ Reduce memory reallocations  
➔ Trade memory for speed  

* Use mostly C library  
➔ C library is oftentimes more efficient  
➔ Some C++ STLs are incredibly slow, especially `std::string` and related I/O functions

* C++11 features  
➔ Use newer functions with underlying move semantics to prevent unnecessary data copying  

* Reduce branch instructions  
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

### Results

*All the results below were tested with no compiler optimizations as was required by the course TAs*

> **Date:** 1:28 AM (UTC+8), June 10, 2016  
> **Hardware:** 50GB Vmware Disk, 4GB RAM, 1 vCore (Guest VM, Host: 1TB SSHD, 16GB RAM, i7-3770)  
> **Environment:** gcc 6.1.1, Kubuntu 16.04 LTS

| # | Import | Dry-Queries | Indexing | Queries |
| --- | --- | --- | --- | --- |
| 1 | 3.9211 | 1.1355 | 1.4272 | 0.0095 |
| 2 | 3.9237 | 1.1274 | 1.3885 | 0.0092 |
| 3 | 3.9130 | 1.1323 | 1.3955 | 0.0093 |
| 4 | 3.8863 | 1.1385 | 1.3984 | 0.0094 |
| 5 | 3.8940 | 1.1297 | 1.4066 | 0.0092 |
| **Avg.** | **3.90762** | **1.13268** | **1.40324** | **0.00932** |

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

> **Date:** 1:45 AM (UTC+8), June 10, 2016  
> **Hardware:** 16GB Persistent Disk, 3.75GB RAM, 1 HyperThread on 2.5GHz Xeon E5 v2 (Google Compute Engine n1-standard-1)  
> **Environment:** gcc 6.1.1, Ubuntu 16.04 LTS

| # | Import | Dry-Queries | Indexing | Queries |
| --- | --- | --- | --- | --- |
| 1 | 5.3151 | 1.4690 | 2.1766 | 0.0135 |
| 2 | 5.7892 | 1.4402 | 2.1010 | 0.0125 |
| 3 | 5.0392 | 1.4805 | 2.0458 | 0.0124 |
| 4 | 5.0558 | 1.4619 | 2.1203 | 0.0125 |
| 5 | 5.3348 | 1.4709 | 2.1435 | 0.0133 |
| **Avg.** | **5.30682** | **1.46450** | **2.11744** | **0.01284** |

---

> **Date:** 1:30 AM (UTC+8), June 10, 2016  
> **Hardware:** 1TB SSHD, 16GB RAM, i7-3770 (Desktop)  
> **Environment:** Cygwin-gcc 5.3.0, Windows 10 Enterprise 64-bit

| # | Import | Dry-Queries | Indexing | Queries |
| --- | --- | --- | --- | --- |
| 1 | 4.0620 | 1.2200 | 1.2650 | 0.0150 |
| 2 | 4.0470 | 1.1870 | 1.2660 | 0.0310 |
| 3 | 4.1260 | 1.2330 | 1.2670 | 0.0150 |
| 4 | 4.1260 | 1.2180 | 1.2650 | 0.0160 |
| 5 | 4.1410 | 1.2180 | 1.2660 | 0.0160 |
| **Avg.** | **4.10040** | **1.21520** | **1.26580** | **0.01860** |

---

> **Date:** 1:50 AM (UTC+8), June 10, 2016  
> **Hardware:** 256GB SSD, 16GB RAM, i5-4260U (MacBook Air Early 2014)  
> **Environment:** gcc 6.1.0, OS X El Capitan

| # | Import | Dry-Queries | Indexing | Queries |
| --- | --- | --- | --- | --- |
| 1 | 6.3953 | 1.8024 | 2.0133 | 0.0241 |
| 2 | 6.3496 | 1.8166 | 2.0211 | 0.0239 |
| 3 | 6.3017 | 1.8142 | 2.0613 | 0.0238 |
| 4 | 6.3532 | 1.8253 | 2.0229 | 0.0293 |
| 5 | 6.3219 | 1.8164 | 2.0494 | 0.0290 |
| **Avg.** | **6.34434** | **1.81498** | **2.03360** | **0.02602** |

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
