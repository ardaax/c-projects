#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
#define MAX_CHILD 10    // Number of max children in a treeNode 
#define MAX_SIZE 100    // MAX_SIZE for node's name array's max length and command line arguments.
extern int id_counter; // Current id in the network tree
/*  Header file tree.h for Personal library with Data Type and associated functions */
/*
    A node treeNode object.
    It has these componenets:
    children[], id, name[]
    It has an array of pointers for 10 possible children of the node.
    id is it's id.
    name is an array containing the name of the Node.


    Operators:
        insertNode, printTree, deleteNode, findParentNode, findNode, delete_2
*/
struct treeNode {
    struct treeNode *children[MAX_CHILD];   // The children nodes as an array of 10 treeNode objects.
    int id; // Unique id
    char name[MAX_SIZE]; // Name of the entity.
};

/*
 * treePtr is the rootNode. Traverses the children to find the id.
 * Once treePtr with id is found, allocates space at the first available child.
 * Makes it's own children NULL.
 */
extern void insertNode(struct treeNode **treePtrPtr, int id, char name[]);

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
extern void printTree(struct treeNode **treePtrPtr, int id, FILE *fp);

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
extern void deleteNode(struct treeNode *treePtr);


/*
    Arguments:
    treePtrPtr: Pointer to a pointer of struct treeNode object. Always headPtr
    id: id of the node we look for

    Recursively checks the id if treePtrPtr's id match that pointer is returned.
*/
extern struct treeNode * findNode(struct treeNode **treePtrPtr, int id);

/*
 * Arguments:
 * treePtrPtr: Pointer to a pointer of struct treeNode object. Always headPtr
 * id: id of the node we look for
 * Recursively checks if id of treePtrPtr's child match with argument id id  that pointer is returned.
*/
extern struct treeNode * findParentNode(struct treeNode **treePtrPtr, int id);



/*
 * Arguments:
 * treePtrHead: Finds the children's index which is treePtrChild
 * treePtrChild: This is node which treePtrHead's child will be freed
 * This function is for freeing the link between the parent and the children(original parent node to be deleted)
*/
extern void delete_2(struct treeNode *treePtrHead, struct treeNode *treePtrChild);


#endif