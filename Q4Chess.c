#include "Q4Chess.h"

chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree) {

	chessPosList* res;
	bool thereIsPath = false;
	int counter=0;
	checkIfPathCoverAllBoard(path_tree->root, counter , &thereIsPath);		/* check first if there is a path like we need*/
	
	if (thereIsPath) {					/* if there is so the boolean is true */
		
		res = (chessPosList*)malloc(sizeof(chessPosList));
		checkMemoryAllocation(res);

		makeEmptyList(res);
		convertPathToList(path_tree->root , res, counter);			/* create the list we need */	
	}		
	else
		res = NULL;			/* if there is no path the cover all board reutrn NULL */
	
	return res;
}

void checkIfPathCoverAllBoard(TreeNode* root, int counter , bool* res) {
	
	counter++;						/* for every recursive call we increase the counter in one (for every position in the path ) */

	if (root == NULL || *res==true) {					/* stop condition to recursion if we found a way or we in the end of the path*/
		return;
	}
	else if(counter == ROW * COL) {
		*res = true;
		}
	else {
		
		treeNodeListCell* curr = root->next_possible_positions;		/* initial the next positions from the root*/

		while (curr != NULL && !*res) {							/* go through all the next positions */

			checkIfPathCoverAllBoard(curr->node, counter, res);			/* and call the recursive */
			
			curr = curr->next;				
		}
	}

}

 void convertPathToList(TreeNode* root , chessPosList* res , int counter) {
		
	 counter++;
	 
	 if (counter == ROW * COL) {
		 insertDataToStartList(res , root->position );		/* insert the first cell to list(is the tail) */
	 }
	 else {

		 treeNodeListCell* curr = root->next_possible_positions;
		
		 while (curr != NULL && res->head == NULL) { /* go through all the path till we find the path that covered the board */

			 convertPathToList(curr->node, res, counter);			

			 curr = curr->next;
		 }
		 if (res->head != NULL) {
			 insertDataToStartList(res, root->position);		/* insert every cell in the path to the list(from the end to start)*/
		 }
	 }
}

 void makeEmptyList(chessPosList* lst) {
 
	 lst->head = lst->tail = NULL;
 }

 void insertDataToStartList(chessPosList* res, chessPos position) {
 
	 chessPosCell* newHead;

	 newHead = createNewChessPosCell(position, NULL);
	 insertNodeToStartList(res, newHead);

 }

 chessPosCell* createNewChessPosCell(chessPos position, chessPosCell* next) {
	
	 chessPosCell* newCell = (chessPosCell*)malloc(sizeof(chessPosCell));
	 checkMemoryAllocation(newCell);

	 newCell->position[0] = position[0];
	 newCell->position[1] = position[1];
	
	 newCell->next = next;

	 return newCell;
 }

 void  insertNodeToStartList(chessPosList* lst , chessPosCell* newHead ) {
 
	 if (lst->head == NULL) {
	 
		 lst->head = lst->tail = newHead;
	 }
	 else {
	 
		 newHead->next = lst->head;
		 lst->head = newHead;
	 }
 }

 void freeList(chessPosList* lst) {
 
	 chessPosCell* curr = lst->head, * next;

	 while (curr != NULL)
	 {
		 next = curr->next;
		 free(curr);
		 curr = next;
	 }
 }