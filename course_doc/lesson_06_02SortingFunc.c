#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

void Swap(int *a, int *b)
{
    int c;
    c = *a;
    *a = *b;
    *b = c;
}

// * Bubble Sorting
void Sorting(int *A)
{
    int i, j, k;
    for (i = 0; i < 9; i++)
    {
        for (j = i + 1; j < 10; j++)
        {
            if (A[i] < A[j])
                // * Both works
                // Swap(&A[i], &A[j]);
                Swap(A + i, A + j);
        }
    }
}

int main(int argc, char *argv[])
{
    int A[10] = {6, 1, 9, 3, 4, 0, 8, 2, 5, 7}; // A is a pointer
    int i;
    for (i = 0; i < 10; i++)
    {
        printf("A[%d] = %d\n", i, A[i]);
    }
    Sorting(A);
    printf("\n");
    for (i = 0; i < 10; i++)
    {
        printf("A[%d] = %d\n", i, A[i]);
    }

    return 0;
}