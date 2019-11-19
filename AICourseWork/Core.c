#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include "Header.h"

#pragma warning(disable:4996)

/**
* core function
* author: Sun Ray
*/

Hpointer handle(Qpointer open, Ipointer begin, int order, Cpointer closed) {	// 处理流

	Ipointer node = begin;

	Hpointer helper = (Hpointer)malloc(HSIZE);

	bool isOk;

	if (isSuccess(node->digit, open->unique)) {	// 若首结点即为目标节点, 直接结束

		isOk = Unknown;
		helper->flag = isOk;
		helper->end = begin;

		return helper;

	}
	else {	// 首结点非目标节点

		while (1) {	// 寻找目标节点

			if (judgeParity(countInverseNumber(assistInverse(node->digit)), open->inversion)) {	// 若逆序数奇偶性相同, 则进行; 否则, 跳过

				if (order == 0) {	// order == 0: 执行宽度优先搜索算法

					breadthFirstSearchFollow(open, node);

				}
				else if (order == 1 || order == 2) {	// order == 1: 执行全局择优搜索算法; order == 2: 执行A*算法

					globalOptimizationFollow(open, node);

				}

			}

			if (isEmpty(open)) {	// (队列)open表为空

				isOk = False;
				break;

			}

			node = deleteQ(open);	// 出队

			if (order == 2) {	// 执行A*算法

				applyAStar(closed, node);	// 应用A*算法

			}

			insertNode(closed, node);	// 插入结点: 注意顺序, 先应用A*算法, 再将结点插入链表中

			if (isSuccess(node->unique, open->unique)) {	// 若找到解决方案, 则跳出

				isOk = True;
				break;

			}

		}

	}

	helper->flag = isOk;
	helper->end = node;

	return helper;

}


Ipointer generateNewLayout(Ipointer nine) {	// 创建节点

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


bool move(Ipointer node, Direction way) {	// 核心函数: 移动 "0"

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

		node->blockDirection = getBlockDirection(way);	// 赋值回退方向

		node->unique = converseMatrix(node->digit);

	}

	return flag;

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
