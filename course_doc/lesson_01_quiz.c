// EX1
#include <stdio.h>

int main()
{
    int i, j, x;
    printf("input how many rows of a you want: ");
    scanf("%d", &x); // & !
    for (i = 1; i <= x; i++)
    {
        for (j = 1; j <= i; j++)
        {
            printf("a");
        }
        printf("\n");
    }
}
/*
EX2
#include <stdio.h>

int main()
{
int i, j, x;
    printf("input x=5");
    scanf("%d", &x);   // & !
    for (i=1; i<=x; i++){
        for (j=1; j<=x-i; j++){
            printf(" ");
        }
        for (j=1; j<=i; j++){
            printf("*");
        }
        printf("\n");
    }
}

EX3
#include <stdio.h>

int main()
{
int i, j, x;
    printf("input x=5");
    scanf("%d", &x);   // & !
    for (i=1; i<=x; i++){
        for (j=1; j<=x-i; j++){
            printf(" ");
        }
        for (j=1; j<=i; j++){
            printf("*");
        }
        for (j=1; j<i; j++){
            printf("*");
        }
        for (j=1; j<=x-i; j++){
            printf(" ");
        }
        printf("\n");
    }
}

EX4
#include <stdio.h>

int main()
{
int i, j, x;
    printf("input x=5");
    scanf("%d", &x);   // & !
    for (i=1; i<=x; i++){
        for (j=1; j<=x-i; j++) printf(" ");
        for (j=1; j<=i; j++) printf("%d",x-i+j);
        for (j=1; j<=i-1; j++) printf("%d",x-j);
        printf("\n");
    }
}
*/
