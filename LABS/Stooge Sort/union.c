#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <ctype.h>

/**
 Given two arrays of pointers to strings which contains name and surname as in the format of "name,surname", 
	1 . find the union strings of two given name&surname list and print them. 
	2 . separate the strings according to "," caharacter and print the names and surnames in format of "Surname Name".

**/
/****************************/
// TODO : FILL HERE
// Function Prototype

/****************************/

void unionlist(char* a1[], char* a2[], int size1, int size2)
{
	int duplicate_size = 0;	//Size of the duplicate elements.
	/* First we need to find the size of union array */
	for(int n=0; n<size1; n++) {
		for (int m = 0; m < size2; m++) {
			if(strcmp(a1[n], a2[m]) == 0)	// Found duplicate skip the mth iteration
			{
				duplicate_size++;
				break;
			}
		}
	}
	int union_size = size1 + size2 - duplicate_size;	//Size of our union array.
	char *duplicate_arr[duplicate_size];	// Duplicate array of pointers.


	int cnt = 0;	// Index of duplicate array
	/* Now we fill the duplicate array just like above*/
	for(int n=0; n<size1; n++) {
		for (int m = 0; m < size2; m++) {
			if(strcmp(a1[n], a2[m]) == 0)	// Found duplicate skip the mth iteration
			{
				duplicate_arr[cnt] = (char *) malloc((strlen(a2[m])+1)*sizeof(char));
				strcpy(duplicate_arr[cnt], a2[m]);
				cnt++;
				break;
			}
		}
	}
	

	/* Now we have found the duplicates and filled our array
	   We can fill unionset array
	*/
	char *unionset[union_size];
	int unionset_index = 0;
	// Let us first fill with elements just in a1
	for (int i = 0; i < size1; i++) {
		int flag = 0;	// Did we find a common
		for (int d = 0; d < duplicate_size; d++)
		{
			if(strcmp(a1[i], duplicate_arr[d]) == 0) {
				flag = 1;
				break;
			}
		}

		if(flag == 0) {	// We didn't find a common add it to the array
		unionset[unionset_index] = (char *) malloc((strlen(a1[i])+1)*sizeof(char));
		strcpy(unionset[unionset_index], a1[i]);
		unionset_index++;
		}	
	}

	// Fill all of the array2
	for (int i = 0; i < size2; i++) {
		unionset[unionset_index] = (char *) malloc((strlen(a2[i])+1)*sizeof(char));
		strcpy(unionset[unionset_index], a2[i]);
		unionset_index++;
	}
	

	// Print the union array
	char *message = "Union of array of pointers to strings Name&Surname";
	int mess_size = strlen(message);	// Size of the message
	printf("%s\n", message);
	for (int m = 0; m < mess_size; m++) printf("-");
	printf("\n");
	for (int i = 0; i < union_size; i++)
	{
		printf("Name&Surname %d : %s\n", i+1, unionset[i]);
	}
	



	/****************************************************/
	/****************************************************/
	// TODO: FILL HERE
	/** 2 . String Operations Part **/
	// Hint : Don't forget to use memory allocation 
	//for each array of pointers for applying String operations.
	/****************************************************/
	/****************************************************/
	printf("\n");
	char *message2 = "Surname&Name";
	int mess_size2 = strlen(message2);	// Size of the message
	printf("%s\n", message2);
	for (int m = 0; m < mess_size2; m++) printf("-");
	printf("\n");
	const char s[2] = ",";
	for(int x = 0; x<union_size; x++)
	{
		char *str = (char *) malloc((strlen(unionset[x])+1)*sizeof(char));
		strcpy(str, unionset[x]);
		/* get the first token */
		char *token;
   		token = strtok(str, s);
		
		char *name = (char *) malloc((strlen(token)+1)*sizeof(char));
		strcpy(name, token);

		token = strtok(NULL, s);
		char *surname = (char *) malloc((strlen(token)+1)*sizeof(char));
		strcpy(surname, token);

		
		name[0] = toupper(name[0]);
		surname[0] = toupper(surname[0]);
		printf("Surname&Name %d : %s %s\n", x+1, surname, name);
	}
	

	


}


int main(void)
{
    char p1[] = "zoe,lang";
    char p2[] = "sam,rodriguez";
    char p3[] = "jack,alonso";
    char p4[] = "david,studi";
    char p5[] = "denzel,feldman";
    char p6[] = "james,bale";
    char p7[] = "james,willis";
    char p8[] = "michael,loaf";
    char p9[] = "dustin,vin";

/***************************************/
/***************************************/
   
	//TODO : FILL HERE
	/** Create two array of pointers 
	1. First array of pointers : p1, p4, p9, p3, p2, p8,p5
	2. Second array of pointer : p9, p5, p1, p6, p7

	**/
	char *group1[] = {p1, p4, p9, p3, p2, p8,p5};
	char *group2[] = {p9, p5, p1, p6, p7};
/***************************************/
/***************************************/
	int size1 = sizeof(group1) / sizeof(group1[0]);
	int size2 = sizeof(group2) / sizeof(group2[0]);
	//printf("%d", size1); 

/****************************/
	// TODO: FILL HERE
	// Call unionlist here
	unionlist(group1, group2, size1, size2);
/****************************/

    return 0;
}
