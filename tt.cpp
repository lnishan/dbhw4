#include <bits/stdc++.h>

using namespace std;

int main() {
	char s[500];
	int i, j;
	int mn = 1e9;
	char file[100];
	strcpy(file, "data/2006.csv");
	for (auto &idx: {6, 7, 8} ) {
		file[8]  = idx + 48;
		freopen(file, "r", stdin);
		while (gets(s)) {
			for (i = 0, j = 0; s[i] && j <= 17; ++i)
				if (s[i] == ',')
					++j;
			j = i;
			for ( ; s[i]; ++i) ;
			mn = min(mn, i - j);
		}
	}
	printf("%d\n", mn);
	return 0;
}
