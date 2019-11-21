#include "stdio.h"
#include "string.h" // for string

int main(int argc, char *argv[])
{
    // char: -128~127
    // unsigned char: 0~255

    char A;
    unsigned char B;
    char S1[2000], S2[2000];
    int i;
    // integer processing
    A = 200;
    B = 200;
    printf("A = %d, B = %d\n", A, B); // A = -56, B = 200

    // string processing
    strcpy(S1, "Hello"); // == note that "Hello" only 5 bytes, somehow copy into S1 will be 6 bytes, which include a "end"
    //S1[5] = 1;
    strcat(S1, "12345"); // += add "_s" after strcpy and strcat(in vc 6.0), make sure the program won't crash
    printf("%s\n", S1);

    sprintf(S2, "Date: %d-%d-%d", 108, 9, 26); // ! print a formatted string into S2
    printf("%s\n", S2);

    strcpy(S1, "0123456789");
    printf("S1=%s\n", S1);

    for (i = 0; i < strlen(S1); i++)
    {
        printf("S[%d] = %c, %d\n", i, S1[i], S1[i]);
        // ! %c print the character, %d print original number in ascii
    }

    S1[5] = '0';
    printf("S1=%s\n", S1);

    S1[5] = 0;             // the "0" is not equal to the "0" in above, the "0" here is ascii code 0
    printf("S1=%s\n", S1); // ! meet the "0" we set, so stop printing there

    for (i = 0; i < 10; i++)
    { // * force it keep printing even after meeting ascii(0) in the fifth position
        printf("S[%d] = %c, %d\n", i, S1[i], S1[i]);
    }
    return 0;
}
