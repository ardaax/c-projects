#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include <assert.h>
#include "tree.h"   // Personal library for tree

/*
 * treePtr is the rootNode. Traverses the children to find the id.
 * Once treePtr with id is found, allocates space at the first available child.
 * Makes it's own children NULL.
 */
void insertNode(struct treeNode **treePtrPtr, int id, char name[])
{
    // Tree is empty, allocate a new memory space.
    if( (*treePtrPtr) == NULL) {    
        *treePtrPtr = (struct treeNode*)malloc(sizeof(struct treeNode));
        strcpy((*treePtrPtr)->name, name);
        (*treePtrPtr)->id = id_counter++;
        for (int i = 0; i < MAX_CHILD; i++)
        {
            (*treePtrPtr)->children[i] = NULL; // Initialize children to NULL
        }
        return;
    }
    // Tree is not empty
    struct treeNode *temp = (*treePtrPtr);   // temporary pointer
    if((temp->id == id)) { // We found the parent node
        for (int i = 0; i < MAX_CHILD; i++) // For every child
        {
            if ( temp->children[i] == NULL) // If the child is empty create this node
            {
                temp->children[i] = malloc(sizeof(struct treeNode));
                strcpy(temp->children[i]->name, name);
                (temp->children[i])->id = id_counter++;
                struct treeNode *child = temp->children[i];
                for (int j = 0; j < MAX_CHILD; j++)
                {
                    child->children[j] = NULL; // Initialize children to NULL
                }
                return;
            }  
        }
    }
}




/*
    Arguments:
    treePtrPtr: Pointer to a pointer of struct treeNode object.
    id: Id of the current node in the recursion.
    fp: file pointer that will be written to.

    Makes a post-order traversal in the tree. Before calling this function 
    the findNode function is used to find correct node, treePtrPtr is
    the Node we want to start printing from.

    Does some string operations to get to the format "EXAMPLE[id]" also uses math.h
*/
void printTree(struct treeNode **treePtrPtr, int id, FILE *fp)
{
    struct treeNode *temp = (*treePtrPtr);
    // We will need to convert int to str ids
    int size = 0;   // Number of integers in the id.
    int n = id;
    // This while loop finds the number of digits in id
    while (n != 0) {
        n /= 10;   
        ++size;
    }

    char *tmpstr = malloc(strlen(temp->name) +1 );  // tmpstr holds current node's name
    strcpy(tmpstr, temp->name);
    char int_str[size+1];   // int_str: string version of id
    snprintf(int_str, size+1, "%d", id);    // snprintf to copy the values of id to int_str
    // Write to file
    fwrite(tmpstr, strlen(tmpstr), 1, fp);
    fwrite("[", 1, 1, fp);
    fwrite(int_str, strlen(int_str), 1, fp);
    fwrite("]", 1, 1, fp);
    fwrite("\n", 1, 1, fp);
    
    free(tmpstr);   // Free dynamically allocated space

    // For every children if it is not null, call printTree with that child as the pointer, recursive part!
    for (int i = 0; i < MAX_CHILD; i++)
    {
        if( temp->children[i] != NULL) {
            printTree(&(temp->children[i]), (temp->children[i])->id, fp);
        }
    }
}


/*
    Arguments:
    treePtr: Pointer to struct treeNode object.

    Makes a post-order traversal in the tree. Before calling this function 
    the findNode function is used to find correct node, treePtrPtr is
    the Node we want to start printing from.
    
    Deletes children of a node if its children are empty. If not goes one step below.
    Basically it is recursive but one level over than normal recursion. Once finished,
    the original nodes all children will be deleted except itself. That node is deleted
    after all the deletions occur.

*/
void deleteNode(struct treeNode *treePtr)
{
    // **treePtrPtr is the root we will delete we will delete all the subtrees
    if (treePtr == NULL) 
    {
        return;
    }
    // For every child call deleteNode, if it is not it just returns nothing.
    for (int i = 0; i < MAX_CHILD; i++)
    {
        deleteNode(treePtr->children[i]);
    }
    
     // The above for function is done. Free all it's children and make them null.
    for (int i = 0; i < MAX_CHILD; i++)
    {
        free(treePtr->children[i]);
        treePtr->children[i] = NULL;
        assert(treePtr->children[i] == NULL);
    }
}

/*
    Arguments:
    treePtrPtr: Pointer to a pointer of struct treeNode object. Always headPtr
    id: id of the node we look for

    Recursively checks the id if treePtrPtr's id match that pointer is returned.
*/
struct treeNode * findNode(struct treeNode **treePtrPtr, int id)
{
    struct treeNode *temp = (*treePtrPtr);  // Temporary treeNode
    struct treeNode *result = NULL; // Returned treeNode value
    if (temp->id == id)  // The id is what we look for return current
    {
        result = temp;
    }

    // Id's are not equal, if the children is not empty recursively call it's children
    if (temp->id != id) {
        for (int i = 0; i < MAX_CHILD; i++)
        {
            if ((temp->children[i]) != NULL)
            result = findNode( &(temp->children[i]), id);
            if ( result != NULL) return result;
        }
    }
    return result;
}


/*
    Arguments:
    treePtrPtr: Pointer to a pointer of struct treeNode object. Always headPtr
    id: id of the node we look for

    Recursively checks if id of treePtrPtr's child match with argument id id  that pointer is returned.
*/
struct treeNode * findParentNode(struct treeNode **treePtrPtr, int id)
{
    // Finds the parent node to the id we look for
    struct treeNode *temp = (*treePtrPtr);
    struct treeNode *result = NULL;
    
    for (int j = 0; j < MAX_CHILD; j++)
    {
        if (temp->children[j] != NULL) {   // if not equal to null
        // The id of current node's j'th child is what we look for, return the current node
        if (temp->children[j]->id == id)
        {
            result = temp;
            return result;
        }
        result = findParentNode( &(temp->children[j]), id);
        if ( result != NULL) return result;
        }
    }
    return result;
}


/*
    Arguments:
    treePtrHead: Finds the children's index which is treePtrChild
    treePtrChild: This is node which treePtrHead's child will be freed

    This function is for freeing the link between the parent and the children(original parent node to be deleted)
*/
void delete_2(struct treeNode *treePtrHead, struct treeNode *treePtrChild)
{
    int index = 0;  // Index of node to be deleted from parent node's perspective.
    for (int i = 0; i < MAX_CHILD; i++)
    {
        if ( treePtrHead->children[i] != NULL)
        {
            if (treePtrHead->children[i]->id == treePtrChild->id)
            {
                index = i;
            }
            
        }
    }
    free(treePtrHead->children[index]);
    treePtrHead->children[index] = NULL;
    assert(treePtrHead->children[index] == NULL);
}