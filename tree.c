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


/*
 * HELPERS FOR TREE_PRINT:
 */

// void recursive_print() {
// 	while (level_node != NULL) {
// 		if (level_node->child == NULL) {
// 			strcat(cum_string, level_node->value);
// 			printf("%s\n", cum_string);
// 			return;
// 		}
// 		recursive_print(next_level_node, cum_string);
// 	}
// }


int is_root(const struct TreeNode *root, struct TreeNode *node) {
	if (!strcmp(root->value, node->value)) {
		return 1;
	}
	return 0;
}

void realign_all_levels(struct TreeNode **all_levels, int ind) {
	if (all_levels[ind] == NULL) {return;}
	
	while (all_levels[ind]->child != NULL) {
		all_levels[ind + 1] = all_levels[ind]->child;
		ind++;
	}
}

int is_valid_all_levels(struct TreeNode **all_levels, int total_levels) {
	if (all_levels[0] == NULL) {return 1;}

	for (int i = 0; i < total_levels; i++) {
		if (all_levels[i] == NULL) {
			return 0;
		}
	}
	return 1;
}

/**
 *  Prints a complete tree to the standard output.
 *
 *  @param tree A pointer to the root of the tree.
 */
void tree_print(const struct TreeNode *tree) {
	if (tree->child == NULL) {
		printf("(NULL)\n");
		return;
	}

	int outer_break = 0;
	int total_levels = INPUT_ARG_MAX_NUM;
	//int print_depth = total_levels - 1;
	struct TreeNode *all_levels[total_levels];
	struct TreeNode *curr = malloc(sizeof(struct TreeNode));
	*curr = *tree;

	int itr = 0;
	while (curr != NULL) {
		all_levels[itr] = curr;
		curr = curr->child;
		itr++;
 	}

	while (1) {
		for (int i = 1; i < total_levels; i++) {
			printf("%s ", all_levels[i]->value);
		}
		printf("\n");
		/**
		 * curr = all_levels[total] 
		 * while (true) {
		 *     if (counter % (INPUT_SIZE_MAX - 1) == 0) {
		 * 	   		all_levels[0] = NULL;
		 * 			break; 
		 *     }
		 * 	   all_levels[total_levels - counter] = its_sibling;
		 * 	   if (all_levels[total_levels - counter] == NULL):
		 * 			counter++;
		 * 			continue;
		 * 	   else {	if (all_levels[total_levels - print_depth]->sibling != NULL || is_root(tree, all_levels[total_levels - print_depth])) {
				all_levels[total_levels - print_depth] = all_levels[total_levels - counter]->sibling;
				realign_all_levels(all_levels, total_levels - counter);
			} else {
				print_depth++;
				all_levels[total_levels - print_depth] = all_levels[total_levels - print_depth]->sibling;
				realign_all_levels(all_levels, total_levels - counter);
			}
		 * 			realign;
		 * 			break;
		 * 	   }
		 * }
		 * 
		 * 
		 * 
		 * 
		 */
		
		//if (all_levels[total_levels - print_depth]->sibling != NULL || is_root(tree, all_levels[total_levels - print_depth])) {
		//if (all_levels[total_levels - print_depth]->sibling != NULL) {
		//	all_levels[total_levels - print_depth] = all_levels[total_levels - print_depth]->sibling;
			//realign_all_levels(all_levels, total_levels - print_depth);
			
		//} else {
		for (int i = total_levels - 1; i > 0; i--) {
			//print_depth++;
			if (all_levels[i]->sibling != NULL) {
				all_levels[i] = all_levels[i]->sibling;
				realign_all_levels(all_levels, i);
				//print_depth = 1;
				outer_break = 0;
				break;
			}
		}
		if (!outer_break) {
			continue;
		}
		break;
		//}

		// } while (!is_valid_all_levels(all_levels, total_levels) || break_loop);
	}
	free(curr);

}
