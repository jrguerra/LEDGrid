/*
 * stddef.c
 *
 *  Created on: Jul 18, 2014
 *      Author: jacob_000
 */

#include "stddef.h"

void
ZeroMemory(void* ptr, int size) {
	int index = 0;
	unsigned char* chPtr = (unsigned char*) ptr;
	for (index = 0; index < size; index ++) {
		chPtr[index] = 0;
	}
}



