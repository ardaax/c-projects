#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SHAPES 50

/* type definitions come here */

const char delim[2] = " ";
/* type definitions come here */

typedef struct
{
    double x;
    double y;
}point_t;

typedef struct
{
    point_t center;
    double radius;
}circle_t;

typedef struct
{
    point_t b_left_c;
    double side;
}square_t;

typedef struct
{
    point_t b_left_c;
    double width;
    double height;
}rectangle_t;

typedef union
{
    circle_t circle;
    square_t square;
    rectangle_t rectangle;
}shape_data_t;

typedef enum {CIRCLE, SQUARE, RECTANGLE} class_t;

typedef struct
{
    class_t type;
    shape_data_t shape;
}shape_t;



int scanShape(FILE *filep, shape_t *objp)
{
    if(filep != NULL) {
        char line[100];
        if(fgets(line, sizeof(line), filep) != NULL) {
        char *token;
        token = strtok(line, delim);
        char name[50];
        strcpy(name, token);
        double x, y;
        if(strcmp(name, "circle") == 0) {
            (*objp).type = 0;
            double rad; //radius
            token = strtok(NULL, delim);    // center x
            x = atof(token);
            token = strtok(NULL, delim);    // center y
            y = atof(token);
            token = strtok(NULL, delim);    // radius
            rad = atof(token);

            (*objp).shape.circle.center.x = x;
            (*objp).shape.circle.center.y = y;
            (*objp).shape.circle.radius = rad;
            //printf("Circle %.2f %.2f %.2f\n", (*objp).shape.circle.center.x, (*objp).shape.circle.center.y, (*objp).shape.circle.radius);
            return 1; 
        }
            else if(strcmp(name, "square") == 0) {
                (*objp).type = 1;
                double side; //side
                token = strtok(NULL, delim);    // center x
                x = atof(token);
                token = strtok(NULL, delim);    // center y
                y = atof(token);
                token = strtok(NULL, delim);    // side
                side = atof(token);

                (*objp).shape.square.b_left_c.x = x;
                (*objp).shape.square.b_left_c.y = y;
                (*objp).shape.square.side = side;

                //printf("Square %.2f %.2f %.2f\n", (*objp).shape.square.b_left_c.x, (*objp).shape.square.b_left_c.y, (*objp).shape.square.side);
                return 1; 
            }
            else if(strcmp(name, "rectangle") == 0) {
                (*objp).type = 2;
                double width, height; //widht and height
                token = strtok(NULL, delim);    // center x
                x = atof(token);
                token = strtok(NULL, delim);    // center y
                y = atof(token);
                token = strtok(NULL, delim);    // width
                width = atof(token);
                token = strtok(NULL, delim);    // height
                height = atof(token);

                (*objp).shape.rectangle.b_left_c.x = x;
                (*objp).shape.rectangle.b_left_c.y = y;
                (*objp).shape.rectangle.width = width;
                (*objp).shape.rectangle.height = height;

                //printf("Rectangle %.2f %.2f %.2f %.2f\n", (*objp).shape.rectangle.b_left_c.x, (*objp).shape.rectangle.b_left_c.y, (*objp).shape.rectangle.width, (*objp).shape.rectangle.height);
                return 1; 
            }
        }
    }
    return 0;
}


int loadShapes(shape_t shapes[])    {
    int num_read_shapes = 0;
    int scanshape_return = 0;
    char file_name[50];
    FILE *fp;
    printf("Enter the file name to read:\n");
    scanf("%s", file_name);
    printf("Opening %s\n", file_name);
    fp = fopen(file_name, "r");

    
    for (int i = 0; i < MAX_SHAPES; i++)
    {
        scanshape_return = scanShape(fp, &shapes[i]);
        //printf("%d scanshape_return value\n", scanshape_return);
        if(scanshape_return == 0) 
        {
            break;
        }
        if(scanshape_return == 1) num_read_shapes++;
    }
    
    
    
    printf("Loading complete\n");
    printf("Closing %s\n", file_name);
    fclose(fp);
    return num_read_shapes;
}


void printShape(const shape_t *objp){
    if((*objp).type == 0)  //Circle
    printf("Circle: <%.2f %.2f><%.2f>\n", (*objp).shape.circle.center.x, (*objp).shape.circle.center.y, (*objp).shape.circle.radius);

    if((*objp).type == 1)  //Square
    printf("Square: <%.2f %.2f><%.2f>\n", (*objp).shape.square.b_left_c.x, (*objp).shape.square.b_left_c.y, (*objp).shape.square.side);

    if((*objp).type == 2)  //Rectangle
    printf("Rectangle: <%.2f %.2f><%.2f><%.2f>\n", (*objp).shape.rectangle.b_left_c.x, (*objp).shape.rectangle.b_left_c.y, (*objp).shape.rectangle.width, (*objp).shape.rectangle.height);    
}



void translate(shape_t *objp, double d){
    if((*objp).type == 0)  //Circle 
    {
        (*objp).shape.circle.center.x += d;
        (*objp).shape.circle.center.y += d;
    }
    else if((*objp).type == 1)  //Square 
    {
        (*objp).shape.square.b_left_c.x += d;
        (*objp).shape.square.b_left_c.y += d;
    }
    else if((*objp).type == 2)  //Rectangle 
    {
        (*objp).shape.rectangle.b_left_c.x += d;
        (*objp).shape.rectangle.b_left_c.y += d;
    }
}

void scale(shape_t *objp, double f){
    if((*objp).type == 0)  //Circle 
    {
        (*objp).shape.circle.radius *= f;
    }
    else if((*objp).type == 1)  //Square 
    {
        (*objp).shape.square.side *= f;
    }
    else if((*objp).type == 2)  //Rectangle 
    {
        (*objp).shape.rectangle.width *= f;
        (*objp).shape.rectangle.height *= f;
    }
}

/* function prototypes*/
int scanShape(FILE *filep, shape_t *objp);
int loadShapes(shape_t shapes[]);
void printShape(const shape_t *objp);
void translate(shape_t *objp, double d);
void scale(shape_t *objp, double f);

int main()
{
    shape_t shapes[MAX_SHAPES];
    int numOfShapes = loadShapes(shapes);

    printf("\nShapes:\n");
    for (int i = 0; i < numOfShapes; i++)
        printShape(&shapes[i]);

    double d;
    printf("\nEnter the translation amount: ");
    scanf("%lf",&d);
    for (int i = 0; i < numOfShapes; i++)
        translate(&shapes[i],d);

    printf("\nShapes after translation by %.2lf:\n",d);
    for (int i = 0; i < numOfShapes; i++)
        printShape(&shapes[i]);

    double f;
    printf("\nEnter the scale factor: ");
    scanf("%lf",&f);
    for (int i = 0; i < numOfShapes; i++)
        scale(&shapes[i],f);

    printf("\nShapes after scaling by %.2lf:\n",f);
    for (int i = 0; i < numOfShapes; i++)
        printShape(&shapes[i]);

    return 0;
}
