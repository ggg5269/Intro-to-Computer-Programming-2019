#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

int main(int argc, char *argv[])
{
    int num;
    FILE *fptr;
    // use appropriate location if you are using MacOS or Linux
    fptr = fopen("fileop.txt", "w");
    if (fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }
    printf("Enter num: ");
    scanf("%d", &num);
    fprintf(fptr, "you enter: %d\n", num);
    fputs("done!", fptr); // * simply put char in to file without format
    fclose(fptr);
    return 0;
}