#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include "Header.h"

#pragma warning(disable:4996)


void run(MinHpointer open, Ipointer begin) {

	start = clock();

	handle(open, begin);

	stop = clock();

	double duration = (double)(stop - start) / CLK_TCK;

	printf("--------- A* algorithm ---------\n");
	printf("”√ ±: %fs\n", duration);

}

