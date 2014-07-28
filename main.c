#include <msp430g2553.h>
#include "stddef.h"
#include "Dot.h"

/*
 * main.c
 * Created by Jacob Guerra
 */
/*
#define WAIT_PERIOD(index, cycles) \
	for (index = 0; index < cycles; index ++) { \
		; \
	} \

#define OUTPUT_MASK 0x80

#define CLOCK_LOW() \
	P1OUT &= 0xF7

#define CLOCK_HIGH() \
	P1OUT |= 0x08

#define SET_OUTPUT(val) \
	P1OUT &= 0xF8; \
	P1OUT |= val

typedef enum {
	AM = 0,
	PM = 1
} TimePostfix;

typedef struct {
	unsigned long Ticks; // this is a tenth of a second
	unsigned long Seconds;
	unsigned long Minute;
	unsigned long Hour;
	TimePostfix Postfix;
	Dot Dots[MAX_DOTS];
	Dot* Screen[ROW_SIZE][COLUMN_SIZE];
	unsigned int NumDots;
	BOOL StateChanged;
	unsigned long Output;

} ClockGlobals, *PClockGlobals;

ClockGlobals Globals;


void
InitGlobals()
{
	unsigned short index;

	WDTCTL = WDTPW | WDTHOLD;

    P1DIR |= 0x1F;
    P1OUT = 0x08;

    WAIT_PERIOD(index, 500);

    P1OUT |= 0x10; // this clears the output

    CCTL0 = CCIE;
    TACTL = TASSEL_2 + MC_1 + ID_3; // clock is 125 kHz
    CCR0 = 12500;
    CCR1 =

    _BIS_SR(GIE); // + CPUOFF);

    ZeroMemory(&Globals, sizeof(ClockGlobals));
}

void
SerialOut(
	unsigned long output
	)
{
	unsigned char out1;
	unsigned char out2;
	unsigned char out3;

	unsigned short index = 0;
	unsigned char shiftIndex = 0;
	unsigned char pinOut = 0;

	out1 = (output & 0x000000FF);
	out2 = ((output >> 8) & 0x000000FF);
	out3 = ((output >> 16) & 0x000000FF);

	while (shiftIndex < 8) {
		WAIT_PERIOD(index, 5);
		CLOCK_LOW();

		pinOut = 0;

		if (out1 & OUTPUT_MASK) {
			pinOut |= 0x01;
		}

		if (out2 & OUTPUT_MASK) {
			pinOut |= 0x02;
		}

		if (out3 & OUTPUT_MASK) {
			pinOut |= 0x04;
		}

		SET_OUTPUT(pinOut);

		WAIT_PERIOD(index, 5);

		CLOCK_HIGH();
		shiftIndex ++;

		out1 = out1 << 1;
		out2 = out2 << 1;
		out3 = out3 << 1;
	}
}

void
SetBit(int x, int y, BOOL set)
{
	int offset = 0;
	unsigned long mask = 0;

	if (x > 4) {
		return;
	}

	if (y > 5) {
		return;
	}

	offset = (y*5) + x;

	mask = 1 << offset;


	if (set) {
		Globals.Output |= mask;
	} else {
		Globals.Output &= ~(mask);
	}
}

BOOL
AddDot(unsigned int x, unsigned int y, int vx, int vy)
{
	unsigned dotNumber;
	if (Globals.NumDots >= MAX_DOTS) {
		return FALSE;
	}

	if (x > ROW_SIZE || y > COLUMN_SIZE) {
		return FALSE;
	}

	if (Globals.Screen[x][y] != NULL) {
		return FALSE;
	}

	dotNumber = Globals.NumDots;
	InitDot(&Globals.Dots[dotNumber]);

	Globals.Dots[dotNumber].x = x;
	Globals.Dots[dotNumber].y = y;
	Globals.Dots[dotNumber].vx = vx;
	Globals.Dots[dotNumber].vy = vy;

	Globals.NumDots ++;
	Globals.Screen[x][y] = &Globals.Dots[dotNumber];
	return TRUE;
}

void
MoveDot(PDot dot)
{
	int newx;
	int newy;
	BOOL dotMoved = FALSE;
	int oldx = dot->x; int oldy = dot->y;
	BOOL HitWall = FALSE;

CalculateX:
	newx = dot->x + dot->vx;
	if (newx > 4 || newx < 0) {
		dot->vx *= -1;
		HitWall = TRUE;
		goto CalculateX;
	}


	if (Globals.Screen[newx][oldy] != NULL && HitWall == FALSE) {
		dot->vx *= -1;
		goto CalculateX;
	} else if (Globals.Screen[newx][oldy] != NULL) {
		newx = oldx;
	}
	*/

	/*if (Globals.Screen[newx][oldy] != NULL) {
			newx = oldx;
	}

	HitWall = FALSE;

CalculateY:
	newy = dot->y + dot->vy;
	if (newy > 1 || newy < 0) {
		dot->vy *= -1;
		HitWall = TRUE;
		goto CalculateY;
	}
	if (Globals.Screen[oldx][newy] != NULL && HitWall == FALSE) {
		dot->vy *= -1;
		goto CalculateY;
	} else if (Globals.Screen[oldx][newy] != NULL) {
		newy = oldy;
	}
*/
/*
	if (Globals.Screen[oldx][newy] != NULL) {
			newy = oldy;
	}

	dot->x = newx;
	dot->y = newy;
	dotMoved = TRUE;

	if (dotMoved) {
		SetBit(oldx, oldy, FALSE);
		SetBit(dot->x, dot->y, TRUE);

		Globals.Screen[oldx][oldy] = NULL;
		Globals.Screen[dot->x][dot->y] = dot;
	}
}

void MoveDots()
{
	int i;

	for (i = 0; i < Globals.NumDots; i ++) {
		MoveDot(&Globals.Dots[i]);
	}
}

void PrintScreen()
{
	SerialOut(~Globals.Output);
}
*/

int main(void) {
/*
	BOOL Print = FALSE;

	InitGlobals();

	AddDot(0, 0, 1, 1);
	AddDot(0, 1, 1, 0);

    while (1) {
    	Print = FALSE;

    	_disable_interrupts();
    	if (Globals.StateChanged == TRUE) {
    		Print = TRUE;
    		Globals.StateChanged = FALSE;
    	}
    	_enable_interrupts();

    	if (Print) {
    		MoveDots();
    		PrintScreen();
    	}
    }
    */

}


#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
	/*
	Globals.Ticks ++;

	if (Globals.Ticks % 5 == 0) {
		Globals.Seconds ++;
		Globals.StateChanged = TRUE;
	}
	*/
}


