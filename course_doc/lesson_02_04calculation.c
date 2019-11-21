#include "stdio.h"
#include "stdbool.h" // for boolean

int main(int argc, char *argv[])
{
    printf("EX.5 calculation \n");
    int i, j, k;
    i = 10;
    j = 2;
    k = i + j;
    printf("i + j = %d\n", k);
    k = i >> j;
    printf("i >> j = %d\n", k); // shift 2 digit, 10/(2^2)=2.5, output 2
    k = i << j;
    printf("i << j = %d\n", k); // shift 2 digit, 10*(2^2)=40, output 40
    k = i & j;
    printf("i & j = %d\n", k); // 1010 AND 0010, output 0010 = 2
    k = i | j;
    printf("i | j = %d\n", k); // 1010 OR 0010, output 1010 = 10
    k = i ^ j;
    printf("i ^ j = %d\n", k); // 1010 XOR 0010, output 1000 = 8
    printf("\n\n");

    int a, b, c;
    bool d;
    a = 10;
    b = 10;
    c = a + b;
    d = c > 15;
    if (d)
    {
        printf(">15\n");
    }
    else
    {
        printf("<15\n");
    }
    /* 
    !for logical operation
    * && and
    * || or
    * -- is
*/
    if ((a > 10) && (b > 10))
        printf("true\n"); // &&: and (for logical operation)
    else
        printf("false\n");

    if ((a == 10) || (b == 10) || (c == 20))
        printf("true\n"); // ==: equal; ||: or (for logical operation)
    else
        printf("false\n");
}
