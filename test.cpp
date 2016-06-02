#include <bits/stdc++.h>

using namespace std;

int main() {
	FILE *fi = fopen("temp/lnishan.db", "rb");
	fseek(fi, 199299953, SEEK_SET);
	char s[30];
	fgets(s, 30, fi);
	printf("%s", s);
	return 0;
}
