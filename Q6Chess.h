#pragma once
#include "Q5Chess.h"

#define NOT_EXIST_FILE -1
#define NOT_LEGAL_PATH 1
#define NOT_COVER_BOARD 2
#define COVER_BOARD 3

#define ONE_STEP 1
#define TWO_STEP 2

int checkAndDisplayPathFromFile(char* file_name);

void convertFileToList(chessPosList* lst, FILE* file);

void convertThePosAndInsertToLst(BYTE byteMask, chessPosList* lst);

void insertDataToEndList(chessPosList* lst, chessPos pos);

void insertNodeToEndList(chessPosList* lst, chessPosCell* newTail);

chessPosCell* createNewCell(chessPos pos, chessPosCell* next);

bool checkIfRightMove(chessPosCell* nextMove, chessPos currPos);

short int countList(chessPosCell* head);