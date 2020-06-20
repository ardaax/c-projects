#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEG_2_KM 111.194926644558550
#define DEG_2_RAD 0.017453292519943
#define RAD_2_DEG 57.295779513082323
#define MAX_SIZE 200

FILE *inp;	// Pointer to input file WorldCities.txt
FILE *outp;	// Pointer to output file

static double a = DEG_2_KM * RAD_2_DEG;


void swap(double *x1, double *y1);
void selectionSort(double arr[], double ind_arr[], int n);
double dms_converter(char letter[], int degree, int min, double sec);
double substr(int len, char arr[], int type);
double dis_cal(double lat1, double lon1, double lat2, double lon2);



void swap(double *x1, double *y1)
{
	double temp = *x1; 
	*x1 = *y1; 
	*y1 = temp; 
}



void selectionSort(double arr[], double ind_arr[], int n) 
{ 
    int i, j, min_idx; 
    // One by one move boundary of unsorted subarray 
    for (i = 0; i < n-1; i++) 
    { 
        // Find the minimum element in unsorted array 
        min_idx = i; 
        for (j = i+1; j < n; j++) 
          if (arr[j] < arr[min_idx]) 
            min_idx = j; 
  
        // Swap the found minimum element with the first element and swap indices in ind_arr
        swap(&arr[min_idx], &arr[i]);
				swap(&ind_arr[min_idx], &ind_arr[i]); 
    } 
} 



/* Returns the Decimal degrees given the DMS values */
double dms_converter(char letter[], int degree, int min, double sec)
{
	int sign = 0;
	if(strcmp("S", letter) == 0 || strcmp("W", letter) == 0)	sign = -1;
	else if(strcmp("E", letter) == 0 || strcmp("N", letter) == 0)	sign = 1;
	//printf("Sign is %d\n", sign);
	return sign*(degree + (min/60.0) + (sec/3600.0));
}



/* Returns the integer version of the string for degree*/
double substr(int len, char arr[], int type)
/* len is lenght of the array, arr is array, type is degree and mins */
{
		char tmp[len];	// This string holds numerical value
		char *str;
		strncpy(tmp, arr ,len);	// Copy it without special char.
		tmp[len] = '\0';
		if(type == 1)
		{
			tmp[2] = '\0';
			if(tmp[0] == '0')	str = &tmp[1];
			else	str = tmp;
			return atof(str);
		}
		else if(type == 2)
		{
			//tmp[7] = '\0';
			if(tmp[0] == '0')	str = &tmp[1];
			else	str = tmp;
			return atof(str);
		}
		return atof(tmp);	// Return doubleing type
}



double dis_cal(double lat1, double lon1, double lat2, double lon2)
{
	//printf("%d\n",a);
	double dist = a * acos(((cos(DEG_2_RAD* lat1) * cos(DEG_2_RAD * lat2) * cos(DEG_2_RAD * (lon1-lon2)))) + (sin(DEG_2_RAD*lat1) * sin(DEG_2_RAD*lat2)));
	return dist;
}


/* Return the string in a formatted way for output*/
/*
char *str(char *instr)
{
	//char *result = (char *) malloc(sizeof(instr[0]));
	char *result;
	printf("%Girdik");
	char *array[12];
	int t = 0;	//Token count.
	char *token;
	token = strtok(instr, "");	// first tokenize
	while( token != NULL ) {
		array[t] = token;
		token = strtok(NULL, "");
		t++;
		}
	strcat(result,array[0]);
	printf("%s", result);

}
*/




