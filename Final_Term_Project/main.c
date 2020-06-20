 #include <stdlib.h>
 #include <stdio.h>
 #include <string.h> 
 #include <assert.h>
 #include "tree.h"

 /*
    Arguments:
    char *token : tokenized string
    char *parent : the node string before '[' element
    int id: id of the node given in token.
    
    Return element and id for insert, delete ,print
    Parent Node
*/
void elementw_id(char *token, char *parent , int *id);

/* Given a str char pointer it eliminates blank lines
    but leaves one space between words change written into result
    char *str: Source string
    char *result: Resulting string after elimination of extra spaces.
*/
void trimstr (char *str, char *result);


int id_counter = 1; // initialzie
const char delim[2] = " ";  //Space
const char sep[2] = "[";  //seperator

FILE *inp;	// Pointer to Input Commands Script File
FILE *outp;	// Pointer to Output File
FILE *binp;	// Pointer to Bonus Input Script File
FILE *boutp;	// Pointer to Bonus Output File

/*  Processes the input arguments calls tree library functions  */
int main(int argc, char **argv) 
{
    char in_text[MAX_SIZE];     // Input Commands Script Filename -- implemented.
    char out_text[MAX_SIZE];    // Output Filename -- implemented
    char bin_text[MAX_SIZE];    // Bonus Input Script Filename -- not implemented.
    char bout_text[MAX_SIZE];    // Bonus Output Filename   -- not implemented.

    /* Writing from input to these strings */
    strcpy(in_text, argv[1]);
    strcpy(out_text, argv[2]);
    strcpy(bin_text, argv[3]);
    strcpy(bout_text, argv[4]);

    // Open files
    inp = fopen(in_text, "r");
    outp = fopen(out_text, "w");
    /* Null file check  */
    if (!inp) {
		fprintf(stderr, "Unable to open file %s", in_text);
		exit(1);
	}

    char line [MAX_SIZE];   /* Current line that is read */
    fgets(line, sizeof(line), inp); // First line is always INSERT SWITCH
    struct treeNode *headPtr = NULL;    // Initially empty, headPtr is the root node of our tree.
    insertNode(&headPtr, id_counter, "SWITCH"); // Create the tree with insertion
    char *token;    // Token is for tokenizer in strtok function.

    /* Read the current line, iterate until the end of the file */
    while (fgets(line, sizeof(line), inp) != NULL)
    {
        char *copy = malloc(sizeof(char)*(strlen(line)+1));  // Current command temporary
        strcpy(copy, line); // Copy the contents to copy str
        int size = strlen(copy);
        char *result = malloc(sizeof(char)*size);    // Result is the string returned after elimination of extra spaces
        trimstr(copy, result);  // Eliminate extra spaces.
        token = strtok(result, delim);  // First token
        char *command = malloc(sizeof(char)*sizeof(strlen(token)+1));   // Command holds the string for insert, delete and print
        strcpy(command, token); 

        /* Command is insert */
        if (strcmp(command, "INSERT") == 0)
        {
            /*
                Tokenizes the string finds parent node with findNode.
                Inserts the new node using insertNode function
            */
            token = strtok(NULL, delim);
            char *new_element = malloc(sizeof(char)*sizeof(strlen(token)+1));   // First string after, COMMAND
            strcpy(new_element, token);
            token = strtok(NULL, delim);
            char *parent = malloc(sizeof(char)*sizeof(strlen(token)+1));    // The string node to be inserted.
            int id = 0;
            elementw_id(token, parent, &id);
            struct treeNode *insertHead = NULL;
            insertHead = findNode(&headPtr, id);    // Find the node to be inserted.
            insertNode(&insertHead, id, new_element);
            free(new_element);
            free(parent);
        }

        /* Command is Delete */
        else if (strcmp(command, "DELETE") == 0)
        {
            /*  TOKENIZES THE STRING finds the node to be deleted and its parent
                calls deleteNode function to recursively delete all subnodes and delete_2
                to delete original root node to be deleted.
            */
            int flag = 0;   // This flag is for checking if the node to be deleted is the rootnode. if yes 1, otherwise no
            token = strtok(NULL, delim);
            char *parent = malloc(sizeof(char)*sizeof(strlen(token)+1));
            int id = 0;
            elementw_id(token, parent, &id);
            struct treeNode *deleteHead = NULL;
            struct treeNode *deleteParent = NULL;
            deleteHead = findNode(&headPtr, id);
            deleteParent = findParentNode(&headPtr, id);
            // If deleteHead is Headptr
            if(deleteHead == headPtr)
            {
                flag = 1;   // Make flag 1
            }
            deleteNode(deleteHead); // Delete all the children of deleteHead
            // Delete the link from parent node
            if (flag == 0)  // IF the node node is not headptr we can look for it's Parent node without error
            delete_2(deleteParent, deleteHead);

            // Freeing RootNode
            else if (flag == 1) {
                id_counter = 1;
                free(headPtr);
                headPtr = NULL;
                assert(headPtr == NULL);
            }
            // Free
            free(parent);
        }

        /* Command is Print */
        else if (strcmp(command, "PRINT") == 0) 
        {
            /*
                Tokenize string, find the root node to be printed from.
                Call printTree function with this headNode.
            */
            token = strtok(NULL, delim);
            char *parent = malloc(sizeof(char)*sizeof(strlen(token)+1));
            int id = 0;
            elementw_id(token, parent, &id);
            struct treeNode *printHead = NULL;
            printHead = findNode(&headPtr, id);
            printTree(&printHead, id, outp);
            // Free
            free(parent);
        }
        // Free mallocs
        free(copy);
        free(command);  
    }
    
    
/* Close the files */
fclose(inp);
fclose(outp);
//fclose(binp);
//fclose(boutp);
}

