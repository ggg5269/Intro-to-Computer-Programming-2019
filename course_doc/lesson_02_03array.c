#include "stdio.h"

int main(int argc, char *argv[])
{
    printf("EX.4 array, input, calculate\n");

    int i, k;
    float s[100], ave; // s[100] has 100 usable spaces

    printf("students = ");
    scanf("%d", &k);
    ave = 0;
    for (i = 0; i < k; i++)
    {
        printf("S[%d]", i + 1); // i + 1
        scanf("%f", &s[i]);
        ave += s[i];
    }
    printf("average = %.2f \n", ave / (float)k);
}
