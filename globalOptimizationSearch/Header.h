#pragma once

#define MINDATA	1e-9	// 堆顶元素(a[0])：最小堆
#define ERROR -1
#define ESIZE sizeof(ElementType)
#define HSIZE sizeof(struct Heap)

typedef enum Status {

	False = 0,
	True

} Status;

typedef int ElementType;
typedef int bool;

typedef struct Heap {

	ElementType* Data;    /* 存储元素的数组 */
	int Size;           /* 堆当前元素的个数 */
	int Capacity;       /* 堆的最大容量 */

} Heap, * Hpointer;

typedef Hpointer MinHpointer;

MinHpointer createMinHeap(int maxSize);
bool isFull(MinHpointer minH);
bool insert(MinHpointer minH, ElementType x);
bool isEmpty(MinHpointer minH);
ElementType deleteMin(MinHpointer minH);
void percDown(MinHpointer minH, int p);
void bulidHeap(MinHpointer minH);
void output(MinHpointer minH);
