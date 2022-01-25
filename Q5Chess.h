#pragma once
#include "Q4Chess.h"

typedef unsigned char BYTE;

void saveListToBinFile(char* file_name, chessPosList* pos_list);

short int countPosList(chessPosList* lst);

BYTE convertPosToBin(chessPosCell* curr);

void checkFile(FILE* file);
