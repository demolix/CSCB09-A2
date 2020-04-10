/*
 * Created by Sotirios-Efstathios Maneas on 2017-01-02.
 */

#include <stdio.h>
#include <string.h>
#include<stdlib.h>

//#include "utils.h"


/*
 * Tokenize the string stored in cmd based on DELIMITERS as separators.
 * Return the number of tokens, and store pointers to them in cmd_argv.
 */



int tokenize(char *cmd, char **cmd_argv) {
int i=0;
char *token=strtok(cmd," ");

        while(token!=NULL && i<5){
      
        cmd_argv[i]=token;
        i++;
        token=strtok(NULL," ");
        }  
        // returning 0 for now, so the compiler does not complain
	return i;
}






