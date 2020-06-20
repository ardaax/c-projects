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