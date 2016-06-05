#include "db.h"

using std::min;

int umap::TB_BITS = 16;
int umap::TB_SIZE = 1 << TB_BITS;
int umap::TB_MASK = TB_SIZE - 1;

umap_t::umap_t(){
	pos.reserve(2048);
}

umap_ref::umap_ref(): used(0) {

}

inline bool umap_ref::equal(const char ori[3], const char dst[3]) {
	return
		key[0] == ori[0] &&
		key[1] == ori[1] &&
		key[2] == ori[2] &&
		key[3] == dst[0] &&
		key[4] == dst[1] &&
		key[5] == dst[2];
}

inline bool umap_ref::equal(const char key_i[6]) {
	return
		key[0] == key_i[0] &&
		key[1] == key_i[1] &&
		key[2] == key_i[2] &&
		key[3] == key_i[3] &&
		key[4] == key_i[4] &&
		key[5] == key_i[5];
}

umap::umap(): distribution(0, TB_SIZE - 1) {
	data.resize(TB_SIZE);
	ref.resize(TB_SIZE);
	int i, j;
	for (i = 0; i < 6; ++i)
		for (j = 0; j < 128; ++j)
			hash_ref[i][j] = distribution(generator);
}

umap::iterator umap::find(const char ori[3], const char dst[3]) {
	int h = hash(ori, dst);
	while (ref[h].used && !ref[h].equal(ori, dst))
		h = (h + 1) & TB_MASK;
	return ref[h].used ? (&data[h]) : NULL;
}

void umap::insert(const char key_i[6], const long &pos) {
	int h = hash(key_i);
	while (ref[h].used && !ref[h].equal(key_i))
		h = (h + 1) & TB_MASK;
	if (!ref[h].used) {
		ref[h].used = 1;
		ref[h].key[0] = key_i[0];
		ref[h].key[1] = key_i[1];
		ref[h].key[2] = key_i[2];
		ref[h].key[3] = key_i[3];
		ref[h].key[4] = key_i[4];
		ref[h].key[5] = key_i[5];
	}
	data[h].pos.emplace_back(pos);
}

inline int umap::hash(const char ori[3], const char dst[3]) {
	return
		hash_ref[0][ori[0]] ^
		hash_ref[1][ori[1]] ^
		hash_ref[2][ori[2]] ^
		hash_ref[3][dst[0]] ^
		hash_ref[4][dst[1]] ^
		hash_ref[5][dst[2]];
}

inline int umap::hash(const char key_i[6]) {
	return
		hash_ref[0][key_i[0]] ^
		hash_ref[1][key_i[1]] ^
		hash_ref[2][key_i[2]] ^
		hash_ref[3][key_i[3]] ^
		hash_ref[4][key_i[4]] ^
		hash_ref[5][key_i[5]];
}
void db::init(){
	//Do your db initialization.
	wbuf = new char[WBUF_SIZE];
	rbuf = new char[RBUF_SIZE];
	iter = 0;
	indexed = 0;
}

void db::setTempFileDir(const char dir[15]){
	//All the files that created by your program should be located under this directory.
	strcpy(temp_dir, dir);
	strcat(temp_dir, "/lnishan.db");
	FILE *fo = fopen(temp_dir, "w"); // empties the file
	fclose(fo);
}

void db::import(const char filename[]){
	//Inport a csv file to your database.
	FILE *fi = fopen(filename, "r");
	FILE *fo = fopen(temp_dir, "ab");
	int i, j, k, l, cnt;
	char s[500];
	int next_iter;
	long sz, sz_left, read_sz;

	fseek(fi, 0, SEEK_END);
	sz_left = sz = ftell(fi);
	rewind(fi);

	read_sz = min(sz_left, RBUF_SIZE - 500);
	fread(rbuf, 1, read_sz, fi);
	if (fgets(s, 500, fi)) {
		for (i = read_sz, j = 0; s[j]; ++i, ++j)
			rbuf[i] = s[j];
		rbuf[i] = 0;
		read_sz += j;
	} else
		rbuf[read_sz] = 0;

	for (i = 0; rbuf[i] != '\n'; ++i) ;
	++i;

	for ( ; sz_left; i = 0) {
		for ( ; rbuf[i]; ) {
			cnt = 0;
			for ( ; cnt != 14; ++i)
				if (rbuf[i] == ',') ++cnt;
			if (rbuf[i] != 'N' && rbuf[i] != ',') { // NA, Empty
				for (j = i, k = iter + 6; rbuf[j] != ','; ++j, ++k)
					wbuf[k] = rbuf[j];
				wbuf[k] = '\n';
				i = j - 1;
				next_iter = k + 1;
			} else {
				while (rbuf[i] != '\n') ++i;
				++i;
				next_iter = iter;
				continue;
			}

			for ( ; cnt != 16; ++i)
				if (rbuf[i] == ',') ++cnt;
			wbuf[iter    ] = rbuf[i    ];
			wbuf[iter + 1] = rbuf[i + 1];
			wbuf[iter + 2] = rbuf[i + 2];
			i += 3;

			for ( ; cnt != 17; ++i)
				if (rbuf[i] == ',') ++cnt;
			wbuf[iter + 3] = rbuf[i    ];
			wbuf[iter + 4] = rbuf[i + 1];
			wbuf[iter + 5] = rbuf[i + 2];

			while (rbuf[i] != '\n') ++i;
			++i;

			iter = next_iter;
		}

		sz_left -= read_sz;

		read_sz = min(sz_left, RBUF_SIZE - 500);
		fread(rbuf, 1, read_sz, fi);
		if (fgets(s, 500, fi)) {
			for (i = read_sz, j = 0; s[j]; ++i, ++j)
				rbuf[i] = s[j];
			rbuf[i] = 0;
			read_sz += j;
		} else
			rbuf[read_sz] = 0;
	}

	wbuf[iter] = 0;
	fputs(wbuf, fo);
	iter = 0;

	fclose(fi);
	fclose(fo);
}

