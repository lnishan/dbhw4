#include "db.h"

umap_t::umap_t(){
	pos.reserve(100);
}

umap_ref::umap_ref(): used(0) {

}

inline bool umap_ref::equal(const char ori[3], const char dst[3]) {
	return
		key[0][0] == ori[0] &&
		key[0][1] == ori[1] &&
		key[0][2] == ori[2] &&
		key[1][0] == dst[0] &&
		key[1][1] == dst[1] &&
		key[1][2] == dst[2];
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
		h = (h + 1) % TB_SIZE;
	return ref[h].used ? (&data[h]) : NULL;
}

void umap::insert(const char ori[3], const char dst[3], long pos = 0) {
	int h = hash(ori, dst);
	while (ref[h].used && !ref[h].equal(ori, dst))
		h = (h + 1) % TB_SIZE;
	ref[h].used = 1;
	ref[h].key[0][0] = ori[0]; ref[h].key[0][1] = ori[1]; ref[h].key[0][2] = ori[2];
	ref[h].key[1][0] = dst[0]; ref[h].key[1][1] = dst[1]; ref[h].key[1][2] = dst[2];
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

inline int umap::hash(const char &c0, const char &c1, const char &c2, const char &c3, const char &c4, const char &c5) {
	return
		hash_ref[0][c0] ^
		hash_ref[1][c1] ^
		hash_ref[2][c2] ^
		hash_ref[3][c3] ^
		hash_ref[4][c4] ^
		hash_ref[5][c5];
}
void db::init(){
	//Do your db initialization.
}

void db::setTempFileDir(const std::string &dir){
	//All the files that created by your program should be located under this directory.
	temp_dir = dir + "/lnishan.db";
	FILE *fo = fopen(temp_dir.c_str(), "w"); // empties the file
	fclose(fo);
}

void db::import(const char filename[]){
	//Inport a csv file to your database.
	FILE *fi = fopen(filename, "r");
	FILE *fo = fopen(temp_dir.c_str(), "a");
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
	FILE *fi = fopen(temp_dir.c_str(), "r");
	long pos = ftell(fi);
	char s[30];
	while (fgets(s, 30, fi)) {
		/* safety, can remove for testing */ if (!s[0]) continue;
		mp.insert(s, s + 3, pos);
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
		FILE * fi = fopen(temp_dir.c_str(), "r");
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
	FILE *fo = fopen(temp_dir.c_str(), "w"); // empties the file
	fclose(fo);
}


