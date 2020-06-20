#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_SIZE 250

void swap_str(char **str1_ptr, char **str2_ptr) ;
void sort(char *strings[], int index_array[], int n);
void swap_int(int *x1, int *y1);
void convert_to_lower(char str[], int size);
int star_index(char str[], int size, int *index);
int isitmatch(char query[], char country[]);

/* Swaps strings by swapping pointers */ 
void swap_str(char **str1_ptr, char **str2_ptr) 
{ 
  char *temp = *str1_ptr; 
  *str1_ptr = *str2_ptr; 
  *str2_ptr = temp; 
}   



void sort(char *strings[], int index_array[], int n)
{
    int i, j, min_idx; 
    // One by one move boundary of unsorted subarray 
    for (i = 0; i < n-1; i++) 
    { 
        // Find the minimum element in unsorted array 
        min_idx = i; 
        //printf("Min indx is %d\n", min_idx);
        for (j = i+1; j < n; j++) {
            convert_to_lower(strings[j], strlen(strings[j]));
            convert_to_lower(strings[min_idx], strlen(strings[min_idx]));
          if (strcmp(strings[j], strings[min_idx]) < 0) {
            //printf("%s is smaller than %s\n", strings[j], strings[min_idx]);
            min_idx = j; 
            //printf("New Min idx is %d and str is %s\n", min_idx, strings[min_idx]);
          }
          
          else if(strcmp(strings[j], strings[min_idx]) == 0)    {
              if(index_array[j] < index_array[min_idx])
              min_idx = j;
          }
          
        }
  
        // Swap the found minimum element with the first element and swap indices in ind_arr
        //printf("Before swap %d %d\n", index_array[min_idx], index_array[i]);
        swap_int(&index_array[min_idx], &index_array[i]);
        swap_str(&strings[min_idx], &strings[i]);
        //printf("After swap %d %d\n", index_array[min_idx], index_array[i]);
    }	
    
}


void swap_int(int *x1, int *y1)
{
	int temp = *x1; 
	*x1 = *y1; 
	*y1 = temp; 
}

/* Convert the string to lower chars*/
/* WORKS */
void convert_to_lower(char str[], int size) {
    for (int i = 0; i < size; i++) {
        str[i] = tolower(str[i]);
    }
}

/* Finds the first occurence of '*' */
/* WORKS */
int star_index(char str[], int size, int *index) {
    for (int i = 0; i < size; i++)
    {
        if(str[i] == '*') {
            *index = i;
            return *index;
        } 
    }
    return *index;  
}

/* Returns 1 if there is a match, if not returns 0*/
/* WORKS */
int isitmatch(char query[], char country[]) {
    int result = 0;
    int star = '*';
    if(query[0] == star) return 1; // Starts with *, then it is a match

    int querylen = strlen(query);
    int countrylen = strlen(country);

    // Convert both query and country to lower chars
    convert_to_lower(query, querylen);
    convert_to_lower(country, countrylen);
    //printf("%s %s %d %d\n", query, country, querylen, countrylen);

    char* pPosition = strchr(query, '*');
    if(pPosition == NULL)   // There is no '*' char so just compare
    {
        //printf("Char * is NOT present\n");
        if(strcmp(query,country) == 0) result=1; //Match
        else result = 0;
    }
    if(pPosition != NULL)
    {
        //printf(" * Char is present\n");
        int index;
        star_index(query, querylen, &index);
        //printf("The index of '*' is %d\n", index);
        if(strncmp(query, country, index) == 0) result = 1;
        else result = 0;
    }
    


    return result;
}

FILE *inp;	// Pointer to input file WorldCities.txt
FILE *outp;	// Pointer to output file

int main(int argc, char **argv) {

    char in_text[MAX_SIZE];
    char out_text[MAX_SIZE];
    char search_str[MAX_SIZE];
    char *token;
    const char *delim = ",";	// Delimeter is comma

    /* Reading and assigning command line arguments to variables */
    strcpy(in_text, argv[1]);
    strcpy(search_str, argv[2]);
    strcpy(out_text, argv[3]);

    inp = fopen(in_text, "r");
    outp = fopen(out_text, "w");

    

    int line_c = -1;	// Number of lines in the input file
    char line[MAX_SIZE];
	/* With this while loop we count the number of lines in the file */
	while (fgets(line, sizeof(line), inp)) {
        //printf("%s", line); 
		line_c += 1;
    }
	rewind(inp);	// Pointing to the start of the file again.
    int count = 0;
    char header_line[MAX_SIZE];
    char *data_array[line_c];   // Will hold each line
    char *city_array[line_c];
    char *country_array[line_c];
    int id_array[line_c];
    strcpy(header_line, fgets(line, sizeof(line), inp));	// Read first line

    /* Reading the data dynamically allocating space */
    while (fgets(line, sizeof(line), inp)) {
        data_array[count] = (char *) malloc((strlen(line)+1)*sizeof(char));
        strcpy(data_array[count], line);
        
        
		char *array[7];
		int t = 0;	//Token count.
		token = strtok(line, delim);	// first tokenize
		while( token != NULL ) {
			array[t] = token;
      		token = strtok(NULL, delim);
			t++;
		 }
        id_array[count] = count;    // Fill id array starting from 0 to 2540
        city_array[count] = (char *) malloc((strlen(array[1])+1)*sizeof(char));
        strcpy(city_array[count], array[1]);    // Fill city array starting from 0 to 2540

        country_array[count] = (char *) malloc((strlen(array[2])+1)*sizeof(char));
        strcpy(country_array[count], array[2]); // Fill country array starting from 0 to 2540
        
        count++;
    }
    //printf("The size of array is %d\n", line_c);
    /* Now we will find the matches and count them */
    int result;
    int match_count = 0;    //Number of matches, this will be used for our array
    for (int i = 0; i < line_c; i++)
    {
        result = isitmatch(search_str, country_array[i]);
        if(result == 1) match_count++;
    }

    int matched_arr[match_count];   // Matched arrays ids
    char *matched_cities[match_count];  //Holds the cities that are matched.

    match_count = 0;
    /* Now we will fill matched arrays just like above*/
    for (int i = 0; i < line_c; i++)
    {
        result = isitmatch(search_str, country_array[i]);
        if(result == 1) 
        {
            matched_arr[match_count] = i;
            matched_cities[match_count] = (char *) malloc((strlen(city_array[i])+1)*sizeof(char));
            strcpy(matched_cities[match_count], city_array[i]);
            match_count++;
        }
    }
    
   
    
   sort(matched_cities, matched_arr, match_count);
   /*
    for (int i = 0; i < match_count; i++)
    {
       printf("This is the id %d and this is the city %s\n", matched_arr[i], matched_cities[i]);
    }
    */
   
    fputs(header_line, outp);
    for (int i = 0; i < match_count; i++)
    {
        fputs(data_array[matched_arr[i]], outp);
    }
    
    

    fclose(inp);
    fclose(outp);
    return 0;
}