void db::createIndex(){
	//Create index.
	FILE *fi = fopen(temp_dir, "rb");
	int i, j;
	char s[30];
	long sz, sz_left, read_sz, pos_base;

	fseek(fi, 0, SEEK_END);
	sz_left = sz = ftell(fi);
	rewind(fi);

	read_sz = min(sz_left, RBUF_SIZE - 30);
	fread(rbuf, 1, read_sz, fi);
	if (fgets(s, 30, fi)) {
		for (i = read_sz, j = 0; s[j]; ++i, ++j)
			rbuf[i] = s[j];
		rbuf[i] = 0;
		read_sz += j;
	} else
		rbuf[read_sz] = 0;
	
	for (i = 0, pos_base = 0; sz_left; i = 0) { 
		for ( ; rbuf[i]; ++i) {
			mp.insert((&rbuf[i]), pos_base + i);
			for ( ; rbuf[i] != '\n'; ++i) ;
		}
		sz_left -= read_sz;
		pos_base += read_sz;

		read_sz = min(sz_left, RBUF_SIZE - 30);
		fread(rbuf, 1, read_sz, fi);
		if (fgets(s, 30, fi)) {
			for (i = read_sz, j = 0; s[j]; ++i, ++j)
				rbuf[i] = s[j];
			rbuf[i] = 0;
			read_sz += j;
		} else
			rbuf[read_sz] = 0;
	}

	fclose(fi);
	indexed = 1;
}

double db::query(const char ori[], const char dst[]){
	//Do the query and return the average ArrDelay of flights from origin to dest.
	//This method will be called multiple times.
	// printf("%d\n", mp.hash(ori, dst));

	double ret;
	if (indexed) {
		auto it = mp.find(ori, dst);
		if (it == NULL) // Not found
			ret = 0.0;
		else {
			FILE * fi = fopen(temp_dir, "rb");
			char s[30];
			long long sum = 0;
			int i, delay;
			for (auto &p: it->pos) {
				fseek(fi, p, SEEK_SET);
				fgets(s, 30, fi);
				if (s[6] == '-') {
					delay = s[7] - 48;
					for (i = 8; s[i] != '\n'; ++i)
						delay = delay * 10 + s[i] - 48;
					delay = -delay;
				} else {
					delay = s[6] - 48;
					for (i = 7; s[i] != '\n'; ++i)
						delay = delay * 10 + s[i] - 48;
				}
				sum += delay;
			}
			ret = (double)sum / it->pos.size();
			fclose(fi);
		}
	} else {
		FILE *fi = fopen(temp_dir, "r");
		char s[30], *ts;
		long long sum = 0;
		int i, j, delay, flights = 0;
		long sz, sz_left, read_sz;
	
		fseek(fi, 0, SEEK_END);
		sz_left = sz = ftell(fi);
		rewind(fi);
		
		read_sz = min(sz_left, RBUF_SIZE - 30);
		fread(rbuf, 1, read_sz, fi);
		if (fgets(s, 30, fi)) {
			for (i = read_sz, j = 0; s[j]; ++i, ++j)
				rbuf[i] = s[j];
			rbuf[i] = 0;
			read_sz += j;
		} else
			rbuf[read_sz] = 0;
		for (i = 0; sz_left; i = 0) { 
			for ( ; rbuf[i]; ++i) {
				ts = rbuf + i;
				if (ts[0] == ori[0] && ts[1] == ori[1] && ts[2] == ori[2] &&
						ts[3] == dst[0] && ts[4] == dst[1] && ts[5] == dst[2]) {
					if (ts[6] == '-') {
						delay = ts[7] - 48;
						for (j = 8; ts[j] != '\n'; ++j)
							delay = delay * 10 + ts[j] - 48;
						delay = -delay;
					} else {
						delay = ts[6] - 48;
						for (j = 7; ts[j] != '\n'; ++j)
							delay = delay * 10 + ts[j] - 48;
					}
					++flights;
					sum += delay;
					for ( ; rbuf[i] != '\n'; ++i) ;
				}
			}
			sz_left -= read_sz;

			read_sz = min(sz_left, RBUF_SIZE - 30);
			fread(rbuf, 1, read_sz, fi);
			if (fgets(s, 30, fi)) {
				for (i = read_sz, j = 0; s[j]; ++i, ++j)
					rbuf[i] = s[j];
				rbuf[i] = 0;
				read_sz += j;
			} else
				rbuf[read_sz] = 0;
	
		}
		ret = (double)sum / flights;
		fclose(fi);
	}
	return ret;
}

void db::cleanup(){
	//Release memory, close files and anything you should do to clean up your db class.
	FILE *fo = fopen(temp_dir, "w"); // empties the file
	fclose(fo);

	delete [] wbuf;
	delete [] rbuf;
}

