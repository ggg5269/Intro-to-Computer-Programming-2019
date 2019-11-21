#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char *argv[])
{
    // EX.2
    int A, B, C;    // variable
    int *D, *E, *F; // D, E, F are pointers

    A = 10;
    B = 20;
    C = 30;
    D = &A;                // *D = 10
    E = &B;                // *E = 20
    F = &C;                // *F = 30
    *F = *E * A + *D * *E; // = 20 * 10 + 10 * 20 = C

    printf("C = %d\n", C);

    return 0;
}