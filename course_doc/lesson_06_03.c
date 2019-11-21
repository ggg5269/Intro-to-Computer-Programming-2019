#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

int Sub(int *a, int *b)
{
    int c;
    *a *= 2;
    *b >>= 1; // shift
    c = *a - *b;
    // c = *a - *b;
    return c;
}

void Fun(int *A)
{
    A += 2;
    *A += *(A + 2);
}

int main(int argc, char *argv[])
{
    int a = 10, b = 20, c, i;
    int A[10] = {6, 1, 9, 3, 4, 0, 8, 2, 5, 7};

    c = Sub(&a, &b);
    printf("a = %d, b = %d, c = %d\n", a, b, c);

    Fun(A);
    for (i = 0; i < 10; i++)
    {
        printf("A[%d] = %d\n", i, A[i]);
    }
    return 0;
}