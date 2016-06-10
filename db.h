#include <string>
#include <cstdio>
#include <cstring>
#include <random>
#include <algorithm>
#include <utility>

#ifndef LNI_VECTOR
#define LNI_VECTOR

namespace lni {

	template <typename T>
	class vector {
		public:
			vector();
			vector(std::initializer_list<T> &&);
			~vector();
			typedef T *iterator;
			inline T & operator [](const int &);

			iterator begin();
			iterator end();
			T & front();
			T & back();

			int size();
			bool empty();
			void push_back(const T &);
			void pop_back();
			void emplace_back(T &&);
			void reserve(const int &);
			void resize(const int &);
			void clear();
			void swap(lni::vector<T> &);
		private:
			int rsrv_sz = 4;
			int vec_sz = 0;
			T *arr;

			inline void reallocate();
	};

}

// #include "vector.cpp"


namespace lni {

	template <typename T>
	vector<T>::vector() {
		arr = new T[rsrv_sz];
	}

	template <typename T>
	vector<T>::vector(std::initializer_list<T> &&lst) {
		rsrv_sz = lst.size() << 2;
		arr = new T[rsrv_sz];
		for (auto &item: lst)
			arr[vec_sz++] = item;
	}

	template <typename T>
	vector<T>::~vector() {
		delete [] arr;
	}

	template <typename T>
	inline T & vector<T>::operator [](const int &idx) {
		return arr[idx];
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::begin() {
		return arr;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::end() {
		return arr + vec_sz;
	}

	template <typename T>
	T & vector<T>::front() {
		return arr[0];
	}

	template <typename T>
	T & vector<T>::back() {
		return arr[vec_sz - 1];
	}

	template <typename T>
	inline void vector<T>::reallocate() {
		int i;
		T *tarr = new T[rsrv_sz];
		for (i = 0; i < vec_sz; ++i)
			tarr[i] = arr[i];
		delete [] arr;
		arr = tarr;
	}
	
	template <typename T>
	int vector<T>::size() {
		return vec_sz;
	}

	template <typename T>
	bool vector<T>::empty() {
		return vec_sz == 0;
	}

	template <typename T>
	void vector<T>::push_back(const T &val) {
		if (vec_sz == rsrv_sz) {
			rsrv_sz <<= 2;
			reallocate();
		}
		arr[vec_sz] = val;
		++vec_sz;
	}

	template <typename T>
	void vector<T>::pop_back() {
		--vec_sz;
		arr[vec_sz].~T();
	}

	template <typename T>
	void vector<T>::emplace_back(T &&val) {
		if (vec_sz == rsrv_sz) {
			rsrv_sz <<= 2;
			reallocate();
		}
		arr[vec_sz] = val;
		++vec_sz;
	}

	template <typename T>
	void vector<T>::reserve(const int &_sz) {
		if (_sz > rsrv_sz) {
			rsrv_sz = _sz;
			reallocate();
		}
	}

	template <typename T>
	void vector<T>::resize(const int &_sz) {
		if (_sz > vec_sz) {
			if (_sz > rsrv_sz) {
				rsrv_sz = _sz;
				reallocate();
			}
			vec_sz = _sz;
		} else {
			int i;
			for (i = vec_sz; i < _sz; ++i)
				arr[i].~T();
			vec_sz = _sz;
		}
	}

	template <typename T>
	void vector<T>::clear() {
		int i;
		for (i = 0; i < vec_sz; ++i)
			arr[i].~T();
		vec_sz = 0;
	}

	template <typename T>
	void vector<T>::swap(lni::vector<T> &rhs) {
		int i, sz = rhs.size();
		T *tmp = new T[sz];
		for (i = 0; i < sz; ++i)
			tmp[i] = rhs.arr[i];
		rhs.reserve(vec_sz);
		for (i = 0; i < vec_sz; ++i)
			rhs.arr[i] = arr[i];
		rhs.vec_sz = vec_sz;
		reserve(sz);
		for (i = 0; i < sz; ++i)
			arr[i] = tmp[i];
		vec_sz = sz;
		delete [] tmp;
	}
}

#endif

class umap_t {
	friend class umap;
	private:
	public:
		umap_t();
		lni::vector<long> pos;
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
	friend class db;
	private:
		static int TB_BITS;
		static int TB_SIZE;
		static int TB_MASK;

		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution;
		int hash_ref[6][128];
		lni::vector<umap_ref> ref;
		lni::vector<umap_t> data;
	public:
		
		typedef umap_t * iterator;
		umap();
		inline int hash(const char [], const char []); 
		inline int hash(const char []);

		iterator find(const char[], const char[]);
		inline void insert(const char [], const long &);
};

class db{
	private:
		long WBUF_SIZE = 100000000;
		long RBUF_SIZE = 200000000;

		char *wbuf;
		char *rbuf;
		int iter;

		char indexed;
		char temp_dir[30];
		char index_dir[30];
		umap mp;

		long *pos;
	public:
		db() {}

		void init();                                     //Do your db initialization.

		void setTempFileDir(const char []);                //All the files that created by your program should be located under this directory.

		void import(const char s[]);                        //Inport a csv file to your database.

		void createIndex();                              //Create index on one or two columns.

		double query(const char [], const char []);          //Do the query and return the average ArrDelay of flights from origin to dest.

		void cleanup();                                  //Release memory, close files and anything you should do to clean up your db class.


};
