#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>

#include "Header.h"

#pragma warning(disable:4996)

/*
 author: Sun Rui
 time: 2018-09-22
*/
void insertNode(Cpointer headp, Ipointer node) {
	
	Cpointer newp = (Cpointer)malloc(CSIZE);

	newp->data = node;

	newp->next = NULL;

	if (isListEmpty(headp)) {

		headp->next = newp;

	} else {

		Cpointer p = headp->next;
		
		headp->next = newp;

		newp->next = p;
	
	}

}


bool isListEmpty(Cpointer headp) {

	if (headp->next == NULL) {

		return True;

	}

	return False;

}



Ipointer findUnique(Cpointer headp, Ipointer node) {

	Cpointer p = headp->next;

	while (p != NULL) {

		if (node->unique == p->data->unique) {	// ÈôÕÒµ½¸ÃÔªËØ

			return p->data;

		}

		p = p->next;

	}

	return NULL;

}


Cpointer getClosed(Ipointer begin) {

	Cpointer closed = (Cpointer)malloc(CSIZE);
	
	closed->data = NULL;
	
	closed->next = NULL;

	insertNode(closed, begin);

	return closed;

}
