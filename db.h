#include <string>
#include <vector>
#include <cstdio>
#include <cstring>
#include <random>
#include <algorithm>

#define TB_SIZE 65536

class umap_t {
	friend class umap;
	private:
	public:
		umap_t();
		std::vector<long> pos;
};

class umap_ref {
	friend class umap;
	private:
		char used;
		char key[2][3];
	public:
		umap_ref();
		inline bool equal(const char[], const char[]);
};

class umap {
	public:
	// private:
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution;
		int hash_ref[6][128];
		std::vector<umap_ref> ref;
		std::vector<umap_t> data;
	// public:
		typedef umap_t * iterator;
		umap();
		inline int hash(const char [], const char []); 
		inline int hash(const char &, const char &, const char &, const char &, const char &, const char &);

		iterator find(const char[], const char[]);
		void insert(const char [], const char [], long);
};

class db{
	private:
		std::string temp_dir;
		umap mp;
	public:
		db() {}

		void init();                                     //Do your db initialization.

		void setTempFileDir(const std::string &);                //All the files that created by your program should be located under this directory.

		void import(const char s[]);                        //Inport a csv file to your database.

		void createIndex();                              //Create index on one or two columns.

		double query(const char [], const char []);          //Do the query and return the average ArrDelay of flights from origin to dest.

		void cleanup();                                  //Release memory, close files and anything you should do to clean up your db class.




};
