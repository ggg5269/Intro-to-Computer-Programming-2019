#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char *argv[])
{
    int A[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}; // ! A = array = pointer
    int *B;                                     // ! B = pointer
    int C;

    B = A;                             // *B = A
    C = B[3];                          // C = 6
    printf("B = %lx\n", B);            // print location
    printf("*B = %d C = %d\n", *B, C); // *B = A[0] = 9
    printf("\n");

    B++;                               // ! pointer B move forward, but  A cannot be calculated like this
    C = B[3];                          // calculation of pointer, move to the next memory space, now C = 5
    printf("B = %lx\n", B);            // move 4 bytes
    printf("*B = %d C = %d\n", *B, C); // C move to the next one as well
    printf("\n");

    C = B[3] * A[3];                   // A[3] stores the same value = 6, B[3] = 5
    printf("B = %lx\n", B);            //
    printf("*B = %d C = %d\n", *B, C); // C = 6 * 5 = 30
    printf("\n");

    return 0;
}