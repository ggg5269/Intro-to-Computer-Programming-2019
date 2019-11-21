#include "stdlib.h"
#include "stdio.h"
#define MAX 100

typedef struct DATA
{
    char N[10]; // name
    int S[5];   // scores
    int No;     // ID
    int Rank;   // rank
} DATA;

DATA A[MAX];
DATA *B;

int main(int argc, char *argv[])
{
    FILE *In;
    int i, No = 0;
    // * 1.open file

    if ((In = fopen("Book1.txt", "rb")) == 0)
    {
        printf("Book1.txt not found\n");
        return -1;
    }

    // * 2.read file
    No = 0;
    while (!feof(In))
    {
        fscanf(In, "%s %d %d %d %d\n",
               A[No].N,
               &A[No].S[0],
               &A[No].S[1],
               &A[No].S[2],
               &A[No].S[3]);
        A[No].S[4] = A[No].S[0] + A[No].S[1] + A[No].S[2] + A[No].S[3];
        A[No].No = No + 1;
        No++;
    }
    // * 3.print data
    B = A;
    for (i = 0; i < No; i++)
    {
        printf("ID = %d ,%s %d %d %d %d %d\n",
               B->No,
               B->N,
               B->S[0],
               B->S[1],
               B->S[2],
               B->S[3],
               B->S[4]);
        B++;
    }

    return 0;
}