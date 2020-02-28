/*
 * Created by Sotirios-Efstathios Maneas on 2017-01-02.
 */

#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "utils.h"

int main(void) {
        // char array to hold a line of input
	char buf[BUFFER_SIZE] = {'\0'};

        // char* array to hold the pointers to tokens
	char *args[INPUT_ARG_MAX_NUM];

        // the root of the tree
        struct TreeNode root;
        root.value = "";
        root.child = NULL;
        root.sibling = NULL;

	struct TreeNode *root_ptr = &root;

        // Add your code below:
        // args[0] = malloc(sizeof(char));
        int num_args;

        for (int i = 0; i < INPUT_ARG_MAX_NUM; i++) {
                args[i] = malloc(sizeof(char)*BUFFER_SIZE);
        }

        while (fgets(buf, BUFFER_SIZE, stdin) != NULL) {
                if ((num_args = tokenize(buf, args)) > INPUT_ARG_MAX_NUM) {
                        fprintf(stderr, "Invalid command.\n");
                } else {
                        if (args[0][0] == 'i' && num_args == INPUT_ARG_MAX_NUM) {
                                tree_insert(root_ptr, &args[1]);
                        } else if (args[0][0] == 'q' && num_args == INPUT_ARG_MAX_NUM - 1) {
                                tree_search(root_ptr->child, &args[1]);
                        } else {
                                fprintf(stderr, "Invalid command.\n");
                        }
                }
        }

        return 0;
}
