#ifndef _SORT_H_
#define _SORT_H_
int insert(int n, int *b) {
	int t, i, j, count = 0;
	for (i = 0; i < n; ++i) {
		t = b[i];
		for (j = i - 1; j >= 0 && t > b[j]; --j) {
			b[j + 1] = b[j];
			++count;
		}
		b[j + 1] = t;
	}
	return count;
}
int halfIns(int n, int *b) {
	int t, count = 0;
	for (int i = 0; i < n; ++i) {
		t = b[i];
		int l = 1, r = i - 1;
		while (l <= r) {
			int m = (l + r) / 2;
			if (t < b[m]) r = m - 1;
			else l = m + 1;
			++count;
		}
		for (int j = i - 1; j >= l; --j) b[j + 1] = b[j];
		b[r + 1] = t;
	}
	return count;
}
int shell(int n, int *b) {
	int d, count = 0;
	for (d = 3; d > 0; --d) {
		for (int i = 0; i < d; ++i) {
			for (int j = i + d; j < n; j += d) {
				++count;
				if (b[j] < b[j - d]) {
					int t = b[j];
					int k = j - d;
					while (k >= 0 && b[k] > t) {
						++count;
						b[k + d] = b[k];
						k -= d;
					}
					b[k + d] = t;
				}
			}
		}
	}
	return count;
}
int bubble(int n, int *b) {
	int count = 0;
	for (int i = 1; i < n; ++i)
	for (int j = 0; j < n - i; ++j) {
		++count;
		if (b[j] > b[j + 1]) {
			int t = b[j];
			b[j] = b[j + 1];
			b[j + 1] = t;
		}
	}
	return count;
}
int qsort(int l, int r, int *b) {
	int i = l, j = r, x = b[(l + r) / 2], count = 0;
	do {
		while (b[i] < x) ++i, ++count;
		while (b[j] > x) --j, ++count;
		if (i <= j) {
			int t = b[i];
			b[i] = b[j];
			b[j] = t;
			++i, --j;
		}
	} while (i <= j);
	if (l < j) count += qsort(l, j, b);
	if (i < r) count += qsort(i, r, b);
	return count;
}
int select(int n, int *b) {
	int count = 0;
	for (int i = 0; i < n; ++i) {
		int k = i;
		for (int j = i + 1; j < n; ++j) {
			++count;
			if (b[j] < b[k]) k = j;
		}
		int t = b[k];
		b[k] = b[i];
		b[i] = t;
	}
	return count;
}
void heap_shift(int n, int x, int &count, int *b) {
	while (x <= n / 2) {
		int t = x * 2;
		if (t < n && b[t] > b[t + 1]) {
			++t;
			++count;
		}
		++count;
		if (b[x] > b[t]) {
			int temp = b[x];
			b[x] = b[t];
			b[t] = temp;
			x = t;
		}
		else break;
	}
}
int heap(int n, int *b) {
	int count = 0;
	for (int i = n / 2; i >= 1; --i)
		heap_shift(n, i, count, b);
	while (n > 0) {
		b[1] = b[n--];
		heap_shift(n, 1, count, b);
	}
	return count;
}
int tmp[30000];
void domerge(int p, int q, int r, int &count, int *b) {
	int t = p, i = p, j = q + 1;
	while (t <= r) {
		++count;
		if (i <= q && (j > r || b[i] <= b[j]))
			tmp[t] = b[i++];
		else
			tmp[t] = b[j++];
		++t;
	}
	for (i = p; i <= r; ++i) b[i] = tmp[i];
}
int merge(int l, int r, int *b) {
	int count = 0;
	if (l != r) {
		int m = (l + r - 1) / 2;
		count += merge(l, m, b);
		count += merge(m + 1, r, b);
		domerge(l, m, r, count, b);
	}
	return count;
}

#endif