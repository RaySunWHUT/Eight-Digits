#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include "Header.h"

#pragma warning(disable:4996)

int main() {

	MinHpointer minH;
	int maxSize;
	int cnt;
	int i, j;
	int a[1000];

	printf("请输入最小堆容量：");
	scanf("%d", &maxSize);
	minH = createMinHeap(maxSize);

	printf("请输入元素的个数：");
	scanf("%d", &cnt);

	printf("请输入元素：");

	for (j = 1; j <= cnt; j++) {

		scanf("%d", &a[j]);
		minH->Data[j] = a[j];
		minH->Size++;

	}

	bulidHeap(minH);
	printf("\n建立的最小堆为：\n");
	output(minH);


	printf("\n插入元素9: \n");
	insert(minH, 9);

	output(minH);

	deleteMin(minH);
	printf("\n删除最大元素后的序列为: \n");
	output(minH);

	return 0;

}
