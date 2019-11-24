#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include "Header.h"

#pragma warning(disable:4996)

/*
 基于A算法(全局择优算法)求解A*算法
 author: Sun Rui
 time: 2019.11.19
 */
void handle(MinHpointer open, Ipointer begin) {	// 处理流

	Ipointer node = begin;

	Cpointer closed = getClosed(begin);

	if (isSuccess(node->digit, open->unique)) {	// 若首结点即为目标节点, 直接结束

		printf("\nsearch successful! \n");

		printf("首结点即为目标节点, 无需移动(移动 0 步到达目标状态). \n");

	}
	else {	// 首结点非目标节点

		bool isOk = Unknown;

		while (1) {	// 寻找目标节点

			if (judgeParity(countInverseNumber(assistInverse(node->digit)), open->inversion)) {	// 若逆序数奇偶性相同, 则进行; 否则, 跳过

				globalOptimizationFollow(open, node);

			}

			if (isHeapEmpty(open)) {	// (队列)open表为空

				isOk = False;
				break;

			}

			node = deleteMin(open);

			applyAStar(closed, node);

			insertNode(closed, node);

			if (isSuccess(node->digit, open->unique)) {	// 若找到解决方案, 则跳出

				isOk = True;
				break;

			}

		}

		if (isOk == True) {

			printf("\nsearch successful! \n");

			int times = backtrack(node);

			printf("\n最少移动 %d 步到达目标状态 \n", times);

		}
		else if (isOk == False) {

			printf("\nsearch failed! \n");
			printf("\n目标状态不可达 \n");

		}

	}

}


Ipointer createNode(Ipointer nine) {	// 创建节点

	Ipointer node = (Ipointer)malloc(ISIZE);

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < 3; j++) {

			node->digit[i][j] = nine->digit[i][j];

		}

	}

	node->zero[0] = nine->zero[0];
	node->zero[1] = nine->zero[1];

	return node;

}


bool move(Ipointer node, Direction way) {	// 移动 "0"

	int x, y;	// 存储 "0" 的横、纵坐标

	x = node->zero[0];
	y = node->zero[1];

	int mx = x;	// 移动后的x坐标
	int my = y;	// 移动后的y坐标

	bool flag = False;	// 标记能否移动

	switch (way) {	// 选择方向

	case UP:
		if ((--mx) >= 0) {

			flag = True;

		}
		break;
	case DOWN:
		if ((++mx) <= 2) {

			flag = True;

		}
		break;
	case LEFT:
		if ((--my) >= 0) {

			flag = True;

		}
		break;
	case RIGHT:
		if ((++my) <= 2) {

			flag = True;

		}
		break;

	}

	if (flag == True) {	// 可移动

		int location = node->digit[mx][my];	// 进行结点元素交换

		node->digit[x][y] = location;

		node->digit[mx][my] = 0;

		node->zero[0] = mx;	// 赋值父节点"0"坐标
		node->zero[1] = my;

		node->unique = converseMatrix(node->digit);

		node->blockDirection = getBlockDirection(way);	// 赋值回退方向

	} else {

		free(node);

	}

	return flag;

}


void locateZeros(Ipointer node) {	// 定位 "0" 的坐标, 只在确定起始结点的"0"坐标时, 调用一次

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < 3; j++) {

			if (node->digit[i][j] == 0) {

				node->zero[0] = i;
				node->zero[1] = j;

			}

		}

	}

}


Direction getBlockDirection(Direction way) {	// 获取禁止移动方向: 本次移动的反方向

	Direction ok = NONE;

	switch (way) {	// 禁止回退

	case UP:
		ok = DOWN;
		break;
	case DOWN:
		ok = UP;
		break;
	case LEFT:
		ok = RIGHT;
		break;
	case RIGHT:
		ok = LEFT;
		break;

	}

	return ok;

}


int backtrack(Ipointer end) {	// 回溯

	Ipointer p = end;

	int times = -1;	// 次数

	while (p != NULL) {

		printf("--------- %d times start ---------\n", ++times);

		for (int i = 0; i < 3; i++) {

			for (int j = 0; j < 3; j++) {

				printf("%3d", p->digit[i][j]);

			}

			printf("\n");

		}

		p = p->parent;

	}

	return times;

}


bool judgeParity(int begin, int open) {		// 判断新产生的九宫格的逆序数的个数的奇偶性是否一致

	int i = begin % 2;
	int j = open % 2;

	if (i == j) {

		return True;

	}
	else {

		return False;

	}

}


void globalOptimizationFollow(MinHpointer open, Ipointer begin) {

	Ipointer node = NULL;

	int k = 0;

	for (Direction way = UP; way <= RIGHT; way++) {	// 尝试 "上、下、左、右" 所有四个方向, 判断是否可移动

		if (way != begin->blockDirection) {	// 非回退方向

			node = createNode(begin);	// 依据父节点创建新节点

			bool flag = move(node, way);	// 移动"0", 为新节点产生新布局

			if (flag == True) {	// 若能够产生新布局, 即, 可移动

				if (judgeParity(countInverseNumber(assistInverse(node->digit)), open->inversion)) {

					node->parent = begin;	// 赋值回溯指针

					getWeight(open, node);

					insertElement(open, node);

				}

			}

		}

	}

}


void getWeight(MinHpointer open, Ipointer node) {	// 获取权重, 权重越小, 越先达到目标状态

	int diff = 0;	// 记录不同元素个数

	int deep = 0;	// root为 1 层

	int weight = 0;

	Ipointer p = node;

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < 3; j++) {

			if (node->digit[i][j] != open->standard[i][j]) {

				diff++;

			}

		}

	}

	deep = getDeep(node);

	weight = diff + deep;	// 权重越小(即, 浅 + 少, 深度约浅、不同元素越少), 相似度越高, 路径越短

	node->weight = weight;

}


int getDeep(Ipointer node) {

	Ipointer p = node;

	int times = 0;

	while (p != NULL) {

		p = p->parent;

		times++;

	}

	return times;

}


/**
 A* algorithm
 author: Sun Rui 2019.11.19
*/
void applyAStar(Cpointer closed, Ipointer node) {	// 应用A*算法

	Ipointer resultp = findUnique(closed, node);

	if (resultp != NULL) {

		if (getDeep(resultp) > getDeep(node)) {

			resultp->parent = node->parent;
			resultp->weight = node->weight;	// 有必要更新

		}

	}

	return;

}