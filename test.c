#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "utils.h"


/*
 * Tokenize the string stored in cmd based on DELIMITERS as separators.
 * Return the number of tokens, and store pointers to them in cmd_argv.
 */

void prin_list(char** array){
        printf("%s \n", *array);
        for (int i = 1; i<=5; i++) {
                printf("%d", i%5);
        }
}


int main(char *cmd, char **cmd_argv) {
        // returning 0 for now, so the compiler does not complain
        char **array = malloc(3 * sizeof(char *));
        int i;
        for (i = 0; i < 3; ++i) {
                array[i] = (char *)malloc(13+1);
        }

        strcpy(array[0], "First");
        strcpy(array[1], "Second");
        strcpy(array[2], "Third");
        prin_list(array+1);
        
        return 0;
}

