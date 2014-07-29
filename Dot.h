/*
 * Dot.h
 *
 *  Created on: Jul 18, 2014
 *      Author: Jacob Guerra
 */

#ifndef DOT_H_
#define DOT_H_

//
// This file should contain all the declarations to move, create, and store
// dot movement.
//

//
// Defines
//

#define NUM_ROWS 2
#define NUM_COLS 5

#define MAX_NUM_DOTS (NUM_ROWS) * (NUM_COLS)

//
// Structs
//

typedef struct {
	signed char x;
	signed char y;
} Vector, *PVector;

typedef struct {
	Vector veloc;
	Vector pos;
} Dot, *PDot;

//
// Functions
//

void DotInit();

int DotAdd();

int DotCount();

void DotMove(unsigned char index);

#define DotClear() \
    DotInit()

#endif /* DOT_H_ */
