/*
 * Created by Sotirios-Efstathios Maneas on 2017-01-02.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "utils.h"

typedef struct TreeNode Node;
/**
 *  A helper function that allocates a new tree node.
 *
 *  @param value The entry's value. It represents either an attribute or a filename.
 *  @return A pointer to the newly allocated node.
 *  (for now it returns NULL, so the compiler does not complain)
 */
Node *allocate_node(const char *value)
{
	Node *new_node = malloc(sizeof(Node));
	if(new_node!=NULL){
		new_node->value=malloc(strlen(value)+1);
		strcpy(new_node->value, value);
	new_node->child = NULL;
	new_node->sibling = NULL;
	}
	
	return new_node;
}



int insert_search(Node *level_root, char *value)
{
	
		while (level_root != NULL)
	{
		
			if (level_root!=NULL && strcmp(level_root->value, value) == 0)
		{
			return 1;
		}
		
		
		level_root = level_root->sibling;
	}
	
	
return 0;
}

// fix this
Node* find_node(Node* parent_level_root,Node* parent_node){

while(parent_level_root!=NULL){
	if(strcmp(parent_level_root->value,parent_node->value)==0){
		return parent_level_root;
	}
	parent_level_root=parent_level_root->sibling;
}

return NULL;
}




//insert in sorted order
Node*linked_list_insert(Node* head_ref,  Node* new_node) 
{ 
    if (  head_ref == NULL ) 
    {
        return new_node;
    }else if (strcmp( head_ref->value ,new_node->value )>=0 ){
		new_node->sibling=head_ref;
		head_ref=new_node;


	}else{
		head_ref->sibling = linked_list_insert( head_ref->sibling, new_node );
	}

    

    return head_ref;
} 





/**
 *  Insert a new image to a tree
 *
 *  @param tree A pointer to the root of the tree.
 *  @param values An array, whose first three members are the attribute values for 
 *                the image and the last one is the filename
 */
void tree_insert(struct TreeNode *root, char **values)
{
	Node *new_nodes[4];

	new_nodes[0] = allocate_node(values[1]);
	new_nodes[1] = allocate_node(values[2]);
	new_nodes[2] = allocate_node(values[3]);
	new_nodes[3] = allocate_node(values[4]);


	if (new_nodes[0] == NULL || new_nodes[1] == NULL || new_nodes[2] == NULL || new_nodes[3] == NULL)
	{
		printf("Cannot allocate memory");
		return;
	}

	if (root->child == NULL)		//when root has no child
	{ 
		root->child = new_nodes[0];
		new_nodes[0]->child = new_nodes[1];
		new_nodes[1]->child = new_nodes[2];
		new_nodes[2]->child = new_nodes[3];
		return;
	}

	Node *level_array[4];
	level_array[0] = root->child;		//color level
	level_array[1] = level_array[0]->child;	//shape level
	level_array[2] = level_array[1]->child;	// texture level
	level_array[3]=level_array[2]->child;	//file level

	

int i=0;

while(insert_search(level_array[i],new_nodes[i]->value)==1 && i<4){
	i++;
}

	if(i==0){
		new_nodes[0]->child=new_nodes[1];			// color node hasn't been inserted
	new_nodes[1]->child=new_nodes[2];
	new_nodes[2]->child=new_nodes[3];
	root->child=linked_list_insert(level_array[0],new_nodes[0]);

	} else if(i==1){
		Node* existing_color_node=find_node(level_array[0],new_nodes[0]); // shape node hasn't been inserted
	new_nodes[1]->child=new_nodes[2];
	new_nodes[2]->child=new_nodes[3];
	
	if(existing_color_node!=NULL){
		existing_color_node->child=linked_list_insert(existing_color_node->child,new_nodes[1]);


	}
	
	existing_color_node=NULL;


	}else if(i==2){
	new_nodes[2]->child=new_nodes[3]; // texture node hasn't been inserted
	Node*existing_shape_node=find_node(level_array[1],new_nodes[1]);
	Node* existing_color_node=find_node(level_array[0],new_nodes[0]);
	if(existing_shape_node!=NULL && existing_color_node!=NULL && insert_search(existing_color_node->child,existing_shape_node->value)==1){
		existing_shape_node->child=linked_list_insert(existing_shape_node->child,new_nodes[2]);
	}
		
	existing_color_node=NULL;
	existing_shape_node=NULL;
	
	
	}else if(i==3){											//file node not there
	Node*existing_shape_node=find_node(level_array[1],new_nodes[1]);
	Node* existing_color_node=find_node(level_array[0],new_nodes[0]);
	Node* existing_texture_node=find_node(level_array[2],new_nodes[2]); 
	if(existing_texture_node!=NULL && existing_color_node!=NULL && existing_shape_node!=NULL && insert_search(existing_color_node->child,existing_shape_node->value)==1 && insert_search(existing_shape_node->child,existing_texture_node->value)==1){
	existing_texture_node->child=linked_list_insert(existing_texture_node->child,new_nodes[3]);
	
		}
	
	existing_color_node=NULL;
	existing_shape_node=NULL;
	existing_texture_node=NULL;
	}

	

}





