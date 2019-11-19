#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include "Header.h"

#pragma warning(disable:4996)

/**
* process block
* author: Sun Ray 2019.11.19
*/
Qpointer initialize() {	// 项目初始化

	const int standard[3][3] = { {1, 2, 3}, {8, 0, 4}, {7, 6, 5} };
	const long unique = converseMatrix(standard);
	const int inversion = countInverseNumber(assistInverse(standard));

	Qpointer open = createQueue(40, unique, inversion);

	for (int i = 0; i < 3; i++) {	// 初始化九宫格

		for (int j = 0; j < 3; j++) {

			open->standard[i][j] = standard[i][j];

		}

	}

	return open;

}


Ipointer input(Qpointer open) {	// input操作

	Ipointer nine = (Ipointer)malloc(ISIZE);

	FILE* fp;

	char fileName[256];

	printf("请输入文件名(数字间空格分隔)：");

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


void helper(Hpointer helper, char name[]) {	// 辅助handle函数

	printf("\n---------- %s 回溯路径 ----------\n", name);

	if (helper->flag == True) {

		printf("\nsearch successful! \n");

		int times = backtrack(helper->end);

		printf("\n最少移动 %d 步到达目标状态. \n\n", times);

	}
	else if (helper->flag == False) {

		printf("\nsearch failed! \n");
		printf("\n目标状态不可达! \n");

	}
	else {	// isOk = Unknown

		printf("\nsearch successful! \n");
		printf("首结点即为目标节点, 无需移动(移动 0 步到达目标状态). \n");

	}

}


void processBlock(Qpointer open, Ipointer begin) {	// 封装

	char* names[] = { "宽度优先搜索算法", "全局择优搜索算法", "A*算法" };

	for (int i = 0; i < 3; i++) {

		Cpointer closed = getClosed(begin);	// 初始化, 获得closed表;

		run(open, begin, i, names[i], closed);

		destoryQ(open);	// 清空队列

		helper(store[i], names[i]);

		dostoryClosed(closed);	// 清空链表

	}

}
