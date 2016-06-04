# dbhw4

[![Build Status](https://travis-ci.com/lnishan/dbhw4.svg?token=zyWYRz96q11zafMJcoGG&branch=master)](https://travis-ci.com/lnishan/dbhw4)

Introduction to Database, Spring 2016. Assignment 4 (Final Project)

---

The aim for this project is to implement an on-disk DBMS (Database Management System).

We are asked to perform the following query on a set of .csv files:

```SQL
SELECT AVG(ArrDelay) FROM ontime WHERE Origin = {QueryAirport1} AND Dest = {QueryAirport2};
```


## Optimization approaches

* A specialized and highly-optimized std::unordered\_map  
➔ Hash function: Simple tabulation hashing
➔ Linear probing  

* An extra-large write buffer  
➔ No need to write to the file before queries  

* Compact and uniform file format  
➔ Simple decoding to boost input efficiency  

* High reserves on std::vectors  
➔ Reduce the number of memory reallocations  
➔ Trade memory for speed  

* Use C library  
➔ Use the more efficient C library. 
➔ Some C++ STLs are incredibly slow, especially std::string and related I/O functions

* C++11 features  
➔ Use newer functions with underlying move semantics to prevent unnecessary data copying  

* Reduction of branch instructions  
➔ Eliminate branch misprediction penalties  

* Generally robust codes throughout


## Test results

> **Date:** 2:30 AM (UTC+8), June 4, 2016  
> **Environment:** 1TB SSHD, 16GB RAM, i7-3770

| # | Import | Indexing | Queries |
| --- | --- | --- | --- | --- |
| 1 | 5.907 | 4.500 | 0.015 |
| 2 | 5.875 | 4.500 | 0.032 |
| 3 | 5.953 | 4.500 | 0.015 |
| 4 | 5.891 | 4.500 | 0.016 |
| 5 | 5.986 | 4.449 | 0.031 |
| **Avg.** | **5.9224** | **4.4998** | **0.0218** |
