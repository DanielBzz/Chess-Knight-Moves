#pragma once
#include "Q1Chess.h"

typedef struct _chessPosCell {
	chessPos position;
	struct _chessPosCell* next;
}chessPosCell;

typedef struct _chessPosList {
	chessPosCell* head;
	chessPosCell* tail;
}chessPosList;

void display(chessPosList* lst);								/*  */
bool checkIfEqual(chessPos first, chessPos second);				/*checking if 2 cells are equal*/
void removeCell(chessPosCell* after);							/* delete cell from the list that apears more than one */
void putTheLocatoionsOnTheBoard(chessPosList* lst);				/* get a list and initalize the board with the locations in the list  */
void printChessBoard(char board[][COL], int row, int col);			/* print the board  */