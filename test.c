#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "tree.h"


/*
 * Tokenize the string stored in cmd based on DELIMITERS as separators.
 * Return the number of tokens, and store pointers to them in cmd_argv.
 */


int main() {
        int i = 5;
        int j = 6;
        int* ptr = &i;
        int* ptr2 = ptr;

        *ptr = j;

        printf("%d", *ptr2);

        return 0;
}

