#pragma once

#define NSIZE sizeof(struct Node)
#define QSIZE sizeof(struct Queue)
#define ISIZE sizeof(struct Nine)

#define CSIZE sizeof(struct Closed)

#define MINDATA	1e-9	// 堆顶元素(a[0])：最小堆
#define ERROR -1
#define MAXCAPACITY 1e5	// 堆最大容量
#define ESIZE sizeof(ElementType)
#define HSIZE sizeof(struct Heap)

clock_t start, stop;   /* 起始时间与结束时间 */

typedef enum bool {   // 自建bool型

	False = 0,
	True,
	Unknown

} bool;


typedef enum Direction {   // 数据结构: 移动的方向

	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE

} Direction;


typedef struct Nine {	// 数据结构: 九宫格

	int digit[3][3];	// 九宫格阵列
	long unique;	// 九宫格转换后得到的序列
	int zero[2];	// "0" 的横、纵坐标：zero[0] = x(横坐标); zero[1] = y(纵坐标);
	Direction blockDirection;	// 禁止方向, 防止回退形成死循环
	struct Nine* parent;	// 父节点指针
	int weight;	// 节点权重

} Nine, * Ipointer;


typedef Ipointer ElementType;	// 元素类型置为Ipointer


typedef struct Heap {	// 最小堆

	ElementType* data;    /* 存储元素的数组 */
	int size;           /* 堆当前元素的个数 */
	int capacity;       /* 堆的最大容量 */
	int standard[3][3];	/* 标准九宫格 */
	int inversion;	  /* 标准九宫格的逆序数 */
	long unique;	/* 标准九宫格布局转换的long型串 */

} Heap, * Hpointer;

typedef Hpointer MinHpointer;

typedef struct Closed {	// 链表实现

	ElementType data;
	struct Closed* next;

} Closed, * Cpointer;


void insertNode(Cpointer headp, Ipointer node);
Ipointer findUnique(Cpointer headp, Ipointer node);
void applyAStar(Cpointer closed, Ipointer node);	// 应用A*算法

Cpointer getClosed(Ipointer begin);
bool isListEmpty(Cpointer headp);



/* -------------------- main主体操作 -------------------- */

MinHpointer initialize();	// 初始化函数

Ipointer input(MinHpointer open);	// 输入函数

void handle(MinHpointer open, Ipointer begin);	// 主要处理流程函数

void run(MinHpointer open, Ipointer begin);	// 处理块

bool isSuccess(int(*digit)[3], int unique);	// 是否成功找到标准九宫格

/* ----------------------------------------------------- */



/* ------------------- core function ------------------- */

long converseMatrix(const int(*nine)[3]);	// 九宫格--->序列转换函数

int countInverseNumber(long number);	// 查找逆序数的个数

long assistInverse(const int(*nine)[3]); // 辅助逆序函数：由于大部分雷同converseMatrix, 后期需要修改

int countBit(long number);	// 查询数字位数

void locateZeros(Ipointer node);	// 定位节点node的九宫格中 "0" 的坐标

Ipointer createNode(Ipointer nine);	// 创建九宫格结点

bool move(Ipointer node, Direction way);	// 移动

Direction getBlockDirection(Direction way);	// 获取回退方向

bool judgeParity(int begin, int open);	// 奇偶校验

int backtrack(Ipointer end);	// 回溯, 得到最终路径

/* --------------------------------------------------- */

void globalOptimizationFollow(MinHpointer open, Ipointer begin);	// 全局优化

void getWeight(MinHpointer open, Ipointer node);	// 获取权重

int getDeep(Ipointer node);	// 获取深度

/* ------------------- priority queue ------------------- */

MinHpointer createMinHeap(int maxSize, long unique, int inversion);
bool isFull(MinHpointer minH);
bool insertElement(MinHpointer minH, ElementType x);
bool isHeapEmpty(MinHpointer minH);
ElementType deleteMin(MinHpointer minH);
void percDown(MinHpointer minH, int p);
void bulidHeap(MinHpointer minH);
void outputHeap(MinHpointer minH);
