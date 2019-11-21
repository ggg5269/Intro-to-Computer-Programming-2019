// ! standard deviation & mean

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h" // for sqrt, sin, cos, ...

#define MAX 100

int main(int argc, char *argv[])
{
    FILE *Inl;         // for file // * pointer
    char N[MAX][10];   // for name, at most 100 students, at most 10 bytes for name
    int S[MAX][6];     // for score
    int i, j, k;       //
    double M[4], D[4]; // mean and std.
    FILE *filePointer;

    Inl = fopen("Book1.txt", "rb"); // rb for which kind of file you are opening
    if (Inl == 0)                   // or '== NULL'
    {
        printf("Book1 not found\n");
        return 0;
    }

    // ? read the data
    i = 0;             // reset i
    while (!feof(Inl)) // feof: file end of file
    {                  // if it's not the end of the file, keep reading
        fscanf(Inl, "%s %d %d %d %d\n", &N[i][0], &S[i][0], &S[i][1], &S[i][2], &S[i][3]);
        S[i][4] = (S[i][0] + S[i][1] + S[i][2] + S[i][3]); // * total score

        // ! fscanf: scan from file, doesn't care about how many spaces between two string
        i++;
    }
    fclose(Inl);
    printf("%d data imported\n", i);

    // ? calculate mean & std.
    // \sigma = sqrt(E(X^2) - \mu^2)

    filePointer = fopen("scoresum.txt", "w"); // ! open file

    for (k = 0; k < 4; k++) // for subjects
    {
        M[k] = D[k] = 0;
        for (j = 0; j < i; j++) // for every students
        {
            M[k] += (double)S[j][k];         // ! integer to double
            D[k] += pow((double)S[j][k], 2); // E(X^2)
        }
        M[k] /= (double)i;
        D[k] /= (double)i;
        D[k] -= pow(M[k], 2);
        D[k] = sqrt(D[k]);
        printf("subject %d mean = %f, std. = %f\n", k + 1, M[k], D[k]);
        fprintf(filePointer, "subject %d mean = %f, std. = %f\n", k + 1, M[k], D[k]);
        // ! print to file
    }

    fclose(filePointer);

    /*
    ! calculate std.
    ! somehow we can combind this process to the dor loop above

    for (k = 0; k < 4; k++) // for subjects
    {
        D[k] = 0;
        for (j = 0; j < i; j++) // for every students
        {
            D[k] += pow((double)S[j][k] - M[k], 2); // ! integer to double
        }
        D[k] /= (double)i;
        D[k] = sqrt(D[k]);
        printf("subject %d Mean = %f\n", k + 1, D[k]);
    }
*/
    return 0;
}