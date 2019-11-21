#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// ! when to input to pointer, when to print with pointer

int main(int argc, char *argv[])
{
    int x, y, A[10], *B;
    char C[100], D[100];

    B = A;
    printf("please input x = ");
    //scanf("%d", &x);               // scanf need pointer &x
    //y = x * x;

    //scanf("%d", A);                // store in the first space of A
    //y = A[0] * A[0];

    scanf("%d", &B[3]); // &B[3] can be B + 3
    y = B[3] * B[3];
    printf("y = %d\n", y);

    printf("input = ");
    scanf("%s", C);
    strcat(C, " 1234");
    printf("C = %s\n", C); //when print string, need pointer
    return 0;
}