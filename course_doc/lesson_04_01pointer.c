#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char *argv[])
{
    /*
? variable + "&" >>> the location of variable
* ex. int A, &A means the loc

? pointer + "*" >>> the variable in such location
* ex. int *A, A means the loc
*/
    //  EX.1

    int A, B, C;    // variable
    int *D, *E, *F; // D, E, F are pointers

    printf("D = %lx E = %lx F = %lx\n", D, E, F); // print out the current location

    A = 10;
    B = 20;
    C = 30;
    //D = (int *) malloc(1*sizeof(int));
    D = &A; // point to memory of variable A

    E = (int *)malloc(1 * sizeof(int));
    F = (int *)malloc(1 * sizeof(int)); // * allocate memory

    *D = 40;
    *E = A;
    *F = *E + B + C;

    printf("A = %d B = %d C = %d\n", A, B, C);
    printf("*D = %d *E = %d *F = %d\n", *D, *E, *F);

    return 0;
}