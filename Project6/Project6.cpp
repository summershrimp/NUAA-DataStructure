#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "Sort.h"
int a[30000], b[30000];


void copy(int n) {
	for (int i = 0; i < n; ++i) b[i] = a[i];
}

int main() {
	srand(time(0));
	printf("%5s%10s%10s%10s%10s%10s%10s%10s%10s\n", "Num", "Insert", "HalfIns", "Shell", "Bubble", "Qsort", "Select", "Heap", "Merge");
	for (int n = 500; n <= 30000; n += 500) {
		for (int i = 0; i < n; ++i) a[i] = rand();
		printf("%5d", n);
		copy(n);
		printf("%10d", insert(n,b));
		copy(n);
		printf("%10d", halfIns(n,b));
		copy(n);
		printf("%10d", shell(n,b));
		copy(n);
		printf("%10d", bubble(n,b));
		copy(n);
		printf("%10d", qsort(0, n - 1,b));
		copy(n);
		printf("%10d", select(n,b));
		// heap sort requires array starts from 1
		for (int i = 0; i < n; ++i) b[i + 1] = a[i];
		printf("%10d", heap(n,b));
		copy(n);
		printf("%10d", merge(0, n - 1,b));
		printf("\n");
	}
	return 0;
}
