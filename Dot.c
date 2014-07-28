/*
 * Dot.c
 *
 *  Created on: Jul 18, 2014
 *      Author: jacob_000
 */

#include "stddef.h"
#include "Dot.h"

//
// Algorithm for dots:
// Keep list of dots and a matrix with their location
// When we move, calculate the collisions that may occur and determine
// new movement
// Then actually move the dots
//

//
// Internal defines
//

#define DOT_EMPTY 0xFF

#define DOT_NO_COLLISION 0
#define DOT_WALL_COLLISION 1
#define DOT_DOT_COLLISION 2

#define DOT_MAX_COLLISIONS 8

#define Dot_SetIndexVector(vector, index) \
	*(vector) |= (1 << index)

#define Dot_ClearIndexVector(vector, index) \
	*(vector) &= ~(1 << index)

//
// Internal Structs
//

typedef struct {
	unsigned char Indices[DOT_MAX_COLLISIONS];
	unsigned char NumCollisions;
} Collision;

typedef union {

	struct {
		unsigned long DotVector : 30;
		unsigned long CollisionType : 2;
	} c;

	unsigned long val;

} CollisionVector;

typedef struct {

	Dot Dots[DOT_MAX_DOTS];
	unsigned char DotIndices[DOT_NUM_ROWS][DOT_NUM_COLS];
	CollisionVector CollisionMatrix[DOT_NUM_ROWS][DOT_NUM_COLS];
	unsigned char NumDots;

} DotGlobals;

DotGlobals Dot_Globals;

//
// Private functions
//

BOOL
FindNextSetBit(unsigned long matrix, unsigned char* index, BOOL reset)
{
	static unsigned char bitindex;
	if (reset) {
		bitindex = 0;
	}

	for (; bitindex < 32; bitindex ++) {
		if (matrix & (1 << bitindex)) {
			*index = bitindex;
			bitindex ++;
			return TRUE;
		}
	}

	return FALSE;
}

BOOL
FindNextClearBit(unsigned long matrix, unsigned char* index, BOOL reset)
{
	static unsigned char bitindex;
	if (reset) {
		bitindex = 0;
	}

	for (; bitindex < 32; bitindex ++) {
		if ((matrix & (1 << bitindex)) == 0) {
			*index = bitindex;
			bitindex ++;
			return TRUE;
		}
	}

	return FALSE;
}

//
// Initialization
//

void
Dot_Init(void)
{
	unsigned short i = 0;
	unsigned short j = 0;
	//
	// Initialize the globals
	//

	ZeroMemory(&Dot_Globals, sizeof(Dot_Globals));

	//
	// Set the matrix to empty dots
	//

	for (i = 0; i < DOT_NUM_ROWS; i ++) {

		for (j = 0; j < DOT_NUM_COLS; j ++) {
			Dot_Globals.DotIndices[i][j] = DOT_EMPTY;
		}

	}
}

//
// Generation
//

BOOL
Dot_CreateDot(Vector* location, Vector* veloc)
{
	unsigned char index;
	PDot DotPointer;

	//
	// Check to see if we can add a new dot
	//

	if (Dot_Globals.NumDots >= DOT_MAX_DOTS) {
		return FALSE;
	}

	if (Dot_Globals.DotIndices[location->x][location->y] != DOT_EMPTY) {
		return FALSE;
	}

	index = Dot_Globals.NumDots;

	DotPointer = &Dot_Globals.Dots[index];
	ZeroMemory(DotPointer, sizeof(Dot));

	DotPointer->vel = *veloc;
	DotPointer->loc = *location;
	Dot_Globals.DotIndices[location->x][location->y] = index;
	Dot_Globals.NumDots ++;

	return TRUE;
}

//
// Movement
//


void
SetCollisionMatrix(void)
{

	unsigned char index = 0;
	signed char newx = 0;
	signed char newy = 0;
	unsigned char ctype = DOT_NO_COLLISION;
	PDot dot = NULL;

	//
	// TODO: Check to see if this works
	//

	ZeroMemory(Dot_Globals.CollisionMatrix, sizeof(Dot_Globals.CollisionMatrix));

	for (index = 0; index < Dot_Globals.NumDots; index ++) {
		dot = &(Dot_Globals.Dots[index]);

		newx = dot->loc.x + dot->vel.x;
		newy = dot->loc.y + dot->vel.y;

		ctype = DOT_NO_COLLISION;
		if (newx >= DOT_NUM_ROWS || newx < 0) {
			ctype |= DOT_WALL_COLLISION;
			newx = dot->loc.x;
		}

		if (newy >= DOT_NUM_COLS || newy < 0) {
			ctype |= DOT_WALL_COLLISION;
			newy = dot->loc.y;
		}

		if (Dot_Globals.CollisionMatrix[newx][newy].c.DotVector != 0) {
			ctype |= DOT_DOT_COLLISION;
		}

		Dot_Globals.CollisionMatrix[newx][newy].c.DotVector |= (1 << index);
		Dot_Globals.CollisionMatrix[newx][newy].c.CollisionType |= ctype;
	}
}

BOOL
GetCollision(Collision* pcol, unsigned long vector)
{
	unsigned char index;

	if (!FindNextSetBit(vector, &index, TRUE)) {
		return FALSE;
	}

	ZeroMemory(pcol, sizeof(Collision));

	pcol->Indices[0] = index;
	pcol->NumCollisions ++;

	while (FindNextSetBit(vector, &index, FALSE)) {
		pcol->Indices[pcol->NumCollisions] = index;
		pcol->NumCollisions ++;
	}

	if (pcol->NumCollisions == 1) {
		return FALSE;
	}

	return TRUE;
}

//
// Proposed:
// 1. Start off by calculating every dot's next location and updating a
//	  collision matrix.
// 2. Go through each hole and look for a collision
// 3. If a hole has a collision, determine which dots are involved
// 4. Set those dots with a collision value of true
// 5. Redo their vectors
// 6. Do not create any new collisions
// 5. Move all not collided dots
// 6.

void
Dot_MoveDots(void)
{

	unsigned char i, j;

	Collision collision;

	//
	// First, let's see if there are potential collisions through a first pass
	//

	SetCollisionMatrix();

	for (i = 0; i < DOT_NUM_ROWS; i ++) {
		for (j = 0; j < DOT_NUM_COLS; j ++) {

			if (GetCollision(&collision, Dot_Globals.CollisionMatrix[i][j].c.DotVector)) {
				//
				// We have a collision
				// Do something
				//
			} else {
				//
				// Move the dot and mark it moved
				//
			}

		}
	}

	//
	// Then, look to see if there are any remaining collisions,
	// those dots don't move
	//

	//
	// Set the screen approriately
	//

}


