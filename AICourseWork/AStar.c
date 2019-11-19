#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include "Header.h"

#pragma warning(disable:4996)

/**
*  A* algorithm
* author: Sun Ray 2019.11.19
*/
void applyAStar(Cpointer closed, Ipointer node) {	// Ó¦ÓÃA*Ëã·¨

	Ipointer resultp = findUnique(closed, node);

	if (resultp != NULL) {

		if (getDeep(resultp) > getDeep(node)) {

			resultp->parent = node->parent;
			resultp->weight = node->weight;

		}

	}

	return;

}
