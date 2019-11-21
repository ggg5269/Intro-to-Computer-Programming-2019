#include "stdio.h"

int main(int argc, char *argv[])
{ /*
    * for loop summation calculating

    int k, x, y;
    printf("please input a number: ");
    scanf("%d", &x);
    y = 0; //for(y = 0, k = 0; k <= x; k++) will be fine
    for (k = 0; k <= x; k++)
    {
        y += 6 * k * k + 2 * k + 8;
    }
    printf("y(%d) = %d\n", x, y);
    return 0;

    * double for loop summation

    int k1, k2, x, y, temp;
    printf("please input a number for x: ");
    scanf("%d", &x);

    for (y = 0, k1 = 2; k1 <= 2 * x; k1++)
    {
        for (temp = 0, k2 = 1; k2 <= k1; k2++)
        {
            temp += 6 * k1 * k2 + k2;
        }
        y += k1 * temp;
    }
    printf("y(%d) = %d\n", x, y);
    */

    // 2^0 + 2^1 + 2^2 +...

    int total = 1,
        amount = 1, k;
    for (k = 1; k <= 100; k++)
    {
        amount = amount * 2;
        total += amount;
        //printf("%d\n", total);
        if (total > 1000000)
        {
            break;
        }
    }
    printf("it takes %d days.\n", k + 1);
}
