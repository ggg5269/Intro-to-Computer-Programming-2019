// 123.cpp : Defines the entry point for the console application.
//

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char *argv[])
{
    FILE *Inl;       // for file // * pointer
    char N[100][10]; // for name, at most 100 students, at most 10 bytes for name
    char S1[10];     // for name searching
    int S[100][10];  // S[i][0 - 3] for score; S[i][4] for sum of score; S[i][5] for ID; S[i][6] for rank
    int i, j, k, l;
    int m, n, o;

    Inl = fopen("Book1.txt", "rb"); // rb for which kind of file you are opening
    if (Inl == 0)
    {
        printf("Book1 not found\n");
        return 0;
    }

    i = 0;             // IMPORTANT!!
    while (!feof(Inl)) // if it's not the end of the file, keep reading //feof: file end of file
    {
        fscanf(Inl, "%s %d %d %d %d\n", &N[i][0], &S[i][0], &S[i][1], &S[i][2], &S[i][3]);
        S[i][4] = (S[i][0] + S[i][1] + S[i][2] + S[i][3]); // total score
        S[i][5] = i;                                       // store ID
        // fscanf: scan from file, doesn't care about how many spaces between two string
        i++;
    }
    printf("%d data imported\n", i);

    // * sort the data by total score

    n = i;                      // set n to 36
    for (i = 0; i < n - 1; i++) // find i_th place, i = 0-34
    {
        for (j = i + 1; j < n; j++)     // j = (i+1)-35
        {                               //
            if (S[i][4] < S[j][4])      // determine the direction
            {                           //
                for (k = 0; k < 6; k++) // for scores
                {
                    m = S[i][k];
                    S[i][k] = S[j][k];
                    S[j][k] = m;
                }
                // for names
                strcpy(S1, &N[i][0]);
                strcpy(&N[i][0], &N[j][0]);
                strcpy(&N[j][0], S1);
            }
        }
    }

    for (k = 0; k < n; k++)
    {
        S[k][6] = k + 1;
        printf("rank = %2d %s %3d %3d %3d %3d %3d %3d %3d\n", k + 1,
               &N[k][0], S[k][0], S[k][1], S[k][2], S[k][3], S[k][4], S[k][5], S[k][6]);
    }

    printf("%d\n", i);

    // * sort data by ID

    n = i + 1;
    for (i = 0; i < n - 1; i++) // find i_th place
    {
        for (j = i + 1; j < n; j++)
        {
            if (S[i][5] > S[j][5]) // determine the direction
            {
                for (k = 0; k < 7; k++)
                {
                    // for scores
                    m = S[i][k];
                    S[i][k] = S[j][k];
                    S[j][k] = m;
                }
                // for names
                strcpy(S1, &N[i][0]);
                strcpy(&N[i][0], &N[j][0]);
                strcpy(&N[j][0], S1);
            }
        }
    }
    for (k = 0; k < n; k++)
    {
        printf("ID = %2d %s %3d %3d %3d %3d %3d rank = %3d\n", S[k][5], &N[k][0], S[k][0], S[k][1], S[k][2], S[k][3], S[k][4], S[k][6]);
    }

    return 0;
}

/*
* Bubble Sorting Algorithm

#define N 5
int main(int argc, char *argv[]){
	int i, j, k, A[N] = {34, 12, 5, 66, 1};

	! bubble sorting desc
	for (i = 0; i < N-1; i++){        // find i_th place
		for (j = i+1; j < N; j++){    // ! "<"
			if (A[i] < A[j]){         // determine the direction
				k = A[i];
				A[i] = A[j];
				A[j] = k;
			}
		}
	}
	for (i=0;i<N;i++){
		printf("A[%d] = %3d\n", i, A[i]);
	}
	return 0;
}
*/
