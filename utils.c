/*
 * Created by Sotirios-Efstathios Maneas on 2017-01-02.
 */

#include <stdio.h>
#include <string.h>

#include "utils.h"


/*
 * Tokenize the string stored in cmd based on DELIMITERS as separators.
 * Return the number of tokens, and store pointers to them in cmd_argv.
 */
int tokenize(char *cmd, char **cmd_argv) {
        // returning 0 for now, so the compiler does not complain
        int counter = 0;

        char *token;
        token = strtok(cmd, DELIMITERS);

        if (token != NULL) {
                strcpy(*cmd_argv, token);
                counter++;
                token = strtok(cmd, DELIMITERS);
        } else {
                fprintf(stderr, "No string was specified");
        }

        while (token != NULL) {
                strcpy(*(cmd_argv + counter), token);
                counter++;
                token = strtok(cmd, DELIMITERS);
        }
        
	return counter;
}