int main(int argc, char **argv)
{
	char in_text[MAX_SIZE];
	char out_text[MAX_SIZE];
	char *token;
	const char *delim = " ";	// Delimeter is space
	int input_status;

	/* Reading and assigning command line arguments to variables */
	double longtitude = atof(argv[1]);
	double latitude = atof(argv[2]);
	int range = atoi(argv[3]);
	strcpy(in_text, argv[4]);
	strcpy(out_text, argv[5]);

	inp = fopen(in_text, "r");
	outp = fopen(out_text, "w");

	char line[MAX_SIZE];
	int line_c = 0;	// Number of lines in the input file

	/* With this while loop we count the number of lines in the file */
	while (fgets(line, sizeof(line), inp)) {
        //printf("%s", line); 
		line_c += 1;
    }
	rewind(inp);	// Pointing to the start of the file again.

	char data_array[line_c-1][MAX_SIZE];	/* This is our double array holding cities database. */
	double decimal_data[line_c-1][2];	/* Latitude and longtitude of all coordinates in Decimal degrees format */
	double dist_array[line_c-1];	//Holds distances of all the coordinates w.r.t our coordinates.
	double index_array[line_c-1];	// When we swap elements in sorting the index numbers in this array will be swapped too.

	fgets(line, sizeof(line), inp);	// Read one line
	/* This while loop reads all the data line by line and populates data_array
		Also, it will tokenize and get the needed data to array
	 */
	int ctr = 0;

	while (fgets(line, sizeof(line), inp)) {
		strcpy(data_array[ctr], line);	// Copy the line to array.

		char *array[12];
		int t = 0;	//Token count.

		token = strtok(line, delim);	// first tokenize
		while( token != NULL ) {
			array[t] = token;
      		token = strtok(NULL, delim);
			t++;
		 }
		//printf("These are the cooardinates of latitude %s %s %s %s\n", array[1], array[2], array[3], array[4]);
	
		/* Getting rid of degree minute and seconds sign
		 and converting them to integers or doubles
		*/
		int dgr1 = (int)substr(strlen(array[1]) - 2, array[1], 0);
		int min1 = (int)substr(strlen(array[2]) - 1, array[2], 1);
		double sec1 = substr(strlen(array[3]) - 1, array[3], 2);
		//printf("After function return %d° %d' %.4lf\"\n", dgr1, min1, sec1);


		//printf("These are the cooardinates of longitude %s %s %s %s\n", array[5], array[6], array[7], array[8]);
		int dgr2 = (int)substr(strlen(array[5]) - 2, array[5], 0);
		int min2 = (int)substr(strlen(array[6]) - 1, array[6], 1);
		double sec2 = substr(strlen(array[7]) - 1, array[7], 2);

		//printf("After function return %d %d %lf\n", dgr2, min2, sec2);
	
		double longt = (double)dms_converter(array[4], dgr1, min1, sec1);
		double lat = (double)dms_converter(array[8], dgr2, min2, sec2);
		//printf("Logitude = %lf Latitude = %lf\n", longt, lat);

		decimal_data[ctr][0] = longt;
		decimal_data[ctr][1] = lat;
		ctr += 1;	// Increment the counter
    }
	
		/*
		Iterate through decimal data and calculate distances, then fill in distances array
		*/
		for(int i = 0; i<line_c-1; i++)
		{
			index_array[i] = i+1;	//Index array
			dist_array[i] = dis_cal(latitude, longtitude, decimal_data[i][1], decimal_data[i][0]);
		}

		selectionSort(dist_array, index_array, line_c-1);
		//printf("\n%lf %lf %d %s %s\n", longtitude, latitude, range, in_text, out_text);
		//printf("Number of lines = %d\n", line_c);

	/* Print to the file	*/
		int i = 0;
		while(dist_array[i] < range)
		{
			int curr_index = index_array[i];
			char *str = data_array[curr_index-1];
			//str = strtok(str, "\n");
			char *array[12];
			int t = 0;	//Token count.
			str = strtok(str, "\n");
			token = strtok(str, delim);	// first tokenize
			while( token != NULL ) {
				array[t] = token;
						token = strtok(NULL, delim);
				t++;
				}
			int min1 = (int)substr(strlen(array[2]) - 1, array[2], 1);
			double sec1 = substr(strlen(array[3]) - 1, array[3], 2);
			int min2 = (int)substr(strlen(array[6]) - 1, array[6], 1);
			double sec2 = substr(strlen(array[7]) - 1, array[7], 2);
			/*
			printf("%s %s %d' %.4lf\" %s %s %d' %.4lf\" %s %s %s %s %.2lf\n", array[0], array[1], min1, sec1, array[4], array[5], min2, sec2,
			array[8], array[9], array[10], array[11],  dist_array[i]
			);
			*/
			fprintf(outp, "%s %s %d' %.4lf\" %s %s %d' %.4lf\" %s %s %s %s %.2lf\n", array[0], array[1], min1, sec1, array[4], array[5], min2, sec2,
			array[8], array[9], array[10], array[11],  dist_array[i]
			);
			//printf("%s %.2lf\n", str, dist_array[i]);
			//fprintf(outp, "%s %.2lf\n", str, dist_array[i]);
			i++;
		}
		
	/* Close the files */
	fclose(inp);
	fclose(outp);

	return 0;
}