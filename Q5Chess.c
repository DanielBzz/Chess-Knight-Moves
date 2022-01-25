#include "Q5Chess.h"

void saveListToBinFile(char* file_name , chessPosList* pos_list) {

	chessPosCell* curr= pos_list->head;
	BYTE posMask, readBYTE;
	short int i = 1, j = 4;
	FILE* file = fopen(file_name, "wb");
	checkFile(file);
	
	short int sizeOfPos = countPosList(pos_list);		/* count how much pos we have in the list*/
	fwrite(&sizeOfPos, sizeof(short int), 1, file);		/* write the size of positions*/

	posMask = convertPosToBin(curr);			/* connvert the first pos to BYTE */
	curr = curr->next;								/* go to next pos*/
	
	if (curr == NULL) {						/* for the case that we get only one position in the list */
		readBYTE = posMask << (2);
		fwrite(&readBYTE, sizeof(BYTE), 1, file);
	}

	while (curr != NULL) {				/* while we still have positions */

		if (i == 4) {					/* it is cyclic every four positions we have exactly 3 BYTES and start over*/

			i = 1;
			j = 4;

			posMask = convertPosToBin(curr);			/* connvert the pos to BYTE */
			curr = curr->next;								/* go to next pos*/
		}
		
		readBYTE = posMask << (i * 2);				/* rearrange the BYTE according to the num of free bits */

		if (curr != NULL) {				/* this if is for the case that we have multiple of 4 plus 1 poses*/
			posMask = convertPosToBin(curr);		/* connvert the pos to BYTE */
			readBYTE |= (posMask >> j);				/* insert to the free bits part of the next pos */
			curr = curr->next;								/* go to next pos*/
		}

		fwrite(&readBYTE, sizeof(BYTE), 1, file);			/* write the BYTE*/

		i++;											/*counter  positions */
		j -= 2;

		if (curr == NULL) {						/* for the case that we get the last pos but insert just part of it */
			readBYTE = posMask << (i * 2);				
			fwrite(&readBYTE, sizeof(BYTE), 1, file);
		}
	}
	fclose(file);
}

BYTE convertPosToBin(chessPosCell* curr) {			/* get a position and turned it to 6 bits*/

	BYTE posMask;

	posMask = curr->position[0] - 'A';
	posMask = posMask << 3;					/* convert that pos to a byte*/

	posMask = posMask | (curr->position[1] - '1');

	return posMask;
}

short int countPosList(chessPosList* lst) {			/* counting how much pos we have*/

	short int size = 0;
	chessPosCell* curr = lst->head;
	
	while (curr != NULL) {
		size++;
		curr = curr->next;
	}
	return size;
}

void checkFile(FILE* file) {

	if (file == NULL) {
		printf(" open file failed \n");
		exit(1);
	}
}
