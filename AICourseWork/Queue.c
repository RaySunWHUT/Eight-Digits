#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<string.h>
#include"Header.h"

#pragma warning(disable:4996)

/**
* queue operation
* author: Sun Ray 2019.11.19
*	创建队列,
*	unique: 标准九宫格的布局;
*	inversion: 标准九宫格的逆序数;
*	number: 已存在九宫格布局数量;
*	headp->nine[100]: 用来存储已经存在的九宫格布局;
*/
Qpointer createQueue(int MAXSize, long unique, int inversion) {

	Qpointer headp = NULL;
	headp = (Qpointer)malloc(QSIZE);
	headp->Front = headp->Rear = NULL;
	headp->MAXSize = MAXSize;
	headp->inversion = inversion;
	headp->unique = unique;

	return headp;

}


bool isEmpty(Qpointer headp) {

	return (headp->Front == NULL);

}


Qpointer addQ(Qpointer headp, ElementType X) {

	Npointer nodep = NULL;

	if (isEmpty(headp)) {

		nodep = (Npointer)malloc(NSIZE);
		nodep->Data = X;
		nodep->Next = NULL;
		headp->Front = nodep;
		headp->Rear = nodep;

	}
	else {

		nodep = (Npointer)malloc(NSIZE);      /*  pList list = (pList)malloc(sizeof(lis)); */
		nodep->Data = X;                      /*  list->element = element; */
		nodep->Next = NULL;
		headp->Rear->Next = nodep;            /*  list->next = queue->rear->next; */
		headp->Rear = headp->Rear->Next;      /*  queue->rear->next = list; */
											  /*  queue->rear = list; */

	}

	return headp;

}


Ipointer deleteQ(Qpointer headp) {

	Npointer Front = NULL;

	if (isEmpty(headp)) {

		printf("The Queue is empty!\n");

	}
	else {

		Front = headp->Front;

		if (headp->Front == headp->Rear) {    /* 若队列中只有一个结点 */

			headp->Front = headp->Rear = NULL;

		}
		else {

			headp->Front = headp->Front->Next;

		}

		//free(Front);	// 因为要回溯生成路径, 所以, 此处取消free()操作

	}

	return Front->Data;	// 返回出队元素

}


void output(Qpointer headp) {	// 输出队列

	Npointer Front = headp->Front;

	printf("------------------ \n");

	while (Front != NULL) {

		for (int i = 0; i < 3; i++) {

			for (int j = 0; j < 3; j++) {

				printf("%3d", Front->Data->digit[i][j]);

			}

			printf("\n");

		}

		Front = Front->Next;

		printf("------------------ \n");

	}

}


void destoryQ(Qpointer headp) {	// 清空队列中的所有元素

	Npointer front = NULL;

	Npointer last = NULL;

	front = headp->Front;

	while (!isEmpty(headp)) {

		if (headp->Front == headp->Rear) {    /* 若队列中只有一个结点 */

			headp->Front = headp->Rear = NULL;

		}
		else {

			headp->Front = headp->Front->Next;

		}

		last = front;

		front = front->Next;

		free(last);	// 因为要回溯生成路径, 所以, 此处取消free()操作

	}

}
