#include "Q3Chess.h"

pathTree findAllPossibleKnightPaths(chessPos* startingPosition) {

	pathTree res;
	chessPosArray*** knightMovesBoard = validKnightMoves();		/* look for all the array we need for every position */

	int checkPosArr[ROW][COL] = { 0 };

	res.root = (TreeNode*)malloc(sizeof(TreeNode));				/* initial the root*/
	checkMemoryAllocation(res.root);

	res.root = createTreeNode(*startingPosition);

	res.root = findAllPossibleKnightPathsRec(res.root, knightMovesBoard, checkPosArr);  /* find the tree recursive */

	freeKnightPos(knightMovesBoard);					/* free the position array */

	return res;
}

TreeNode* findAllPossibleKnightPathsRec(TreeNode* root, chessPosArray*** arr, int checkPosArr[][COL]) {

	int i, j;
	treeNodeListCell* curr;


	if (root == NULL) {			/* stop condition*/
		return NULL;
	}
	else {

		i = root->position[0] - 'A';				/* convert the pos to int (for the array) */
		j = root->position[1] - '1';

		checkPosArr[i][j] = 1;				/* change from 0 to 1 that we know that we already put that pos on that path tree */

		root->next_possible_positions = knigtMovesFromArrayToList(*arr[i][j], checkPosArr);	/* initial the list for every tree node */
		curr = root->next_possible_positions;

		while (curr != NULL) {				/* run on the list and call recursive for every branching path */

			curr->node = findAllPossibleKnightPathsRec(curr->node, arr, checkPosArr);
			
			curr = curr->next;
				
			//checkPosArr[i][j] = 0;

		}
	}
	checkPosArr[i][j] = 0;		/* change from 0 to 1 that we know that we already put that pos on that path tree */
	return root;
}

treeNodeListCell* knigtMovesFromArrayToList(chessPosArray arr, int checkPosArr[][COL]) {

	unsigned int i = 0;
	treeNodeListCell* possibleMovesList = NULL;
	treeNodeListCell* newTail = NULL;

	while (possibleMovesList == NULL && i < arr.size) {	/*check first that we have the first possible move to insert the list */

		if (checkPosArr[(arr.positions[i][0] - 'A')][(arr.positions[i][1] - '1')] == 0)
			/* the condition that we still not have the node in that path */
		{
			
			newTail = createTreeNodeListCell(arr.positions[i]);
			possibleMovesList = newTail;							/*initial the first cell in the list*/
		}
		i++;
	}
	for (i; i < arr.size; i++) {
		if (checkPosArr[(arr.positions[i][0] - 'A')][(arr.positions[i][1] - '1')] == 0) { /* same condition(same as in the while ) */

			treeNodeListCell* temp = createTreeNodeListCell(arr.positions[i]);

			newTail->next = temp;
			newTail = temp;
		}
	}

	return possibleMovesList;
}

treeNodeListCell* createTreeNodeListCell(chessPos dataPosition) {

	treeNodeListCell* newTail = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	checkMemoryAllocation(newTail);

	newTail->node = (TreeNode*)malloc(sizeof(TreeNode));
	checkMemoryAllocation(newTail->node);

	newTail->node = createTreeNode(dataPosition);
	newTail->next = NULL;

	return newTail;
}

TreeNode* createTreeNode(chessPos dataPosition) {

	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	checkMemoryAllocation(newNode);

	newNode->position[0] = dataPosition[0];
	newNode->position[1] = dataPosition[1];
	newNode->next_possible_positions = NULL;

	return newNode;
}

void freePathTree(pathTree tr) {

	freePathTreeRec(tr.root);

}

void freePathTreeRec(TreeNode* root) {

	if (root == NULL) {
		return;
	}
	else {
		treeNodeListCell* curr = root->next_possible_positions;
		treeNodeListCell* next;

		while (curr != NULL) {				// run on the list and call recursive for every branching path
			next = curr->next;
			freePathTreeRec(curr->node);
			
			//free(curr->node);
			free(curr);
			
			curr = next;
			
		}
		free(root);
	}
}
