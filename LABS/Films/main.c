#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    unsigned int id; // film id
    char name[20]; // film name
    char format[5]; // format of film = 3d or 2d
    char showDate[20]; //show date of film
    char showTime[20]; // show time
    int price; // ticket price
    int capacity; // remain capacity of the saloon
}filmData;

const int size = sizeof(filmData);

void showRecords(FILE *filePtr);

int updateCapacity(FILE *filePtr, unsigned int id, int newCapacity);
int addFilm(FILE *filePtr, unsigned int id, char name[20], char format[5], char showDate[20], char showTime[20], int price, int capacity);
int deleteFilm(FILE *filePtr, unsigned int id);
int showLowPriced2DFilms(FILE *filePtr, int maxPrice);

int main()
{
    //printf("%d %d %d\n", size, sizeof(unsigned int), sizeof(int));
    unsigned int id;
    int newCapacity;
    int status;

    char name[20];
    char format[5];
    char showDate[20];
    char showTime[20];
    int price;
    int capacity;

    int count;
    int maxPrice;

    FILE *filePtr;
    filePtr = fopen("films.bin","rb+");
    if (filePtr == NULL)
    {
        printf("Could not open films.bin");
        return 0;
    }

    showRecords(filePtr);

    int choice;

    printf("\nWhich operation do you choose?\n");
    printf("1 : Update Capacity\n");
    printf("2 : Add Film\n");
    printf("3 : Delete Film\n");
    printf("4 : Show Low-priced 2D Films\n");
    printf("> ");
    scanf("%d",&choice);

    switch (choice)
    {
    case 1:
        printf("\nFilm id: ");
        scanf("%d",&id);
        printf("New capacity: ");
        scanf("%d",&newCapacity);
        status = updateCapacity(filePtr, id, newCapacity);
        if (status == 1)
            showRecords(filePtr);
        else
            printf("No film with id %d\n", id);
        break;
    case 2:
        printf("\nFilm id: ");
        scanf("%d",&id);
        printf("Name: ");
        scanf("%s",name);
        printf("Format: ");
        scanf("%s",format);
        printf("Show date: ");
        scanf("%s",showDate);
        printf("Show time: ");
        scanf("%s",showTime);
        printf("Price: ");
        scanf("%d",&price);
        printf("Capacity: ");
        scanf("%d",&capacity);
        status = addFilm(filePtr, id, name, format, showDate, showTime, price, capacity);
        if (status == 1)
            showRecords(filePtr);
        else
            printf("There is already a film with id %d\n", id);
        break;
    case 3:
        printf("\nFilm id: ");
        scanf("%d",&id);
        status = deleteFilm(filePtr, id);
        if (status == 1)
            showRecords(filePtr);
        else
            printf("No film with id %d\n", id);
        break;
    case 4:
        printf("\nMax price: ");
        scanf("%d",&maxPrice);
        count = showLowPriced2DFilms(filePtr, maxPrice);
        if (count == 0)
            printf("No 2D film with a price <= %d\n", maxPrice);
        else
            printf("There are %d 2D films with a price <= %d\n", count, maxPrice);
        break;
    }

    fclose(filePtr);
    return 0;
}

void showRecords(FILE *filePtr)
{
    fseek(filePtr, 0, SEEK_SET);

    printf("\n%-3s %-20s %-10s %-12s %-12s %-10s %s\n",
                   "ID",
                   "Name",
                   "Format",
                   "Show Date",
                   "Show Time",
                   "Price",
                   "Capacity");

    while (!feof(filePtr))
    {
        filmData film;
        int result = fread(&film, sizeof(filmData), 1, filePtr);
        if (result != 0 && film.id != 0)
        {
            printf("%-3d %-20s %-10s %-12s %-12s %-10d %d\n",
                   film.id,
                   film.name,
                   film.format,
                   film.showDate,
                   film.showTime,
                   film.price,
                   film.capacity);
        }
    }
}

int updateCapacity(FILE *filePtr, unsigned int id, int newCapacity)
{
    int result = 0;
    filmData fd;
    int offset = (size*(id-1));
    fseek(filePtr,offset,SEEK_SET);   // Go to begginning
    fread(&fd, sizeof(filmData) ,1,filePtr);
    if(fd.id == id){
        fseek(filePtr,offset+76, SEEK_SET);  // go to the capacity.
        fwrite(&newCapacity, 4,1,filePtr);
        result = 1;
    }
    else result = 0;
    rewind(filePtr);
    return result;
}

int addFilm(FILE *filePtr, unsigned int id, char name[20], char format[5], char showDate[20], char showTime[20], int price, int capacity)
{
    int result = 0;
    filmData fd;
    int offset = (size*(id-1));
    fseek(filePtr,offset,SEEK_SET);   // Go to begginning
    fread(&fd,size,1,filePtr);
    if(fd.id != id){
        fseek(filePtr,offset, SEEK_SET);  
        fwrite(&id, 4,1,filePtr);
        fwrite(name, 20,1,filePtr);
        fwrite(format, 5,1,filePtr);
        fwrite(showDate, 20,1,filePtr);
        fwrite(showTime, 20,1,filePtr);
        fseek(filePtr,offset+72, SEEK_SET); // Couldnt figure out.
        fwrite(&price, 4,1,filePtr);
        fseek(filePtr,offset+76, SEEK_SET); // Couldnt figure out.
        fwrite(&capacity, 4,1,filePtr);
        result = 1;
    }
    else result = 0;
    rewind(filePtr);
    return result;
}

int deleteFilm(FILE *filePtr, unsigned int id)
{
    int result = 0;
    filmData fd;
    int offset = (size*(id-1));
    fseek(filePtr,offset,SEEK_SET); 
    fread(&fd,size,1,filePtr);

    if(fd.id==id){
        fseek(filePtr,offset,SEEK_SET);
        unsigned int id = 0; 
        char name[20] = ""; 
        char format[5] = ""; 
        char show_date[20] = ""; 
        char show_time[20] = ""; 
        int price = 0; 
        int capacity = 0; 
        fwrite(&id,sizeof(unsigned int), 1,filePtr);  
        fwrite(name, sizeof(name),1,filePtr);
        fwrite(format, sizeof(format),1,filePtr);
        fwrite(show_date, sizeof(show_date),1,filePtr);
        fwrite(show_time, sizeof(show_time),1,filePtr);
        fwrite(&price, sizeof(price),1,filePtr);
        fwrite(&capacity, sizeof(capacity),1,filePtr);
        result = 1;
    }
    else result = 0;
    
    return result;
}

int showLowPriced2DFilms(FILE *filePtr, int maxPrice)
{
    int result = 0;
    printf("\n%-3s %-20s %-10s %-12s %-12s %-10s %s\n",
                   "ID",
                   "Name",
                   "Format",
                   "Show Date",
                   "Show Time",
                   "Price",
                   "Capacity");
    fseek(filePtr,0,SEEK_SET);   // Go to begginning
    while (!feof(filePtr))
    {
        filmData film;
        fread(&film, sizeof(filmData), 1, filePtr);
        int format_result = strcmp("2d", film.format);
        if((format_result==0) && (film.price <= maxPrice))
        {
            result++;
            printf("%-3d %-20s %-10s %-12s %-12s %-10d %d\n",
                   film.id,
                   film.name,
                   film.format,
                   film.showDate,
                   film.showTime,
                   film.price,
                   film.capacity);
        }
    }
    return result;
}
