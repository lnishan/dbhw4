#include "db.h"

umap_t::umap_t(){
	pos.reserve(20);
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
	// printf("fnd: %d\n", h);
	while (ref[h].used && !ref[h].equal(ori, dst))
		h = (h + 1) % TB_SIZE;
	return ref[h].used ? (&data[h]) : NULL;
}

void umap::insert(const char ori[3], const char dst[3], long pos = 0) {
	int h = hash(ori, dst);
	// printf("ins: %d\n", h);
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

void db::setTempFileDir(const char dir[]){
	//All the files that created by your program should be located under this directory.
	strcpy(temp_dir, dir);
}

void db::import(const std::string &csvFileName){
	//Inport a csv file to your database.
}

void db::createIndex(){
	//Create index.
}

double db::query(const char ori[], const char dst[]){
	//Do the query and return the average ArrDelay of flights from origin to dest.
	//This method will be called multiple times.
	// printf("%d\n", mp.hash(ori, dst));
	mp.insert(ori, dst, (long)ori[0]);
	mp.insert(ori, dst, (long)dst[0]);
	auto it = mp.find(ori, dst);
	if (it == NULL)
		puts("Error");
	else
		printf("%lld %lld\n", it->pos[0], it->pos[1]);
	return 0; //Remember to return your result.
}

void db::cleanup(){
	//Release memory, close files and anything you should do to clean up your db class.
}


