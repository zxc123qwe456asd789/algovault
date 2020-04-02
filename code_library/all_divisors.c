#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


#define MAX 10000010


short len[MAX];
int lp[MAX], *divisors[MAX];


/***
 * generates all divisors from 1 to MAX efficiently
 * the idea is to generate the lp[x], the largest prime factor of x using sieve
 * then generate the divisors iteratively, i.e, to get divisors of x, use lp[x] and the divisors of [x / lp[x]]
 * this is order of magnitudes faster than the naive approach because of reduced cache miss
 * for instance, takes 1.1 seconds to generate all divisors up to 10^7 locally, where as the naive approach takes 16.5 seconds
 *
 * naive approach:
 * vector <int> divisors[MAX];
 *
 * void generate(){
 *	   for (int i = 1; i < MAX; i++){
 *		   for (int j = i; j < MAX; j += i){
 *			    divisors[j].push_back(i);
 *		   }
 *	   }
 * }
 *
***/

void generate(){
    int i, j, k, c, d, x;

    len[0] = len[1] = lp[0] = lp[1] = 1;
    for (i = 4; i < MAX; i++, i++) len[i] = 2;

    for (i = 3; (i * i) < MAX; i += 2){
		for (j = (i * i), d = i + i; j < MAX && !len[i]; j += d){
			if (!len[j]) len[j] = i;
		}
    }

    for (i = 2; i < MAX; i++){
        if (!len[i]) lp[i] = i;
        else{
            lp[i] = len[i];
            x = lp[i /len[i]];
            if (x > lp[i]) lp[i] = x;
        }
    }

    divisors[1] = (int *) malloc(sizeof(int));
    divisors[1][0] = 1, len[1] = 1;

    for (i = 2; i < MAX; i++){
        c = 1, k = i;
        while (k > 1 && lp[k] == lp[i]){
            c++;
            k /= lp[k];
        }

        len[i] = c * len[k];
        divisors[i] = (int *) malloc(sizeof(int) * len[i]);

        for (x = 1, j = 0, len[i] = 0; j < c; j++, x *= lp[i]){
            for (d = 0; d < len[k]; d++){
                divisors[i][len[i]++] = divisors[k][d] * x;
            }
        }
    }
}

int main(){
	clock_t start = clock();

    generate();

    int i, n = 24;

    printf("All divisors of %d are:\n", n);
    for (i = 0; i < len[n]; i++){
		printf("%d\n", divisors[n][i]);
	}

    fprintf(stderr, "\nTime taken = %0.6f\n", (clock() - start) / (1.0 * CLOCKS_PER_SEC));
    return 0;
}
