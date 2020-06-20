#include <stdio.h>
#include <stdlib.h>

struct node
{
    int value;
    struct node *next;
};

void printAll(struct node *headPtr);
int isEmpty(struct node *headPtr);

void insertNode(struct node **headPtrPtr, int value);
int deleteNode(struct node **headPtrPtr);

int main()
{
    struct node *headPtr = NULL;

    int choice;
    int value;
    int delValue;

    while (1)
    {
        printf("\n1 : insert\n");
        printf("2 : delete\n");
        printf("3 : quit\n\n");
        printf("> ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter value: ");
            scanf("%d", &value);
            insertNode(&headPtr, value);
            printf("List: ");
            printAll(headPtr);
            break;
        case 2:
            if (!isEmpty(headPtr))
            {
                delValue = deleteNode(&headPtr);
                printf("%d deleted\n",delValue);
            }
            printf("List: ");
            printAll(headPtr);
            break;
        case 3:
            return 0;
        }
    }

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

int isEmpty(struct node *headPtr)
{
    return (headPtr == NULL);
}

void insertNode(struct node **headPtrPtr, int value)
{
    // to be implemented
    if(isEmpty(*headPtrPtr) == 1) {
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

int deleteNode(struct node **headPtrPtr)
{
    int val=0;
    if(isEmpty(*headPtrPtr) == 0) { //The list is not empty
        struct node *temp = (*headPtrPtr)->next;
        val = (*headPtrPtr)->value;
        free((*headPtrPtr));
        (*headPtrPtr) = temp;
    }
    return val;
}