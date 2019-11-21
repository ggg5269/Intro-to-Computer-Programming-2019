#include "stdio.h"
#include "stdbool.h" // for boolean

int a = 20, b = 20, c = 30; //global variable
int main(int argc, char *argv[])
{
    printf("EX.6 local & global \n"); //
    int a, b, c;                      // * local variable, 暫態
    a = 10;
    b = 10;
    c = a + b;
    printf("%d, %d, %d\n", a, b, c);
}