/**
 *  Searches a tree to print all files with matching attribute values.
 *
 *  @param tree A pointer to the root of the tree.
 *  @param values An array of attribute values
 */

void tree_search(const struct TreeNode *root, char **values)
{
	
	Node*level_array[3];
	level_array[0]=root->child;
	level_array[1]=level_array[0]->child;
	level_array[2]=level_array[1]->child;

	Node*potential_texture_node=allocate_node(values[3]);
	Node*potential_color_node=allocate_node(values[1]);
	Node*potential_shape_node=allocate_node(values[2]);

	 


	

		Node *file_ptr=NULL;
		Node* shape_node=NULL;
		Node*texture_node=NULL;
		Node* color_node=NULL;

		color_node=find_node(level_array[0],potential_color_node);
		if(color_node!=NULL){
		 
		 	shape_node=find_node(color_node->child,potential_shape_node);
		
			if(shape_node!=NULL){
		
				 texture_node=find_node(shape_node->child,potential_texture_node);
		
				if(texture_node!=NULL){
		
					file_ptr=texture_node->child;

				}
			}
		}
		
		if(file_ptr!=NULL){
			while(file_ptr!=NULL){
			printf("%s\n",file_ptr->value);
			file_ptr=file_ptr->sibling;
		}
		free(potential_color_node);
		free(potential_shape_node);
		free(potential_texture_node);
		
		potential_color_node=NULL;
		potential_shape_node=NULL;
		potential_texture_node=NULL;
		color_node=NULL;
		shape_node=NULL;
		texture_node=NULL;

		
			}else{
		printf("%s","(NULL)\n");
	}

}

/**
 *  Prints a complete tree to the standard output.
 *
 *  @param tree A pointer to the root of the tree.
 */
void tree_print(const struct TreeNode *tree)
{
	if(tree==NULL || tree->child==NULL){
		printf("%s","(NULL)\n");
		
	}else{
		Node* colorNode=tree->child;

		while(colorNode!=NULL){	//color level
			
			Node* shapeNode=colorNode->child;
			
			while(shapeNode!=NULL){
			
				Node* textureNode=shapeNode->child;
			
				while(textureNode!=NULL){
			
					Node*fileNode=textureNode->child;
			
					while (fileNode!=NULL)
			
					{	if(tree->child!=NULL && shapeNode!=NULL && textureNode!=NULL && fileNode!=NULL){
						printf("%s %s %s %s\n",colorNode->value,shapeNode->value,textureNode->value,fileNode->value);

					}
						fileNode=fileNode->sibling;
					}
					textureNode=textureNode->sibling;
				}
				shapeNode=shapeNode->sibling;
			}

			
			colorNode=colorNode->sibling;	

		}

	}
}



