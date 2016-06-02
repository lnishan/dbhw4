#include "db.h"

int umap::TB_BITS = 16;
int umap::TB_SIZE = 1 << TB_BITS;
int umap::TB_MASK = TB_SIZE - 1;

umap_t::umap_t(){
	pos.reserve(400);
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
	for (i = 0; i < 6; i++)
		for (j = 0; j < 128; j++)
			hash_ref[i][j] = distribution(generator);
}

umap::iterator umap::find(const char ori[3], const char dst[3]) {
	int h = hash(ori, dst);
	while (ref[h].used && !ref[h].equal(ori, dst))
		h = (h + 1) & TB_MASK;
	return ref[h].used ? (&data[h]) : NULL;
}

void umap::insert(const char key_i[6], long pos = 0) {
	int h = hash(key_i);
	while (ref[h].used && !ref[h].equal(key_i))
		h = (h + 1) & TB_MASK;
	ref[h].used = 1;
	ref[h].key[0] = key_i[0];
	ref[h].key[1] = key_i[1];
	ref[h].key[2] = key_i[2];
	ref[h].key[3] = key_i[3];
	ref[h].key[4] = key_i[4];
	ref[h].key[5] = key_i[5];
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
	FILE *fo = fopen(temp_dir, "a");
	int i, j, k, cnt;
	char s[500], sout[20];
	fgets(s, 500, fi);
	while (fgets(s, 500, fi)) {
		cnt = 0;
		for (i = 0; s[i]; ++i) {
			if (s[i] == ',') {
				++cnt;
				if (cnt == 14) {
					if (s[i + 1] == 'N') { // NA
						sout[6] = '0';
						sout[7] = '\n'; sout[8] = 0;
					} else {
						for (j = i + 1, k = 6; s[j] != ','; ++j, ++k)
							sout[k] = s[j];
						sout[k] = '\n'; sout[k + 1] = 0;
						i = j - 1;
					}
				} else if (cnt == 16) {
					sout[0] = s[i + 1];
					sout[1] = s[i + 2];
					sout[2] = s[i + 3];
					i += 3;
				} else if (cnt == 17) {
					sout[3] = s[i + 1];
					sout[4] = s[i + 2];
					sout[5] = s[i + 3];
					i += 3;
				}
			}
		}
		fputs(sout, fo);
	}
	fclose(fi);
	fclose(fo);
}

void db::createIndex(){
	//Create index.
	FILE *fi = fopen(temp_dir, "r");
	long pos = ftell(fi);
	char s[30];
	while (fgets(s, 30, fi)) {
		/* safety, can remove for testing */ if (!s[0]) continue;
		mp.insert(s, pos);
		pos = ftell(fi);
	}
	fclose(fi);
}

double db::query(const char ori[], const char dst[]){
	//Do the query and return the average ArrDelay of flights from origin to dest.
	//This method will be called multiple times.
	// printf("%d\n", mp.hash(ori, dst));

	double ret;
	auto it = mp.find(ori, dst);
	if (it == NULL) // Not found
		ret = 0.0;
	else {
		FILE * fi = fopen(temp_dir, "r");
		char s[30];
		long long sum = 0;
		int i, delay;
		for (auto &p: it->pos) {
			fseek(fi, p, SEEK_SET);
			fgets(s, 30, fi);
			/* safety, can remove for testing */ if (!s[0]) continue;
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
			// printf("%d ", delay);
			sum += delay;
		}
		ret = (double)sum / it->pos.size();
		fclose(fi);
	}
	return ret; //Remember to return your result.
}

void db::cleanup(){
	//Release memory, close files and anything you should do to clean up your db class.
	FILE *fo = fopen(temp_dir, "w"); // empties the file
	fclose(fo);
}


