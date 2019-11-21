#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char *argv[])
{
    printf("³¯Ãh¦w/0753736\n");
    FILE *Inl;
    char N[100][10];
    char S1[10];
    int S[100][10];
    int i, j, k;
    int m, n, o;
    double T[4], A[4], B[4];

    Inl = fopen("Book1.txt", "rb");
    if (Inl == 0)
    {
        printf("Book1 not found\n");
        return 0;
    }

    i = 0;
    while (!feof(Inl))
    {
        fscanf(Inl, "%s %d %d %d %d\n", &N[i][0], &S[i][0], &S[i][1], &S[i][2], &S[i][3]);
        S[i][4] = i; //(S[i][0] + S[i][1] + S[i][2] + S[i][3]);
        //S[i][5] = i;
        i++;
    }
    //====
    //====
    for (o = 0; o < 4; o++)
    {
        n = 35;
        for (i = 0; i < n; i++)
        {
            for (j = i + 1; j < n + 1; j++)
            {
                if (S[i][o] < S[j][o])
                {
                    m = S[i][o];
                    S[i][o] = S[j][o];
                    S[j][o] = m;
                }
            }
        }

        T[o] = 0;
        for (j = 0; j < 9; j++)
        {
            T[o] += S[j][o];
        }
        T[o] /= (double)9;

        A[o] = 0;
        for (j = 0; j < 36; j++)
        {
            A[o] += S[j][o];
        }
        A[o] /= (double)36;

        B[o] = 0;
        for (j = 27; j < 36; j++)
        {
            B[o] += S[j][o];
        }
        B[o] /= (double)9;
    }
    printf("%f %f %f %f\n", T[0], T[1], T[2], T[3]);
    printf("%f %f %f %f\n", A[0], A[1], A[2], A[3]);
    printf("%f %f %f %f\n", B[0], B[1], B[2], B[3]);

    return 0;
}