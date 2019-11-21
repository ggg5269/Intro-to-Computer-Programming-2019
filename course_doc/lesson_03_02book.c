#include "stdio.h"
#include "string.h" // for string

int main(int argc, char *argv[])
{
    FILE *Inl;       // for file // * pointer
    char N[100][10]; // for name, at most 100 students, at most 10 bytes for name
    char S1[10];     // for name searching
    int S[100][5];   // for score
    int i, j, k, l;

    Inl = fopen("Book1.txt", "rb"); // rb for which kind of file you are opening
    if (Inl == 0)
    {
        printf("Book1 not found\n");
        return 0;
    }

    // ? read the data
    i = 0;             // * IMPORTANT!!
    while (!feof(Inl)) // feof: file end of file
    {                  // if it's not the end of the file, keep reading
        fscanf(Inl, "%s %d %d %d %d\n", &N[i][0], &S[i][0], &S[i][1], &S[i][2], &S[i][3]);
        S[i][4] = (S[i][0] + S[i][1] + S[i][2] + S[i][3]); // * total score

        // ! fscanf: scan from file, doesn't care about how many spaces between two string
        i++;
    }
    printf("%d data imported\n", i);

    // ? search for specific letter
    for (k = 0; k < i; k++)
    {
        if (!strncmp(&N[k][0], "陳", 2) | !strncmp(&N[k][0], "張", 2))
        {
            //strncmp(first string, second string, size of str)
            printf("%s %3d %3d %3d %3d %3d\n", &N[k][0], S[k][0], S[k][1], S[k][2], S[k][3], S[k][4]);
            // &N[k][0] for string, always use pointer!
            // no need for int.
        }
    }

    // ? search for full name
    printf("Full Name = ");
    scanf("%s", S1); // input NAME
    for (k = 0; k < i; k++)
    {
        if (!strcmp(&N[k][0], S1))
        {
            //strcmp compare full string
            printf("%s %3d %3d %3d %3d %3d\n", &N[k][0], S[k][0], S[k][1], S[k][2], S[k][3], S[k][4]);
            // &N[k][0] for string, always use pointer!
            // no need for int.
        }
    }

    // ? search by keywords
    printf("keyword = ");
    scanf("%s", S1); // input NAME
    j = strlen(S1);  // set length of the letter input

    for (k = 0; k < i; k++) // * for every row of names
    {
        for (l = 0; l < strlen(&N[k][0]); l += 2) // ! +2 each time, cus chinese word is 2 bytes
        {
            if (!strncmp(&N[k][l], S1, j)) // * strcmp compare full string
            {
                printf("%s %3d %3d %3d %3d %3d\n", &N[k][0], S[k][0], S[k][1], S[k][2], S[k][3]), S[k][4];
                // &N[k][0] for string, always use pointer!
                // no need for int.
            }
        }
    }

    return 0;
}
