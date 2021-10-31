#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

/**
 * In the insertion part, choose to shift the array instead of exchanging elements every time
 * to reduce the time of accessing array
 */
void shellsort(int v[], int n) {
	int gap, i, j, tmp;

	for (gap = n / 2; gap > 0; gap /= 2)
		for (i = gap; i < n; i++) {
			for (j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap)
				;
			tmp = v[i];
			for (int k = i - gap; k >= j + gap; k -= gap) {
				v[k + gap] = v[k];
			}
			v[j + gap] = tmp;
		}
}
