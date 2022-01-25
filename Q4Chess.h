#pragma once
#include "Q3Chess.h"

chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree);

void checkIfPathCoverAllBoard(TreeNode* root, int counter, bool* res);

void convertPathToList(TreeNode* root, chessPosList* res, int counter);

void makeEmptyList(chessPosList* lst);

void insertDataToStartList(chessPosList* res, chessPos position);

chessPosCell* createNewChessPosCell(chessPos position, chessPosCell* next);

void  insertNodeToStartList(chessPosList* lst, chessPosCell* newHead);

void freeList(chessPosList* lst);