/*
 * Dot.h
 *
 *  Created on: Jul 18, 2014
 *      Author: Jacob Guerra
 */

#ifndef DOT_H_
#define DOT_H_

/*
#define MAX_DOTS 30
#define ROW_SIZE 5
#define COLUMN_SIZE 6

typedef struct {
	int x;
	int y;
	int vx;
	int vy;
} Dot, *PDot;
*/

//
// Defines
//

#define DOT_NUM_ROWS 2
#define DOT_NUM_COLS 5
#define DOT_MAX_DOTS (DOT_NUM_ROWS * DOT_NUM_COLS)

//
// Types
//

typedef struct {
	signed char x;
	signed char y;
} Vector, *PVector;

typedef struct {
	Vector vel;
	Vector loc;
	Vector NextLoc;
	BOOL Collision;
} Dot, *PDot;

//
// Initialization
//

void
Dot_Init(void);

//
// Generation
//

BOOL
Dot_CreateDot(Vector* location, Vector* veloc);


//
// Movement
//

void
Dot_MoveDots(void);

//
// Cleanup
//

//
// TODO: May need to update this fucntion with something else that represents
// slowly moving out all the stuff
//

#define Dot_RemoveAllDots() \
	Dot_Init()


#endif /* DOT_H_ */
