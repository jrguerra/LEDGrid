/*
 * Dot.c
 *
 *  Created on: Jul 18, 2014
 *      Author: jacob_000
 */

#include "stddef.h"
#include "Dot.h"

typedef struct {
	Dot Matrix[NUM_COLS][NUM_ROWS];
	int NumDots;	
} DotGlobalsType;

DotGlobalsType DotGlobals;

void DotInit() 
{
	return;
}

int DotAdd()
{
	return 0;
}

int DotCount()
{
	return DotGlobals.NumDots;
}

void DotMove(unsigned char index) 
{
	
}


