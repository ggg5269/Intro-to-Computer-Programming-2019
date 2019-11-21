#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

int main(int argc, char *argv[])
{
    char S1[100];
    int A, B, C, i, j, k;

    while (1)
    {
        // input func.
        printf(">");
        scanf("%s", S1);
        /* // * use `sscanf` to scan the string format
        if ((i = sscanf(S1, "%d+%d", &A, &B)) == 2) // '==2' means two numbers are validated
            j = A + B;
        else if ((i = sscanf(S1, "%d-%d", &A, &B)) == 2)
            j = A - B;
        else if ((i = sscanf(S1, "%d*%d", &A, &B)) == 2)
            j = A * B;
        else if ((i = sscanf(S1, "%d/%d", &A, &B)) == 2)
            j = A / B;
        if (i == 2)
            printf(": %d\n", j);
        */

        // find strlen "i"
        for (i = 0; i < sizeof(S1); i++)
            if (S1[i] == 0) // the 0 here is ASCII code 0
                break;
        // find the location of '+ - * /' "k"
        for (k = 0; k < i; k++)
            if ((S1[k] == '+') || (S1[k] == '-') || (S1[k] == '*') || (S1[k] == '/'))
                break;
        // extract A, B
        A = 0;
        B = 0;
        // set to double and add 0.5, prevent from floating point issue
        for (j = 0; j < k; j++)
            A += (int)(((double)S1[j] - '0') * pow(10, k - j - 1) + 0.5);
        for (j = k + 1; j < i; j++)
            B += (int)(((double)S1[j] - '0') * pow(10, i - j - 1) + 0.5);

        if (S1[k] == '+')
            C = A + B;
        else if (S1[k] == '-')
            C = A - B;
        else if (S1[k] == '*')
            C = A * B;
        else if (S1[k] == '/')
            C = A / B;
        printf("A= %d, B= %d, ans = %d, i = %d k = %d\n", A, B, C, i, k);
    }
}
