#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include "Header.h"

#pragma warning(disable:4996)

int main() {

	
	Qpointer open = initialize();

	Ipointer begin = input();

	run(open, begin);

	return 0;

}
