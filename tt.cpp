#include <bits/stdc++.h>

using namespace std;

int main() {
	long sz;
	char *buf;


	time_t st = clock();

	FILE *fi = fopen("data/2008.csv", "r");
	fseek(fi, 0, SEEK_END);
	sz = ftell(fi);
	
	rewind(fi);
	buf = new char[sz + 1];
	fread(buf, 1, sz, fi);

	printf("%d\n", sz);
	
	// printf("%s", buf + sz - 1000);
	
	fclose(fi);
	
	printf("%.4f\n", (double)(clock() - st) / CLOCKS_PER_SEC);

	
	while (rand() % 10000) ;


	st = clock();

	fi = fopen("data/2008.csv", "r");
	printf("\n\n\n\n fgets()");
	int i;
	char s[500];
	while (fgets(s, 500, fi)) ;

	printf("%.4f\n", (double)(clock() - st) / CLOCKS_PER_SEC);
	return 0;
}
