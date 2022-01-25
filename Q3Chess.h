#pragma once
#include "Q2Chess.h"

typedef struct _treeNodeListCell
treeNodeListCell;

typedef struct _treeNode {

	chessPos position;
	treeNodeListCell* next_possible_positions;

}TreeNode;

typedef struct _treeNodeListCell {

	TreeNode* node;
	struct _treeNodeListCell* next;

}treeNodeListCell;

typedef struct pathTree {

	TreeNode* root;

}pathTree;


pathTree findAllPossibleKnightPaths(chessPos* startingPosition);
treeNodeListCell* knigtMovesFromArrayToList(chessPosArray arr, int checkPosArr[][COL]);		/* make a list from possible knight moves array*/
TreeNode* findAllPossibleKnightPathsRec(TreeNode* root, chessPosArray*** arr, int checkPosArr[][COL]);		/* the recursion function that make the tree */
treeNodeListCell* createTreeNodeListCell(chessPos dataPosition);	/* make a cell in the list */
TreeNode* createTreeNode(chessPos dataPosition);
void freePathTree(pathTree tr);
void freePathTreeRec(TreeNode* root);
