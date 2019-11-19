#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include "Header.h"

#pragma warning(disable:4996)

/**
* 全局择优搜索 algorithm
* author: Sun Ray 2019.11.19
*/
void globalOptimizationFollow(Qpointer open, Ipointer begin) {

	Ipointer node = NULL;

	Ipointer weight[4] = { NULL };

	int k = 0;

	for (Direction way = UP; way <= RIGHT; way++) {	// 尝试 "上、下、左、右" 所有四个方向, 判断是否可移动

		if (way != begin->blockDirection) {	// 非回退方向

			node = generateNewLayout(begin);	// 依据父节点创建新节点

			bool flag = move(node, way);	// 移动"0", 为新节点产生新布局

			if (flag == True) {	// 若能够产生新布局, 即, 可移动

				if (judgeParity(countInverseNumber(assistInverse(node->digit)), open->inversion)) {

					node->parent = begin;	// 赋值回溯指针

					getWeight(open, node);

					weight[k++] = node;

				}

			}

		}

	}

	weightSort(weight, k);	// 按启发函数权重排序

	for (int i = 0; i < k; i++) {	// 按启发函数值的大小顺序入队列

		addQ(open, weight[i]);

	}

}


void getWeight(Qpointer open, Ipointer node) {	// 获取权重, 权重越小, 越先达到目标状态

	int diff = 0;	// 记录不同元素个数

	int deep = 0;	// root为 1 层

	int weight = 0;

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < 3; j++) {

			if (node->digit[i][j] != open->standard[i][j]) {

				diff++;

			}

		}

	}

	deep = getDeep(node);

	weight = diff + deep;	// 启发函数: 权重越小(即, 浅 + 少, 深度越浅、不同元素越少), 相似度越高, 路径越短

	node->weight = weight;

}


void weightSort(ElementType A[], int N) {	// 权重排序: 插入排序

	int p, i;
	ElementType temp;

	for (p = 1; p < N; p++) {

		temp = A[p];  /* 取出未排序序列的第一个元素 */

		for (i = p; i > 0 && A[i - 1]->weight > temp->weight; i--) {  /* 依次与已排序序列中的元素比较并右移 */

			A[i] = A[i - 1];

		}

		A[i] = temp;  // 找到合适位置，插入

	}

}


int getDeep(Ipointer node) {	// 获取结点深度

	Ipointer p = node;

	int times = 0;

	while (p != NULL) {

		p = p->parent;

		times++;

	}

	return times;

}