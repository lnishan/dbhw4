#include <iostream>
#include <time.h>
#include "db.h"

using namespace std;

int main(int argc, char* argv[]){
	//declear db object
	db mydb;

	//init db
	mydb.init();

	//set temp directory
	mydb.setTempFileDir("temp");

	//Import data
	clock_t tImport = clock();
	mydb.import("data/2006.csv");
	mydb.import("data/2007.csv");
	mydb.import("data/2008.csv");
	double import_time = (double)(clock() - tImport) / CLOCKS_PER_SEC;
	
	//Query without index
	clock_t tNoIdxQuery = clock();
	/*double noidx_result1 = mydb.query("IAH", "JFK");
	double noidx_result2 = mydb.query("IAH", "LAX");
	double noidx_result3 = mydb.query("JFK", "LAX");
	double noidx_result4 = mydb.query("JFK", "IAH");
	double noidx_result5 = mydb.query("LAX", "IAH");*/
	double noidx_query_time = (double)(clock() - tNoIdxQuery) / CLOCKS_PER_SEC;
	
	//Create index on one or two columns.
	clock_t tIndex = clock();
	mydb.createIndex();
	double index_time = (double)(clock() - tIndex) / CLOCKS_PER_SEC;

	//Do queries
	//These queries are required in your report.
	//We will do different queries in the contest.
	//Start timing
	clock_t tQuery = clock();
	double result1 = mydb.query("IAH", "JFK");
	double result2 = mydb.query("IAH", "LAX");
	double result3 = mydb.query("JFK", "LAX");
	double result4 = mydb.query("JFK", "IAH");
	double result5 = mydb.query("LAX", "IAH");

	//End timing
	double query_time = (double)(clock() - tQuery) / CLOCKS_PER_SEC;
	
	//printf("Results (pre-indexing): %.4f %.4f %.4f %.4f %.4f\n", noidx_result1, noidx_result2, noidx_result3, noidx_result4, noidx_result5);
	printf("Results: %.4f %.4f %.4f %.4f %.4f\n", result1, result2, result3, result4, result5);
	
	printf("Time taken for import: %.4fs\n", import_time);
	printf("Time taken for indexing: %.4fs\n", index_time);
	printf("Time taken for queries (pre-indexing): %.4fs\n", noidx_query_time);
	printf("Time taken for queries: %.4fs\n", query_time);

	//Cleanup db object
	mydb.cleanup();
}
