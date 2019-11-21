#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char *argv[])
{
    int A[3][4] = {{3, 2, 1, 4},
                   {6, 5, 3, 9},
                   {5, 6, 0, 4}};
    int *B, C;

    B = &A[1][3];       // ! *B = 9
    C = B[3] + A[2][2]; // ! B[3] = 3 spaces after 9, which is 0
    printf("*B = %d C = %d\n", *B, C);

    B = (int *)A + 2; // *B = 1
    //printf("*B = %d B[3] = %d\n", *B++, B[3]);
    printf("*B = %d B[3] = %d \n", *B, B[3]);

    C = (*B++) + A[2][2] + B[3]; // C = (*++B) + A[2][2] + B[3]; <- skip first
    //    1         0       5    //      4         0       3
    printf("*B = %d C = %d \n", *B, C);

    return 0;
}
