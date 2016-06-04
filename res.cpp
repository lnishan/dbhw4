#include <bits/stdc++.h>

using namespace std;

double a[5][4];

void parse_batch(int r) {
	char s[100];
	char *ptr;
	int j, len;
	for (j = 0; j < 4; j++) {
		while (gets(s) && s[0] != 'T') ;
		ptr = strtok(s, ":");
		ptr = strtok(NULL, ":");
		len = strlen(ptr);
		ptr[len - 1] = '0';
		sscanf(ptr, "%lf", &a[r][j]);
	}
}

int main(int argc, char *argv[]) {
	int i, j;
	double sum[4];
	char file[30];
	for (i = 0; i < 4; i++)
		sum[i] = 0.0;
	if (argc >= 2) {
		freopen(argv[1], "r", stdin);
	}
	// freopen("res.txt", "w", stdout);

	puts("| # | Import | Dry-Queries | Indexing | Queries |");
	puts("| --- | --- | --- | --- | --- |");

	for (i = 0; i < 5; i++)
		parse_batch(i);

	for (i = 0; i < 5; i++) {
		printf("| %d |", i + 1);
		for (j = 0; j < 4; j++) {
			sum[j] += a[i][j];
			printf(" %.4f |", a[i][j]);
		}
		puts("");
	}

	printf("| **Avg.** |");
	for (j = 0; j < 4; j++)
		printf(" **%.5f** |", sum[j] / 5.0);
	return 0;
}
