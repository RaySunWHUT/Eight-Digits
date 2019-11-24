#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include "Header.h"

#pragma warning(disable:4996)


MinHpointer initialize() {	// 项目初始化

	const int standard[3][3] = { {1, 2, 3}, {8, 0, 4}, {7, 6, 5} };
	const long unique = converseMatrix(standard);
	const int inversion = countInverseNumber(assistInverse(standard));

	MinHpointer open = createMinHeap(MAXCAPACITY, unique, inversion);

	for (int i = 0; i < 3; i++) {	// 初始化九宫格

		for (int j = 0; j < 3; j++) {

			open->standard[i][j] = standard[i][j];

		}

	}

	return open;

}


Ipointer input(MinHpointer open) {	// input操作

	Ipointer nine = (Ipointer)malloc(ISIZE);

	FILE* fp;

	char fileName[256];

	printf("请输入文件名(文本为数字序列)：");

	scanf("%s", &fileName);

	char value = NULL;

	int sequence[9] = { 0 };

	int k = 0;

	fp = fopen(fileName, "r");  /* 以只读方式读取文件 */

	while ((value = fgetc(fp)) != EOF) {    /* 当文件未到末尾时，统计各对应字符的权值 (即频数) */

		if (value != ' ') {

			int ok = value - '0';

			sequence[k++] = ok;

		}

	}

	k = 0;

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < 3; j++) {

			nine->digit[i][j] = sequence[k++];

		}

	}

	nine->unique = converseMatrix(nine->digit);

	locateZeros(nine);	// 定位首节点 "0" 的坐标

	nine->blockDirection = NONE;
	nine->parent = NULL;

	getWeight(open, nine);

	return nine;

}