/*
    Arguments:
    char *token : tokenized string
    char *parent : the node string before '[' element
    int id: id of the node given in token.
    
    Return element and id for insert, delete ,print
    Parent Node
*/
void elementw_id(char *token, char *parent , int *id)
{
    strcpy(parent, token);
    token = strtok(parent, "[");
    token = strtok(NULL, "[");
    token[strlen(token)-1] = '\0';
    *id = atoi(token);
}



/* Given a str char pointer it eliminates blank lines
    but leaves one space between words change written into result
    char *str: Source string
    char *result: Resulting string after elimination of extra spaces.
*/
void trimstr (char *str, char *result)
{
    int flag = 0;   // For making after ] empty
    int index = 0;  // current index in result
    char space = ' ';   // space
    char *ptr;    //Pointer to string
    ptr = &str[0];   // Points to the start of the string
    while (*(ptr) != '\0')
    {
       if (*ptr != space)   // Write to result array
       {
           result[index++] = *ptr;
       }
       if ((*ptr == space) && ((*(ptr+1) != space)) )   // Just one space, write.
       {
           result[index++] = *ptr;
       }
        ptr++;  // Go to the next char
    }
    // Shift and delete first element if it is empty space
    if (result[0] == ' ') {  
        for(int i=0; i<strlen(result)-1;i++)    {
        result[i]=result[i+1];
        }
    }
    // Find [int], if there is a space remove space by shifting it.
    for (int i = 0; i < strlen(result); i++)
    {
        if(result[i] == '[')    index = i-1;
        
    }
    // Shift from space before '['
    if (result[index] == ' ')
    {
        for(int i=index; i<strlen(result)+1;i++)  
        {
            result[i]=result[i+1];
        }
    }
    // Find the index of the last element which is ], go to label
    for (int i = 0; i < strlen(result); i++)
    {
        if(result[i] == ']') {
            index = i;  // Last element
            goto label;
        }   
    }
    label:result[index+1] = '\0';   // Terminate the string in this location
}