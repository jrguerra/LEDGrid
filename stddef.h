/*
 * stddef.h
 *
 *  Created on: Jul 18, 2014
 *      Author: jacob_000
 */

#ifndef STDDEF_H_
#define STDDEF_H_


#define NULL (void*) (0)

typedef enum {
	FALSE = 0,
	TRUE = 1
} BOOL, *PBOOL;

void
ZeroMemory(void* ptr, int size);

#endif /* STDDEF_H_ */
