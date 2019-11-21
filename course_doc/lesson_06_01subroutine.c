#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

// * subroutine
void Swap(int a, int b)
{
    int c;
    c = a;
    a = b;
    b = c;
}

// * subroutine
void Swap2(int *a, int *b) // ! 'void' return nothing
{
    int c;
    c = *a;
    *a = *b;
    *b = c;
}

// * function
int Add(int a, int b) // ! return a 'int' variable
{
    return (a + b);
}

float Mul(float a, float b)
{
    float c;
    c = a * b;
    return c;
}

int main(int argc, char *argv[])
{
    int a = 10, b = 20, c;
    float a1 = 1.2, b1 = 1.3, c1;
    printf("before Swap: a = %d, b = %d\n", a, b);

    Swap(a, b);
    printf("after Swap: a = %d, b = %d,\n", a, b);

    Swap2(&a, &b);
    printf("after Swap2: a = %d, b = %d,\n", a, b);

    c = Add(a, b);
    printf("a = %d, b = %d, c = %d\n", a, b, c);

    c1 = Mul(a1, b1);
    printf("a1 = %f, b1 = %f, c1 = %f\n", a1, b1, c1);
    return 0;
}
