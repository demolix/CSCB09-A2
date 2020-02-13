#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "tree.h"


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


int main() {
        // char array to hold a line of input
	char buf[BUFFER_SIZE] = {'\0'};

        // char* array to hold the pointers to tokens
	//char *args[INPUT_ARG_MAX_NUM];

        // returning 0 for now, so the compiler does not complain
        fgets(buf, BUFFER_SIZE, stdin);

        char *token;
        token = strtok(buf, DELIMITERS);

        printf("%s", token);

        token = strtok(NULL, DELIMITERS);

        printf("%s", token);

        token = strtok(NULL, DELIMITERS);

        printf("%s", token);

        token = strtok(NULL, DELIMITERS);

        printf("%s", token);


        return 0;
}

