#pragma once
#include "Q6Chess.h"

#define EXIT 6
#define GETPOS 1
#define CREATETREE 2
#define FINDPATH 3
#define CREATEFILE 4
#define CHECKFILE 5

void printMenu();

void startActions();

void getStartingPos(bool* OkPos, chessPos* pos);

bool checkPos(char row , char col);

char* getNameOfFile();

void displayRes(int res, char* fileNameCase5);