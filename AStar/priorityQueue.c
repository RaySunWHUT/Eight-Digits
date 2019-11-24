#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include "Header.h"

#pragma warning(disable:4996)

/*
 author: Sun Rui
 time: 2019-11-23
*/
MinHpointer createMinHeap(int maxSize, long unique, int inversion) {	// 创建最小堆

	MinHpointer minHeap = (MinHpointer)malloc(HSIZE);
	minHeap->data = (ElementType*)malloc((maxSize + 1) * ESIZE);
	minHeap->capacity = maxSize;
	minHeap->size = 0;

	Ipointer top = (Ipointer)malloc(ISIZE);
	top->blockDirection = Unknown;
	top->parent = NULL;
	top->zero[0] = top->zero[1] = 0;
	top->weight = MINDATA;

	minHeap->data[0] = top;   /* 哨兵结点 */

	minHeap->unique = unique;
	minHeap->inversion = inversion;

	return minHeap;

}


bool isFull(MinHpointer minH) {	// 判满

	return (minH->size == minH->capacity);

}


bool insertElement(MinHpointer minH, ElementType x) {    /* 程序精简 */

	int i = 0;   /* 即插入结点后堆中最后一个结点的位置 */

	if (isFull(minH)) {

		printf("min heap is full! \n");

		return False;

	}
	else {

		i = ++minH->size;

		for (; x->weight < minH->data[i / 2]->weight; i = i / 2) {

			minH->data[i] = minH->data[i / 2];

		}

		minH->data[i] = x;

		return True;

	}

}


bool isHeapEmpty(MinHpointer minH) {

	return (minH->size == 0);

}


ElementType deleteMin(MinHpointer minH) {      /* 妙！妙啊！ */

	int parent, child;
	ElementType minItem, x;

	if (isHeapEmpty(minH)) {  /* 空堆 */

		printf("min heap is empty. \n");
		return ERROR;

	}

	minItem = minH->data[1];    /* 取出根结点，最小元素 */
	x = minH->data[minH->size--];     /* 取出最后一个元素 */

	for (parent = 1; parent * 2 <= minH->size; parent = child) {

		child = parent * 2;
		if ((child != minH->size) && (minH->data[child]->weight > minH->data[child + 1]->weight)) {   /* 未到达最后位置且右孩子 < 左孩子 */

			child++;    /* child指向左右结点中的较小值 */

		}

		if (x->weight <= minH->data[child]->weight) {	/* 找到合适位置 */

			break;

		}
		else {    /* X < minH->Data[child] */

			minH->data[parent] = minH->data[child];

		}

	}

	minH->data[parent] = x;

	return minItem;

}


void percDown(MinHpointer minH, int p) {	// 下滤

	int parent, child;
	ElementType x;

	x = minH->data[p];	// 每层根节点

	for (parent = p; parent * 2 <= minH->size; parent = child) {

		child = parent * 2;   /* 先指向左子树 */

		if ((child != minH->size) && (minH->data[child]->weight > minH->data[child + 1]->weight)) {

			child++;    /* 调整，指向较小子树 */

		}

		if (x->weight <= minH->data[child]->weight) {

			break;

		}
		else {

			minH->data[parent] = minH->data[child];

		}

	}

	minH->data[parent] = x;

}


void bulidHeap(MinHpointer minH) {	// 将已存在的N个元素按最小堆的要求存放于一维数组中

	int i = 0;

	for (i = minH->size / 2; i >= 1; i--) {

		percDown(minH, i);

	}

}


void outputHeap(MinHpointer minH) {

	int i = 0;

	for (i = 1; i <= minH->size; i++) {

		printf("%4d", minH->data[i]->weight);

	}

}
