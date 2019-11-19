#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include "Header.h"

#pragma warning(disable:4996)

/**
* 三种测试用例文件包含在static文件夹中
* author: Sun Ray
*/
int main() {

	Qpointer open = initialize();

	Ipointer begin = input(open);

	processBlock(open, begin);

	return 0;

}
