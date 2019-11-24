#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include "Header.h"

#pragma warning(disable:4996)

int main() {

	MinHpointer open = initialize();
	
	Ipointer begin = input(open);

	run(open, begin);

	return 0;

}
