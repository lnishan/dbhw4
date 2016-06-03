/*

The table has "NA" and empty columns,
so the correct results should be slightly higher than below

+---------------+
| AVG(ArrDelay) |
+---------------+
|       16.9388 |
|       11.4326 |
|       11.0744 |
|       12.3813 |
|        7.1389 |
+---------------+
5 rows in set (1 min 30.72 sec)

*/

(SELECT AVG(ArrDelay) FROM `ontime` WHERE Origin='IAH' AND Dest='JFK') UNION
(SELECT AVG(ArrDelay) FROM `ontime` WHERE Origin='IAH' AND Dest='LAX') UNION
(SELECT AVG(ArrDelay) FROM `ontime` WHERE Origin='JFK' AND Dest='LAX') UNION
(SELECT AVG(ArrDelay) FROM `ontime` WHERE Origin='JFK' AND Dest='IAH') UNION
(SELECT AVG(ArrDelay) FROM `ontime` WHERE Origin='LAX' AND Dest='IAH')

