/*
 * Created by Sotirios-Efstathios Maneas on 2017-01-02.
 */

#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "utils.h"

int main(void) {

        // char array to hold a line of input
	char buf[BUFFER_SIZE];

        // char* array to hold the pointers to tokens
	char *args[INPUT_ARG_MAX_NUM];

        // the root of the tree
        struct TreeNode root;
        root.value = "";
        root.child = NULL;
        root.sibling = NULL;

	struct TreeNode *root_ptr = &root;
        
while(fgets(buf,BUFFER_SIZE,stdin)!=NULL){
        // Add your code below:
       int argc= tokenize(buf,args);
       //error check
        
      if(*args[0]=='i' && argc==5){
              tree_insert(root_ptr,args);
      }
       else if (*args[0]=='p'&& argc==1)
      {tree_print(&root);
            
       }else if (*args[0]=='q' && argc==4){
               tree_search(&root,args);
       }else
       {
               fprintf(stderr,"Invalid command.\n");
               exit(1);
       }
       
      

}
        

        return 0;
}
