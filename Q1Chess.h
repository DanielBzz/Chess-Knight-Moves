#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROW 5
#define COL 5
#define MAX_KNIGHT_MOVES 8

typedef char chessPos[2];		// ***** maybe define as 0 - row letter , 1 - coll number

typedef struct _chessPosArray {
	unsigned int size;
	chessPos* positions;
}chessPosArray;

chessPosArray*** validKnightMoves();							/* return the board with all the valid knight moves for all the positions */
chessPosArray* validKnightMovesInPos(int row, int col);			/*get the valid knight moves and the size for one position on the board */
void checkMemoryAllocation(void* arr);
void freeKnightPos(chessPosArray*** arr);						/*free chessPosArray*** */
