#include "stdio.h"

int main(int argc, char *argv[])
{
    // !�ܼ� & �B��
    /*
    * [����ܼƫ��A]
      char   1byte,  -128~127
      short  2bytes, -32768~32767
      int    4bytes,
      long   4bytes,
      ...,
      unsigned char,  0~255
      unsigned short, 0~65535
      ...,
    */
    printf("EX.1 ���\n");
    int i, k, Sum;
    printf("k=");
    scanf("%d", &k);

    Sum = 0;                 // Sum�M��
    for (i = 1; i <= k; i++) // for(start; stop; step)
    {
        Sum += i; // Sum = Sum + i
    }
    printf("i = %d\n", i);
    printf("1 + ... + %d = %d\n", k, Sum);
    return 0;
}
