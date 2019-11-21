#include <stdio.h>

int main()
{
    int i, j, x;
    printf("please input a number: "); //
    scanf("%d", &x);                   //! "&" is important, scanf will store string into the position
    for (i = 1; i <= x; i++)
    {
        for (j = 1; j <= x - i; j++)
        {
            printf(" ");
        }
        for (j = 1; j <= i; j++)
        {
            printf("%d", x - i + j);
        }
        for (j = 1; j < i; j++)
        {
            printf("%d", x - j);
        }
        printf("\n");
    }
    return 0;
}
