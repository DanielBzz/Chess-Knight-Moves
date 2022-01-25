#include "Q2Chess.h"

void display(chessPosList* lst) {

	chessPosCell* curr, * temp, * prev;

	if (lst->head == lst->tail) {	/* check if the list is empty, or if there is one cell in the list we also return */
		return;
	}
	else {

		temp = lst->head;		/* temp be the head */

		while (temp != NULL) {
			prev = temp;		/* prev be the temp every time we start the while */
			curr = temp->next;			/* curr be the second node*/

			while (curr != NULL) {		/*the curr run on the list , and compare every cell to the temp */

				if (checkIfEqual(temp->position, curr->position)) {

					removeCell(prev);		/* if is equal remove the curr*/
					curr = prev->next;
				}
				else {
					prev = curr;
					curr = curr->next;
				}
			}
			temp = temp->next;
		}
	}
	putTheLocatoionsOnTheBoard(lst);
}

bool checkIfEqual(chessPos first, chessPos second) {		/*checking if 2 cells are equal*/

	if (first[0] != second[0])
		return false;
	if (first[1] != second[1])
		return false;

	return true;
}

void removeCell(chessPosCell* after) {

	chessPosCell* toDelete;

	toDelete = after->next;
	after->next = toDelete->next;
	free(toDelete);
}

void putTheLocatoionsOnTheBoard(chessPosList* lst) {		/* put the locations on the board before we print it  */

	int board[ROW][COL] = { 0 };
	chessPosCell* curr = lst->head;
	int i, j;
	int counter = 1;

	//for (i = 0; i < ROW; i++) {				/* initial the board to spaces(empty cells)*/
	//	for (j = 0; j < COL; j++) {
	//		board[i][j] = ' ';
	//	}
	//}

	while (curr != NULL) {					/* when the cell appear in the list so we put number that represent the place in the list */

		i = (int)(curr->position[0] - 'A');
		j = (int)(curr->position[1] - '1');

		board[i][j] = counter;
		counter++;

		curr = curr->next;
	}

	printChessBoard(board, ROW, COL);
}

void printChessBoard(int board[][COL], int row, int col) {		/* print all the board*/

	int i, j;

	for (i = 0; i <= row; i++) {
		if (i == 0) {
			printf(" |");
		}
		else {
			printf("%3d  |", i);
		}
	}
	printf("\n_|_____|_____|_____|_____|_____|_____|");
	
	for (i = 0; i < row; i++) {
		printf("\n");

		printf("%c|", 'A' + i);
		
		for (j = 0; j < col; j++) {
			if (board[i][j] == 0) {
				printf("     |", board[i][j]);
			}
			else {
				printf("%3d  |", board[i][j]);
			}
		}
		printf("\n_|_____|_____|_____|_____|_____|_____|");
	}
	printf("\n");

}