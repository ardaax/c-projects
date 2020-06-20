 #include <stdlib.h>
 #include <stdio.h>
 #include <string.h>
 #define MAX_SIZE 1000

typedef struct
    {
    __uint8_t R;
    __uint8_t G;
    __uint8_t B;
    }pixel_data;


FILE *inp;	// Pointer to input image file
FILE *outp;	// Pointer to cropped output image file
FILE *outp2;    // Pointer to the magnified image file
const __uint8_t black = 0;


 int main(int argc, char **argv) 
 {

    char in_text[MAX_SIZE];
    char out_text[MAX_SIZE];
    char out_double_text[] = "D";
    /* Reading and assigning command line arguments to variables */
    strcpy(in_text, argv[1]);
    strcpy(out_text, argv[2]);
	int CropC = atoi(argv[3]);
	int CropR = atoi(argv[4]);
	int CropWidth = atoi(argv[5]);
	int CropHeight = atoi(argv[6]);

    

    inp = fopen(in_text, "rb");
    if (!inp)
	{
		fprintf(stderr, "Unable to open file %s", in_text);
		exit(1);
	}
    outp = fopen(out_text, "w");
    pixel_data pixel;
    char img_type_str[4];   //GRY or RBG
    __int8_t num_bands;  // 1 for grayscale, 3 for RGB
    int rown;   // Row number
    int coln;   // Column number
    __int8_t num_bits;   // Should always be 8 for RGB
    printf("size of int : %d\n",sizeof(pixel));

    fseek(inp, 0, SEEK_END);
    int size = ftell(inp);  //Size of the file
    rewind(inp);    // Return to beginning

    // HEADER READ 
    fread(img_type_str,4,1,inp);
    fread(&num_bands,1,1,inp);
    fread(&rown,4,1,inp);
    fread(&coln,4,1,inp);
    fread(&num_bits,1,1,inp);
    printf("%d %s %u %d %d %u\n", size, img_type_str, num_bands, rown, coln, num_bits);
    fwrite(img_type_str,4,1,outp);
    fwrite(&num_bands,1,1,outp);
    fwrite(&CropHeight, 4, 1, outp);
    fwrite(&CropWidth, 4, 1, outp);
    fwrite(&num_bits, 1, 1, outp);

    // Normal output for writing
    pixel_data *arr = (pixel_data *)malloc(rown * coln * sizeof(pixel_data)); 


    // Fill the array with whole image
    for(int r = 0; r<rown; r++)
    {
        for (int c = 0; c < coln; c++)
        {
            fread(&(*(arr + r*coln + c)).R, 1, 1, inp);
            fread(&(*(arr + r*coln + c)).G, 1, 1, inp);
            fread(&(*(arr + r*coln + c)).B, 1, 1, inp);
        }
    }
    
    // Normal size empty array keeps the cropped image
    pixel_data *arr_img = (pixel_data *)malloc(CropHeight * CropWidth * sizeof(pixel_data)); 
 

    // This code writes the cropped region to a new array called arr_img also the original file
    // arr_img is used for double image
    // We keep 4 indices 2 for writing to normal file, 2 for writing to arr_img
    int row_index = 0;  //row for arr_img
    int col_index = 0;  //column for arr_img
    printf("CropR = %d, Crop Height = %d, CropC = %d, Crop Width = %d\n",CropR, CropHeight, CropC, CropWidth);
    for(int r = CropR; r<CropR + CropHeight; r++)
    {
        col_index = 0;
        for (int c = CropC; c < CropC + CropWidth; c++)
        {
            if(r<rown && c<coln){   // Within the image boundaries
                fwrite(&(*(arr + r*coln + c)).R, 1, 1, outp);
                fwrite(&(*(arr + r*coln + c)).G, 1, 1, outp);
                fwrite(&(*(arr + r*coln + c)).B, 1, 1, outp);
                (*(arr_img + row_index*CropWidth + col_index)).R = (*(arr + r*coln + c)).R;
                (*(arr_img + row_index*CropWidth + col_index)).G = (*(arr + r*coln + c)).G;
                (*(arr_img + row_index*CropWidth + col_index)).B = (*(arr + r*coln + c)).B;
            }
            else if((c>=coln) && (r<rown) || (r >= rown && c<coln) || (r >= rown && c>=coln))   //Outside the image boundaries.
            {
                fwrite(&black, 1, 1, outp);        
                fwrite(&black, 1, 1, outp);
                fwrite(&black, 1, 1, outp);
                (*(arr_img + row_index*CropWidth + col_index)).R = black;
                (*(arr_img + row_index*CropWidth + col_index)).G = black;
                (*(arr_img + row_index*CropWidth + col_index)).B = black;

            }
            col_index++;
        }
        row_index++;
    }
   
  
    // Double sized image
    int newr = CropHeight*2;
    int newc = CropWidth*2;
    pixel_data *arr_double = (pixel_data *)malloc(newr * newc * sizeof(pixel_data)); 

    
    // Filling the double image array
    // Keeping 4 indices.
    int d_row = 0;
    int d_col = 0; 
    for (int i = 0; i < CropHeight; i++)
    {
        d_col = 0;
        for (int j = 0; j < CropWidth; j++)
        {
            // Itself
            (*(arr_double + d_row*newc + d_col)).R = (*(arr_img + i*CropWidth + j)).R;
            (*(arr_double + d_row*newc + d_col)).G = (*(arr_img + i*CropWidth + j)).G;
            (*(arr_double + d_row*newc + d_col)).B = (*(arr_img + i*CropWidth + j)).B;
            //Next column
            (*(arr_double + d_row*newc + d_col+1)).R = (*(arr_img + i*CropWidth + j)).R;
            (*(arr_double + d_row*newc + d_col+1)).G = (*(arr_img + i*CropWidth + j)).G;
            (*(arr_double + d_row*newc + d_col+1)).B = (*(arr_img + i*CropWidth + j)).B;
            //Next row
            (*(arr_double + (d_row+1)*newc + d_col)).R = (*(arr_img + i*CropWidth + j)).R;
            (*(arr_double + (d_row+1)*newc + d_col)).G = (*(arr_img + i*CropWidth + j)).G;
            (*(arr_double + (d_row+1)*newc + d_col)).B = (*(arr_img + i*CropWidth + j)).B;
            //Next row and column
            (*(arr_double + (d_row+1)*newc + d_col+1)).R = (*(arr_img + i*CropWidth + j)).R;
            (*(arr_double + (d_row+1)*newc + d_col+1)).G = (*(arr_img + i*CropWidth + j)).G;
            (*(arr_double + (d_row+1)*newc + d_col+1)).B = (*(arr_img + i*CropWidth + j)).B;

            d_col += 2;
        }
        d_row += 2;
    }
    
    // Double image text and opening it.
    char *temp = malloc(sizeof(img_type_str));
    strcpy(temp, img_type_str);
    strcat(out_double_text, out_text);
    outp2 = fopen(out_double_text, "w");

    // Writing to the double image
    fwrite(temp,4,1,outp2);
    fwrite(&num_bands,1,1,outp2);
    fwrite(&newr, 4, 1, outp2);
    fwrite(&newc, 4, 1, outp2);
    fwrite(&num_bits, 1, 1, outp2);
    for (int i=0; i<newr; i++) {
        for(int j=0; j<newc; j++) {
            fwrite(&(*(arr_double + i*newc + j)).R, 1, 1, outp2);
            fwrite(&(*(arr_double + i*newc + j)).G, 1, 1, outp2);
            fwrite(&(*(arr_double + i*newc + j)).B, 1, 1, outp2);
        }
    }

    // FREE
    free(arr);
    free(arr_img);
    free(arr_double);
    fclose(inp);
    fclose(outp);
    fclose(outp2);
    
    return 0;
 }