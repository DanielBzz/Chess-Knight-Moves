#include "Q6Chess.h"

int checkAndDisplayPathFromFile(char* file_name) {

	FILE* file = fopen(file_name, "rb");
	if (file == NULL) {
		return NOT_EXIST_FILE;
	}							//(if file does not exist return -1);
	short int sizeOfPos, i, counter=0;
	chessPosList posLst;
	bool rightMoves=true;

	makeEmptyList(&posLst);				/* initial the list */
	
	convertFileToList(&posLst , file);	/* get a file of positions and turned it to list of positions */

	chessPosCell* curr = posLst.head;

	while (curr->next != NULL && rightMoves ) {			/* check that every next move in the list is availabe*/
	
		rightMoves= checkIfRightMove(curr->next, curr->position);
		curr = curr->next;
	}
	if (!rightMoves) {						
		return NOT_LEGAL_PATH;
	}
	
	display(&posLst);				/* display the path on the board */
	
	counter = countList(posLst.head);		/* check how much positions in the list*/
	freeList(&posLst);
	return counter == ROW * COL ? NOT_COVER_BOARD : COVER_BOARD;
}

void convertFileToList(chessPosList* lst, FILE* file) {	/* get a file of positions and turned it to list of positions */

	short int i, sizeOfPos ,j=1;
	BYTE byteMask=0 ,  originalBYTEprev=0 , originalBYTEcurr=0 ;
	chessPos pos;
	
	fread(&sizeOfPos, sizeof(short int), 1, file);			/* read the size*/
	
	for (i = 1; i <= sizeOfPos; i++) { 

		fread(&originalBYTEcurr, sizeof(BYTE), 1, file);		/* read first byte*/

		byteMask = (originalBYTEcurr >> (j) * 2) | originalBYTEprev << (((j) * 6) % 8 ) ;	/*arrange the pos in one byte */

		convertThePosAndInsertToLst(byteMask, lst);		/* insert the pos we got to the end of the list */

		originalBYTEprev = originalBYTEcurr;			/* we finish with the prev so get the next and prev will be the curr in next iteration*/
	
		if (j == 3) {			/*j is cyclic counter for the BYTES every 3 bytes(4 pos) we initial the prev byte  */
			i++;
			if (i <= sizeOfPos) {
				convertThePosAndInsertToLst(originalBYTEprev, lst);
				j = 0;
				originalBYTEprev = 0;
			}
		}
		j++;
	}

	fclose(file);
}

void convertThePosAndInsertToLst(BYTE byteMask , chessPosList* lst) {

	chessPos pos;
	BYTE posMask;

	posMask = (byteMask & 0x3f );		/* the mask with 0011 1111*/

	pos[1] = '1' + (posMask & 7);		/* get the col*/

	posMask = posMask >> 3;
	pos[0] = 'A' + posMask;				/* get thr row*/

	insertDataToEndList(lst, pos);		/* insert to list*/
}

void insertDataToEndList(chessPosList* lst, chessPos pos) {

	chessPosCell* newTail;
	newTail = createNewCell(pos, NULL);
	insertNodeToEndList(lst, newTail);
}

void insertNodeToEndList(chessPosList* lst, chessPosCell* newTail)
{
	if (lst->head==NULL)
		lst->head = lst->tail = newTail;
	else
	{
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}

chessPosCell* createNewCell(chessPos pos, chessPosCell* next)
{
	chessPosCell* node = (chessPosCell*)malloc(sizeof(chessPosCell));
	checkMemoryAllocation(node);

	node->position[0] = pos[0];
	node->position[1] = pos[1];
	node->next = next;

	return node;
}

bool checkIfRightMove(chessPosCell* nextMove, chessPos currPos) {	/* check that the next move is possible */

	if (currPos[1] - TWO_STEP == nextMove->position[1]) {	
		if (currPos[0] + ONE_STEP == nextMove->position[0]) {

			return true;
		}
		if (currPos[0] - ONE_STEP == nextMove->position[0]) {
			return true;

		}
	}
	if (currPos[1] + TWO_STEP == nextMove->position[1]) {
		if (currPos[0] + ONE_STEP == nextMove->position[0]) {
		
			return true;
		}

		if (currPos[0] - ONE_STEP == nextMove->position[0]) {
		
			return true;
		}
	}
	if (currPos[0] - TWO_STEP == nextMove->position[0]) {
		if (currPos[1] - ONE_STEP == nextMove->position[1]) {
		
			return true;
		}
		if (currPos[1] + ONE_STEP == nextMove->position[1]) {
			return true;

		}
	}
	if (currPos[0] + TWO_STEP == nextMove->position[0]) {
		if (currPos[1] - ONE_STEP == nextMove->position[1]) {
			return true;

		}
		if (currPos[1] + ONE_STEP == nextMove->position[1]) {
		
			return true;
		}
	}

	return false;
}

short int countList(chessPosCell* head) {

	short int counter=0;
	chessPosCell* curr = head;

	while (curr != NULL) {

		counter++;
		curr = curr->next;
	}
	return counter;
}