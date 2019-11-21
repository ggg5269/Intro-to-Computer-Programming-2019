#include "stdio.h"
#include "string.h"

/*
* action || binary file| text file
* ==============================
* open   || fopen      | fopen
* ------------------------------
* read   || fread      | fscanf
* ------------------------------
* write  || fwrite     | fprintf
* ------------------------------
* close  || fclose     | fclose
* ------------------------------
* check  ||        feof
*        ||        fseek
*        ||        ftell
*/

// analyze RFC3261.txt

int main(int argc, char *argv[])
{
    FILE *In;
    int i, j, k, KL;
    double a;
    char S1[2000];
    char A1[100], A2[100], Key[100];
    int C[26];

    // * open file
    if ((In = fopen("rfc3261.txt", "rb")) == 0)
    {
        printf("txt file not found\n");
        return 0;
    }

    //  * 1. calculate file size by while loop
    i = 0;
    while (!feof(In))
    {
        fread(S1, 1, 1, In); //fread(memory, how many, size, variable)
        i++;
    }
    printf("file size = %d\n", i - 1);

    // * 2. calculate file size by ftell
    fseek(In, 0, SEEK_END); // move pointer to the last
    i = ftell(In);          // tell the position of pointer
    fseek(In, 0, 0);        // move the pointer back
    printf("file size = %d\n", i);

    // * count frequency of letters
    for (i = 0; i < 26; i++)
    {
        C[i] = 0;
    }

    i = 0;
    while (!feof(In))
    {
        fread(S1, 1, 1, In);
        if ((S1[0] >= 'a') && (S1[0] <= 'z'))
        {
            j = (int)(S1[0] - 'a');
            C[j]++;
        }
        if ((S1[0] >= 'A') && (S1[0] <= 'Z'))
        {
            j = (int)(S1[0] - 'A');
            C[j]++;
        }
        i++;
    }
    for (k = 0; k < 26; k++)
    {
        printf("%c appears %5d times\n", k + 'a', C[k]);
    }

    // * input keyword
    printf("input keyword: \n");
    scanf("%s", Key);
    KL = strlen(Key);
    for (i = 0; i < KL; i++)
    {
        Key[i] |= 0x20; // * 改小寫
    }
    printf("Key = %s\n", Key);

    // * count SIP

    i = 0;
    k = 0;
    while (!feof(In))
    {
        fread(A1, 1, 1, In); // * read 1 letter
        A1[0] |= 0x20;

        for (j = 0; j < KL; j++)
        {
            A2[j] = A2[j + 1]; // * push forward
        }

        A2[KL] = A1[0];

        if (!strncmp(A2, Key, KL))
        {
            k++;
        }
    }

    printf("%s appears %d times\n", Key, k);

    /*
    * wrong
    a = 0;
    while(!feof(In))
    {
        fread(S1, 3, 1, In);
        if((S1[0]=='S') && (S1[1]=='I') && (S1[2]=='P'))
        {
            a++;
        }
    }
    printf("%d\n", a);*/
    return 0;
}
