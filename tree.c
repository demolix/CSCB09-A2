/*
 * Created by Sotirios-Efstathios Maneas on 2017-01-02.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"


/**
 *  A helper function that allocates a new tree node.
 *
 *  @param value The entry's value. It represents either an attribute or a filename.
 *  @return A pointer to the newly allocated node.
 *  (for now it returns NULL, so the compiler does not complain)
 */
struct TreeNode *allocate_node(const char *value) {

	struct TreeNode *new_node = malloc(sizeof(struct TreeNode*));
	new_node->value = malloc(INPUT_ARG_MAX_NUM*sizeof(char));
	strcpy(new_node->value, value);
	new_node->child = NULL;
	new_node->sibling = NULL;
	return new_node;
}

/**
 *  Insert a new image to a tree
 *
 *  @param tree A pointer to the root of the tree.
 *  @param values An array, whose first three members are the attribute values for 
 *                the image and the last one is the filename
 */
void tree_insert(struct TreeNode *root, char **values) {
	//struct TreeNode head = root->child;
	static int counter = 1;

	if (root->child == NULL) {
		root->child = allocate_node(values[0]);
		if (counter % 5 != 0) {

			counter++;
			tree_insert(root->child, &values[1]);
			return;
		} else {
			//Base case of recursion.
			counter = 1;
			return;
		}
	} 
	root = root->child;

	while (root != NULL){
		if (!strcmp(root->value, *values)){

			if (counter % (INPUT_ARG_MAX_NUM - 1) != 0) {
				counter++;
				tree_insert(root, &values[1]);
				return;
			} else {
				counter = 1;
				return;
			}
		}
		if (root->sibling == NULL) {
			root->sibling = allocate_node(*values);                             //Sorted insert here.
			if (counter % (INPUT_ARG_MAX_NUM - 1) != 0) {
				counter++;
				tree_insert(root->sibling, &values[1]);
				return;
			} else {
				counter = 1;
				return;
			}
		}
		root = root->sibling;
	}

	

}

/**
 *  Searches a tree to print all files with matching attribute values.
 *
 *  @param tree A pointer to the root of the tree.
 *  @param values An array of attribute values
 */
void tree_search(const struct TreeNode *root, char **values) {
}

/**
 *  Prints a complete tree to the standard output.
 *
 *  @param tree A pointer to the root of the tree.
 */
void tree_print(const struct TreeNode *tree) {
}
