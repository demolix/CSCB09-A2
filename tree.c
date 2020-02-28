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
static int counter = 1;
static int search_depth = 1;

struct TreeNode *allocate_node(const char *value) {

	struct TreeNode *new_node = malloc(sizeof(struct TreeNode));
	new_node->value = malloc(INPUT_ARG_MAX_NUM*sizeof(char));
	strcpy(new_node->value, value);
	new_node->child = NULL;
	new_node->sibling = NULL;
	return new_node;
}

void level_insert(struct TreeNode *head, char **values, int *counter) {
	while (head != NULL) {
		if (strcmp(head->value, values[0]) == 0) {
			(*counter)++;
			tree_insert(head, &values[1]);
			return;
		} else if (head->sibling == NULL) {
			(*counter)++;
			head->sibling = allocate_node(values[0]);
			tree_insert(head->sibling, &values[1]);
			return;
		} else if (strcmp(head->sibling->value, values[0]) > 0) {
			struct TreeNode *temp = head->sibling;
			head->sibling = allocate_node(values[0]);                          
			head->sibling->sibling = temp;
			(*counter)++;
			tree_insert(head->sibling, &values[1]);
			return;
		}
		head = head->sibling;
	}
}

/**
 *  Insert a new image to a tree
 *
 *  @param tree A pointer to the root of the tree.
 *  @param values An array, whose first three members are the attribute values for 
 *                the image and the last one is the filename
 */
void tree_insert(struct TreeNode *root, char **values) {

	if (counter % (INPUT_ARG_MAX_NUM) == 0) {
		counter = 1;
		// Base case of recursion.
		return;
	}

	if (root->child == NULL) {
		root->child = allocate_node(values[0]);
		counter++;
		tree_insert(root->child, &values[1]);
		return;
	} 

	//Do the case where root's child->value is greater than root->value.
	if (strcmp(root->child->value, values[0]) > 0) {
		struct TreeNode *temp = root->child;
		root->child = allocate_node(values[0]);
		root->child->sibling = temp;
		counter++;
		tree_insert(root->child, &values[1]);
		return;
	}
	
	level_insert(root->child, values, &counter);
}

/*
 * HELPER FUNCTIONS FOR TREE_SEARCH FOLLOW:
 */

struct TreeNode *in_this_level(struct TreeNode *root, char *value) {
	while (root != NULL) {
		if (!strcmp(root->value, value)) {
			return root;
		}
		root = root->sibling;
	}
	return NULL;
} 


void print_list(struct TreeNode *head) {
	while (head != NULL) {
		printf("%s ", head->value);
		head = head->sibling;
	}
	printf("\n");
}
/**
 *  Searches a tree to print all files with matching attribute values.
 *
 *  @param tree A pointer to the root of the tree.
 *  @param values An array of attribute values
 */
void tree_search(const struct TreeNode *root, char **values) {
	//Base case of recursion.
	struct TreeNode *curr = malloc(sizeof(struct TreeNode));
	*curr = *root;

	if (search_depth % (INPUT_ARG_MAX_NUM - 1) == 0) {
		search_depth = 1;
		print_list(curr);
		free(curr);
		return;
	}

	if ((curr = in_this_level(curr, values[0])) != NULL) {
		search_depth++;
		tree_search(curr->child, &values[1]);
	} else {
		search_depth = 1;
		printf("(NULL)\n");
	}
	free(curr);
	
}

/**
 *  Prints a complete tree to the standard output.
 *
 *  @param tree A pointer to the root of the tree.
 */
void tree_print(const struct TreeNode *tree) {
}
