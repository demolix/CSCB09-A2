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
        while (fgets(buf, BUFFER_SIZE, stdin) != NULL) {
                if (tokenize(buf, args) > INPUT_ARG_MAX_NUM) {
                        fprintf(stderr, "Invalid command.");
                        exit(1);
                }

                if (args[0][0] == 'i'){
                        tree_insert(root_ptr, args);
                }
        }

        return 0;
}
