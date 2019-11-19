#pragma once

#define NSIZE sizeof(struct Node)
#define QSIZE sizeof(struct Queue)
#define ISIZE sizeof(struct Nine)

#define CSIZE sizeof(struct Closed)

#define HSIZE sizeof(struct Helper)

#define MAXK 10e1  /* 测试函数重复调用的次数 */

clock_t start, stop;   /* 起始时间与结束时间 */

typedef enum bool{   // 自建bool型

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


typedef struct Node {	/* 数据结构: 队列中的结点 */

	ElementType Data;
	struct Node* Next;

} Node, * Npointer;


typedef struct Helper {	// 辅助handle函数的结构体

	bool flag;
	Ipointer end;

} Helper, * Hpointer;

void helper(Hpointer helper, char name[]);

Hpointer store[3];	/* 存储三种结果 */


typedef struct Closed {	// 链表实现

	ElementType Data;
	struct Closed* Next;

} Closed, * Cpointer;

Cpointer createClosed();
void insertNode(Cpointer headp, Ipointer node);
Ipointer findUnique(Cpointer headp, Ipointer node);
void applyAStar(Cpointer closed, Ipointer node);	// 应用A*算法

Cpointer getClosed(Ipointer begin);
void dostoryClosed(Cpointer headp);


typedef struct Queue {	// 队列

	Npointer Front, Rear;    /* 队头，队尾指针 */
	int MAXSize;                   /* 队列最大容量 */
	int standard[3][3];	/* 标准九宫格 */
	int inversion;	  /* 标准九宫格的逆序数 */
	long unique;	/* 标准九宫格布局转换的long型串 */

} Queue, * Qpointer;


/* ------------------ queue function ------------------ */

Qpointer createQueue(int MAXSize, long unique, int inversion);	// 创建队列

bool isEmpty(Qpointer headp);	// 队列判空

Qpointer addQ(Qpointer headp, ElementType X);	// 入队

Ipointer deleteQ(Qpointer headp);	// 修改后的出队操作

void output(Qpointer headp);	// 队列输出函数：本次实验基本没有使用; 仅做测试函数

void destoryQ(Qpointer headp);	// 清空队列元素
/* ----------------------------------------------------- */



/* -------------------- main主体操作 -------------------- */

Qpointer initialize();	// 初始化函数

Ipointer input(Qpointer open);	// 输入函数

Hpointer handle(Qpointer open, Ipointer begin, int order, Cpointer closed);	// 主要处理流程函数

bool isSuccess(int sequence, int unique);	// 是否成功找到标准九宫格

/* ----------------------------------------------------- */



/* ------------------- core function ------------------- */

long converseMatrix(const int(*nine)[3]);	// 九宫格--->序列转换函数

int countInverseNumber(long number);	// 查找逆序数的个数

long assistInverse(const int(*nine)[3]); // 辅助逆序函数：由于大部分雷同converseMatrix, 后期需要修改

int countBit(long number);	// 查询数字位数

void locateZeros(Ipointer node);	// 定位节点node的九宫格中 "0" 的坐标

void breadthFirstSearchFollow(Qpointer open, Ipointer begin);	// 寻找后继

Ipointer generateNewLayout(Ipointer nine);	// 创建新的九宫格结点

bool move(Ipointer node, Direction way);	// 移动

Direction getBlockDirection(Direction way);	// 获取回退方向

bool judgeParity(int begin, int open);	// 奇偶校验

int backtrack(Ipointer end);	// 回溯, 得到最终路径

/* --------------------------------------------------- */

void globalOptimizationFollow(Qpointer open, Ipointer begin);	// 全局优化

void weightSort(ElementType A[], int N);	// 权重排序: 利用插入排序

void getWeight(Qpointer open, Ipointer node);	// 获取权重

int getDeep(Ipointer node);	// 获取深度

void print(ElementType A[], int N);	// 测试用

void run(Qpointer open, Ipointer begin, int order, char name[], Cpointer closed);  /* 时间测试函数 */

void processBlock(Qpointer open, Ipointer begin);	// 程序块: 封装使用
