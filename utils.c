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
        token = strtok_r(cmd, DELIMITERS, &cmd);

        if (token != NULL) {
                cmd_argv[counter] = token;
                counter++;
                token = strtok_r(cmd, DELIMITERS, &cmd);
        } else {
                fprintf(stderr, "Invalid command.\n");
        }

        while (token != NULL) {
                cmd_argv[counter] = token;
                counter++;
                token = strtok_r(cmd, DELIMITERS, &cmd);
        }
        
	return counter;
}
