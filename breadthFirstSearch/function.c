#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>
#include "Header.h"
#pragma warning(disable:4996)


/**
* sum为逆序数的个数
*/
int countInverseNumber(long number) { // 456

	int sum = 0;

	int bit = countBit(number); // 3 = countBit(456)

	int power = bit - 1; // 2

	long temp = number;

	while (temp != 0L) {

		int zero = (int)pow(10, power); // 10, 2

		long first = temp / zero;	// 456 / 100

		long follow = temp - first * zero;	// 456 - 4 * 100

		long sub = follow;

		while (sub != 0) {

			if (first > (sub % 10)) {

				sum++;

			}

			sub /= 10;

		}

		temp = follow;

		power--;

	}

	return sum;

}


long assistInverse(const int(*nine)[3]) {	// 逆序数辅助函数：由于和 converseMatrix 太过相似, 有机会会考虑重构

	long number = 0L;

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < 3; j++) {

			int temp = nine[i][j];

			if (temp != 0) {

				number = number * 10 + temp;

			}

		}

	}

	return number;

}


int countBit(long number) {	// 计算数字位数

	int bit = 0;

	while (1) {

		if (number % 10 != 0) {

			number = number / 10;
			bit++;

		}
		else {

			break;

		}

	}

	return bit;

}


/**
* 判断是否成功
*/
bool isSuccess(int(*digit)[3], int unique) {	// 是否找到标准九宫格

	if (converseMatrix(digit) == unique) {

		return True;	// digit九宫格布局 = 标准九宫格; 成功

	}
	else {

		return False;

	}

}


/**
* 九宫格 ---> long型串
* ps: 实际上转换成字符型更健壮！
*/
long converseMatrix(const int(*nine)[3]) {	// 将九宫格矩阵(二维数组), 从左到右、从上到下, 转换为一串数字

	long number = 0L;

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < 3; j++) {

			int temp = nine[i][j];	// 注：此处temp必须要能够取到 "0", 否则, 一定出错; 若加判断条件 if (temp != 0) X: 大错特错

			number = number * 10 + temp;

		}

	}

	return number;

}
