#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include "Header.h"

#pragma warning(disable:4996)


/**
* 宽度优先搜索 algorithm
*/
void breadthFirstSearchFollow(Qpointer open, Ipointer begin) {	// 寻找后继节点

	Ipointer node = NULL;

	for (Direction way = UP; way <= RIGHT; way++) {	// 尝试 "上、下、左、右" 所有四个方向, 判断是否可移动

		if (way != begin->blockDirection) {	// 非回退方向

			node = generateNewLayout(begin);	// 依据父节点创建新节点

			bool flag = move(node, way);	// 移动"0", 为新节点产生新布局

			if (flag == True) {	// 若能够产生新布局, 即, 可移动

				node->parent = begin;	// 赋值回溯指针

				if (judgeParity(countInverseNumber(assistInverse(node->digit)), open->inversion)) {

					addQ(open, node);

				}

			}

		}

	}

}
