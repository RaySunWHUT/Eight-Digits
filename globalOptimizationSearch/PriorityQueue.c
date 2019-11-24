#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include "Header.h"

#pragma warning(disable:4996)


MinHpointer createMinHeap(int maxSize) {	// 创建最小堆

	MinHpointer minHeap = (MinHpointer)malloc(HSIZE);
	minHeap->Data = (ElementType*)malloc((maxSize + 1) * ESIZE);
	minHeap->Capacity = maxSize;
	minHeap->Size = 0;
	minHeap->Data[0] = MINDATA;   /* 哨兵结点 */

	return minHeap;

}


bool isFull(MinHpointer minH) {	// 判满

	return (minH->Size == minH->Capacity);

}


bool insert(MinHpointer minH, ElementType x) {    /* 程序精简 */

	int i = 0;   /* 即插入结点后堆中最后一个结点的位置 */

	if (isFull(minH)) {

		printf("min heap is full! \n");

		return False;

	}
	else {

		i = ++minH->Size;

		for ( ; x < minH->Data[i / 2]; i = i / 2) {

			minH->Data[i] = minH->Data[i / 2];

		}

		minH->Data[i] = x;

		return True;

	}

}


bool isEmpty(MinHpointer minH) {

	return (minH->Size == 0);

}


ElementType deleteMin(MinHpointer minH) {      /* 妙！妙啊！ */

	int parent, child;
	ElementType minItem, x;

	if (isEmpty(minH)) {  /* 空堆 */

		printf("min heap is empty. \n");
		return ERROR;

	}

	minItem = minH->Data[1];    /* 取出根结点，最小元素 */
	x = minH->Data[minH->Size--];     /* 取出最后一个元素 */

	for (parent = 1; parent * 2 <= minH->Size; parent = child) {

		child = parent * 2;
		if ((child != minH->Size) && (minH->Data[child] > minH->Data[child + 1])) {   /* 未到达最后位置且右孩子 < 左孩子 */

			child++;    /* child指向左右结点中的较小值 */

		}

		if (x <= minH->Data[child]) {	/* 找到合适位置 */

			break;

		} else {    /* X < minH->Data[child] */

			minH->Data[parent] = minH->Data[child];

		}

	}

	minH->Data[parent] = x;

	return minItem;

}


void percDown(MinHpointer minH, int p) {	// 下滤

	int parent, child;
	ElementType x;

	x = minH->Data[p];	// 每层根节点

	for (parent = p; parent * 2 <= minH->Size; parent = child) {

		child = parent * 2;   /* 先指向左子树 */

		if ((child != minH->Size) && (minH->Data[child] > minH->Data[child + 1])) {

			child++;    /* 调整，指向较小子树 */

		}

		if (x <= minH->Data[child]) {

			break;

		}
		else {

			minH->Data[parent] = minH->Data[child];

		}

	}

	minH->Data[parent] = x;

}


void bulidHeap(MinHpointer minH) {	// 将已存在的N个元素按最小堆的要求存放于一维数组中

	int i = 0;

	for (i = minH->Size / 2; i >= 1; i--) {

		percDown(minH, i);

	}

}


void output(MinHpointer minH) {

	int i = 0;

	for (i = 1; i <= minH->Size; i++) {

		printf("%4d", minH->Data[i]);

	}

}
