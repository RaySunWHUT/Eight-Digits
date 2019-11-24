#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include "Header.h"

#pragma warning(disable:4996)

void run(Qpointer open, Ipointer begin) {

	start = clock();

	handle(open, begin);

	stop = clock();

	double duration = (double)(stop - start) / CLK_TCK;

	printf("--------- breadth first search ---------\n");
	printf("”√ ±: %fs\n", duration);

}
