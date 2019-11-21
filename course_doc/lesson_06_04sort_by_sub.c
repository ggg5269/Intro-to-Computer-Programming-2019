#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

#define MAX 100

int Read_File(char *F, int S1[][6], char N1[][10]) // ! 2d array as an argument
{
    int No = 0, i;
    FILE *In;
    //char S1[200];
    In = fopen(F, "rb");
    while (!feof(In))
    {
        fscanf(In, "%s %d %d %d %d\n", &N1[No][0], &S1[No][0], &S1[No][1], &S1[No][2], &S1[No][3]);
        S1[No][4] = (S1[No][0] + S1[No][1] + S1[No][2] + S1[No][3]);
        No++;
    }

    return No;
}

int Print_Data(int No, int S[][6], char N[][10], char *C)
{
    int i, j, k;
    // * parameter check
    if (No <= 0)
        return -1; // data empty
    else if (strlen(C) > 10)
        return -2; // filter condition error
    else if (S == 0)
        return -3; // score pointer error
    else if (N == 0)
        return -4; // name pointer error

    for (i = 0; i < No; i++)
    {
        for (k = 0; k < strlen(&N[i][0]); k++) // search every letters in name
        {
            if (!strncmp(C, &N[i][k], strlen(C)))
            {
                printf("%s ", &N[i][0]);
                for (j = 0; j < 6; j++)
                    printf(" %d", S[i][j]);
                printf("\n");
            }
        }
    }
    return 0;
}
/*==========
// ! SORTING
==========*/
int Sorting(int No, int S[][6], char N[][10])
{
    int n, i, j, k, m;
    char S1[10];
    n = No;                     // set n to 36
    for (i = 0; i < n - 1; i++) // find i_th place, i = 0-34
    {
        for (j = i + 1; j < n; j++)     // j = (i+1)-35
        {                               //
            if (S[i][4] < S[j][4])      // determine the direction
            {                           //
                for (k = 0; k < 6; k++) // swap for scores
                {
                    m = S[i][k];
                    S[i][k] = S[j][k];
                    S[j][k] = m;
                }
                // swap for names
                strcpy(S1, &N[i][0]);
                strcpy(&N[i][0], &N[j][0]);
                strcpy(&N[j][0], S1);
            }
        }
    }
    for (k = 0; k < n; k++)
    {
        S[k][5] = k + 1;
        //printf("rank = %2d %s %3d %3d %3d %3d %3d %3d %3d\n", k + 1, &N[k][0], S[k][0], S[k][1], S[k][2], S[k][3], S[k][4], S[k][5], S[k][6]);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int No, i;
    int S[MAX][6];
    char N[MAX][10];
    // * read file
    No = Read_File("Book1.txt", S, N);

    // * sorting
    Sorting(No, S, N);

    // * print name and score
    Print_Data(No, S, N, "¶À");

    /*
    for (i = 0; i < No; i++)
    {
        printf("%s %d %d %d %d\n", &N[i][0], S[i][0], S[i][1], S[i][2], S[i][3]);
    }
    */
    return 0;
}
