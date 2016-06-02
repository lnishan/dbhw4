#include <string>
#include <vector>
#include <cstdio>
#include <cstring>
#include <random>
#include <algorithm>



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
		char key[6];
	public:
		umap_ref();
		inline bool equal(const char[], const char[]);
		inline bool equal(const char[]);
};

class umap {
	private:
		static int TB_BITS;
		static int TB_SIZE;
		static int TB_MASK;

		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution;
		int hash_ref[6][128];
		std::vector<umap_ref> ref;
		std::vector<umap_t> data;
	public:
		typedef umap_t * iterator;
		umap();
		inline int hash(const char [], const char []); 
		inline int hash(const char []);

		iterator find(const char[], const char[]);
		inline void insert(const char [], long);
};

class db{
	private:
		char temp_dir[30];
		umap mp;
	public:
		db() {}

		void init();                                     //Do your db initialization.

		void setTempFileDir(const char []);                //All the files that created by your program should be located under this directory.

		void import(const char s[]);                        //Inport a csv file to your database.

		void createIndex();                              //Create index on one or two columns.

		double query(const char [], const char []);          //Do the query and return the average ArrDelay of flights from origin to dest.

		void cleanup();                                  //Release memory, close files and anything you should do to clean up your db class.




};
