#include "Q1Chess.h"

chessPosArray*** validKnightMoves() {

	chessPosArray*** chessBoard;
	int i, j, h;

	chessBoard = (chessPosArray***)malloc(ROW * sizeof(chessPosArray**));
	checkMemoryAllocation(chessBoard);

	for (i = 0; i < ROW; i++) {
		chessBoard[i] = (chessPosArray**)malloc(COL * sizeof(chessPosArray*));
		checkMemoryAllocation(chessBoard[i]);

	}

	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			chessBoard[i][j] = validKnightMovesInPos(i, j);
		}
	}

	return chessBoard;
}

chessPosArray* validKnightMovesInPos(int row, int col) {

	chessPosArray* resPos;
	resPos = (chessPosArray*)malloc(sizeof(chessPosArray));
	checkMemoryAllocation(resPos);

	int size = 0, i;
	resPos->positions = (chessPos*)malloc(MAX_KNIGHT_MOVES * sizeof(chessPos));		/* initialize chesPos array to valid knight moves from one pos */
	checkMemoryAllocation(resPos->positions);

	if (col - 2 >= 0) {					/* check if the knight move availabe */
		if (row + 1 < ROW) {
			resPos->positions[size][0] = 'A' + row + 1;
			resPos->positions[size][1] = '1' + col - 2;

			size++;
		}
		if (row - 1 >= 0) {
			resPos->positions[size][0] = 'A' + row - 1;
			resPos->positions[size][1] = '1' + col - 2;

			size++;
		}
	}
	if (col + 2 < COL) {
		if (row + 1 < ROW) {
			resPos->positions[size][0] = 'A' + row + 1;
			resPos->positions[size][1] = '1' + col + 2;

			size++;
		}

		if (row - 1 >= 0) {
			resPos->positions[size][0] = 'A' + row - 1;
			resPos->positions[size][1] = '1' + col + 2;

			size++;
		}
	}
	if (row - 2 >= 0) {
		if (col - 1 >= 0) {
			resPos->positions[size][0] = 'A' + row - 2;
			resPos->positions[size][1] = '1' + col - 1;

			size++;
		}
		if (col + 1 < COL) {
			resPos->positions[size][0] = 'A' + row - 2;
			resPos->positions[size][1] = '1' + col + 1;

			size++;
		}
	}
	if (row + 2 < ROW) {
		if (col - 1 >= 0) {
			resPos->positions[size][0] = 'A' + row + 2;
			resPos->positions[size][1] = '1' + col - 1;

			size++;
		}
		if (col + 1 < COL) {
			resPos->positions[size][0] = 'A' + row + 2;
			resPos->positions[size][1] = '1' + col + 1;

			size++;
		}
	}

	if (size != MAX_KNIGHT_MOVES) {

		resPos->positions = (chessPos*)realloc(resPos->positions, size * sizeof(chessPos));
		checkMemoryAllocation(resPos->positions);
	}
	resPos->size = size;

	return resPos;
}

void checkMemoryAllocation(void* arr) {

	if (arr == NULL) {
		printf("Memory allocation failed! \n");
		exit(1);
	}
}

void freeKnightPos(chessPosArray*** arr) {		/* free the memory we allocate*/
	int i, j, h;

	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			free((arr[i][j])->positions);
			free(arr[i][j]);
		}
		free(arr[i]);
	}

	free(arr);
}