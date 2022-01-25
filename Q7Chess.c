#include "Q7Chess.h"

void printMenu(){
	printf("--------------------------------------------------------\n");
	printf("Please enter your choose from the following options:\n");
	printf("1. Enter a knight starting move\n");
	printf("2. Create all possible knight path\n");
	printf("3. Find a knight path covering all board\n");
	printf("4. Save knight path covering all board to file\n");
	printf("5. Load and display path from file\n");
	printf("6. Exit\n");
	printf("--------------------------------------------------------\n");
}

void startActions() {

	int choice ,res;
	chessPos pos;
	bool OkPos = false, OkTree = false, OkList = false;
	pathTree tree;
	chessPosList* list=NULL;
	char* fileNameCase4 , *fileNameCase5;

	scanf("%d", &choice);			/* get the action*/
	
	while (choice > EXIT || choice < GETPOS) {
		printf("-----------------------------\n");
		printf("Please enter availabe option:\n");
		printf("-----------------------------\n");
		getchar();
		scanf("%d", &choice);			/* get the action*/

	}

	while (choice != EXIT) {			/* not exit */

		switch (choice) {
		case GETPOS:
			getStartingPos(&OkPos, &pos);		/* get the position*/
			OkTree = false;					/* still there is no tree for that pos*/
			OkList = false;					/* still there is no list for that pos*/
			break;
		case CREATETREE:
			if (OkPos == false) {			/* if the user skip option one*/
				getStartingPos(&OkPos, &pos);
			}
			tree = findAllPossibleKnightPaths(&pos);		/* create tree*/
			OkTree = true;									/* there is a tree*/
			break;
		case FINDPATH:
			if (OkPos == false) {					/* if the user skip option one*/
				getStartingPos(&OkPos, &pos);
			}
			if (OkTree == false) {					/* if the user skip option two*/
				tree = findAllPossibleKnightPaths(&pos);
				OkTree = true;
			}
			list = findKnightPathCoveringAllBoard(&tree);	/* create list for covered board path*/

			if (list == NULL) {					/* if there is'nt path that cover*/
				printf("------------------------------------------------------------\n");
				printf("There isn't a path that covered all board from that position\n");
				printf("------------------------------------------------------------\n");
			}
			OkList = true;				/* we get a list or we check and get null still*/
			break;
		case CREATEFILE:
			if (OkPos == false) {					/* if the user skip option one*/
				getStartingPos(&OkPos, &pos);

			}
			if (OkTree == false) {					/* if the user skip option two*/
				tree = findAllPossibleKnightPaths(&pos);
				OkTree = true;
			}
			if (OkList == false) {					/* if the user skip option tree*/
				list = findKnightPathCoveringAllBoard(&tree);	
				OkList = true;
			}
			if (list != NULL) {						/* if there is list save it to file*/
				fileNameCase4 = getNameOfFile();
				saveListToBinFile(fileNameCase4, list);
				free(fileNameCase4);
			}
			else {
				printf("------------------------------------------------------------\n");
				printf("There isn't a path that covered all board from that position\n");
				printf("------------------------------------------------------------\n");
			}
			break;
		case CHECKFILE:
			fileNameCase5 = getNameOfFile();
			res = checkAndDisplayPathFromFile(fileNameCase5);		/* get name and check the list*/

			displayRes(res, fileNameCase5);				/* print the result of the prev function */
			free(fileNameCase5);

			break;
		}
		printMenu();
		scanf("%d", &choice);
	}
	if (OkTree) {
		freePathTree(tree);
	}
	if (list != NULL) {

		freeList(list);
		free(list);
	}
	printf("--------------------------------\n");
	printf("see you in the next semester! :)");
	printf("--------------------------------\n");

}

void getStartingPos(bool* OkPos, chessPos* pos ) {			/* get a pos and check if it valis pos */

	char row, col;
		printf("-------------------------------\n");
		printf("Please enter starting position: \n");
		printf("-------------------------------\n");

		getchar();
		scanf("%c %c", &row , &col);

		*OkPos = checkPos(row, col);
		while (*OkPos == false) {
			printf("-------------------------------\n");
			printf("You Entered Invalid Position!\n ");
			printf("Please enter starting position: \n");
			printf("-------------------------------\n");

			getchar();

			scanf("%c %c", &row, &col);

			*OkPos = checkPos(row, col);
		}
		*pos[0] = row;
		(*pos)[1] = col;

	return pos;
}

bool checkPos(char row , char col) {			/* check the pos */
	
	if (row > 'H' || row < 'A') {
		return false;
	}
	if (col > '9' || col < '1') {
		return false;
	}
	return true;
}

char* getNameOfFile() {						/* get a string name from the user */
	
	int phySize = 2, logSize = 0;
	char* fileName=(char*)malloc(sizeof(char)* phySize);
	printf("-----------------------\n");
	printf("Please enter file name:\n");
	printf("-----------------------\n");

	getchar();

	char c = getchar();

	while (c != '\n' && c != ' ' ) {

		fileName[logSize] = c;

		logSize++;

		if (logSize == phySize) {
			phySize *= 2;
			fileName = (char*)realloc(fileName, sizeof(char) * phySize);
		}
		c = getchar();
		

	}
	fileName[logSize] = '\0';;
	logSize++;
	
	if (logSize != phySize) {
		fileName = (char*)realloc(fileName, sizeof(char) * logSize);

	}
	return fileName;
}

void displayRes(int res, char* fileNameCase5) {		/* print the result of the finction 5 of checking the file*/

	if (res == NOT_EXIST_FILE) {
		printf("-------------------------\n");
		printf("\nThe file %s not exist! \n", fileNameCase5);
		printf("-------------------------\n");

	}
	if (res == NOT_LEGAL_PATH)
	{
		printf("------------------\n");
		printf("\nNot legal path! \n");
		printf("------------------\n");
	}
	if (res == NOT_COVER_BOARD)
	{
		printf("----------------------\n");
		printf("\nyou cover all board!\n");
		printf("----------------------\n");

	}
	if (res == COVER_BOARD)					/* never get to that option */
	{
		printf("-------------------------\n");
		printf("\nYou not cover all board\n");
		printf("-------------------------\n");

	}
}

