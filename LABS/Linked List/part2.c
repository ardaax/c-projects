#include <stdio.h>
#include <stdlib.h>

#define SENT -1

struct node
{
    int value;
    struct node *next;
};

void printAll(struct node *headPtr);

void insertNode(struct node **headPtrPtr, int value);
struct node * unionList(struct node *hPtr1, struct node *hPtr2);
int traverse(struct node **headPtrPtr, int value);
int count(struct node **headPtrPtr);

int main()
{
    struct node *hPtr1 = NULL;
    struct node *hPtr2 = NULL;

    int value;
    int status;

    status = scanf("%d",&value);
    while (status == 1 && value != SENT)
    {
        insertNode(&hPtr1, value);
        status = scanf("%d",&value);
    }
    printf("List1: ");
    printAll(hPtr1);

    status = scanf("%d",&value);
    while (status == 1 && value != SENT)
    {
        insertNode(&hPtr2, value);
        status = scanf("%d",&value);
    }
    printf("List2: ");
    printAll(hPtr2);

    struct node *hPtrUn = unionList(hPtr1, hPtr2);
    printf("Union: ");
    printAll(hPtrUn);

    printf("List1: ");
    printAll(hPtr1);
    printf("List2: ");
    printAll(hPtr2);

    return 0;
}

void printAll(struct node *headPtr)
{
    struct node *tempPtr = headPtr;

    if (tempPtr == NULL)
        printf("Empty List\n");
    else
    {
        while (tempPtr != NULL)
        {
            printf("%d ",tempPtr->value);
            tempPtr = tempPtr->next;
        }
        printf("\n");
    }
}

void insertNode(struct node **headPtrPtr, int value)
{
    // to be implemented
    if((*headPtrPtr) == NULL) {
        (*headPtrPtr) = (struct node*)malloc(sizeof(struct node));
        (*headPtrPtr)->value = value;
        (*headPtrPtr)->next = NULL;
    }
    else {
        struct node *temp =  (struct node*)malloc(sizeof(struct node));;  //temporary for new
        temp->value = value;
        temp->next = (*headPtrPtr);
        (*headPtrPtr) = temp;
    }
}

struct node * unionList(struct node *hPtr1, struct node *hPtr2)
{
    //printf("Initial hpt1 %d\n", hPtr1);
    struct node *temp1 = hPtr1; //Keeps the hptr1
    struct node *temp2 = hPtr2; //Keeps the hptr1
    struct node *list_union = NULL;
    int count1 = count(&temp1);  //count the elements in hptr1


    int count2 = count(&temp2);  //count the elements in hptr2
    for (int i = 0; i<count2; i++)  // This many times of nodes to write
    {
        int new = count2 - i - 1;   // How many nodes to go
        for (int cnt = 0; cnt < new; cnt++)
        {
            //printf("%d\n", hPtr1->value);
            hPtr2 = hPtr2->next;
        }
        //printf("This is the value to write %d\n", hPtr2->value);

        
         if(traverse(&hPtr1,hPtr2->value) == 0) { // If it is not a duplicate value in hptr2
            insertNode(&list_union, hPtr2->value);
        }
        hPtr2 = temp2;
    }


    for (int i = 0; i<count1; i++)  // This many times of nodes to write
    {
        int new = count1 - i - 1;   // How many nodes to go
        for (int cnt = 0; cnt < new; cnt++)
        {
            //printf("%d\n", hPtr1->value);
            hPtr1 = hPtr1->next;
        }
        //printf("This is the value to write %d\n", hPtr1->value);
        insertNode(&list_union, hPtr1->value);
        hPtr1 = temp1;
    }

    
    return list_union;
}

int traverse(struct node **headPtrPtr, int value)
{
    int result = 0;
    struct node *temp1 = (*headPtrPtr); //Keeps the hptr1
    // Looks for a value in the linked list if found return 1, otherwise 0.
    while(temp1 != NULL)
    {
        if(temp1->value == value) result = 1;
        temp1 = temp1->next;
    }
    //printf("The result is %d and seach value is %d\n", result, value);
    return result;
}


int count(struct node **headPtrPtr)
{
    int i = 0;
    struct node *temp = (*headPtrPtr); //Keeps the hptr1
    // Count the number of elements
    while(temp != NULL) {
        i++;
        temp = temp->next;
    }
    //printf("Number of elements here is %d\n", i);
    return i;
}