#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include "Header.h"

#pragma warning(disable:4996)

/**
* test part
* author: Sun Ray 2019.11.19
*/
void print(ElementType A[], int N) {	// 测试用函数

	for (int k = 0; k < N; k++) {

		for (int i = 0; i < 3; i++) {

			for (int j = 0; j < 3; j++) {

				printf("%4d", A[k]->digit[i][j]);

			}

			printf("\n");

		}

		printf("weight = %d", A[k]->weight);

		printf("\n---------------------------\n");

	}

}


void run(Qpointer open, Ipointer begin, int order, char name[], Cpointer closed) {	// runtime测试函数

	int i = 0;

	start = clock();

	store[order] = handle(open, begin, order, closed);

	stop = clock();

	double duration = (double)(stop - start) / CLK_TCK;

	duration *= 1000;

	printf("%s 用时: %fms(放大1000倍)\n", name, duration);

}
