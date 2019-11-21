#include "stdlib.h"
#include "stdio.h"

//! define 用法
#define A (3 + 2)
#define B 10
#define LBE(x) (((x & 0xFF) << 8) + ((x >> 8) & 0xFF))
#define WIN
#define LINUX

// ! #include  用法
#include "file1.h" // * include my own header
#include <math.h>

//! 網路使用
#include "winsock2.h"
#pragma comment(lib, "ws2_32.lib")

/*
! 錄放音使用
#include "mmysystem.h"
#pragma comment(lib, "winmm.lib")
*/

int main(int argc, char *argv[])
{
    int S[B][2], *N, *M;
    int i, j, k;

    printf("   A=%d\n", A);
    printf(" 2*A=%d\n", 2 * A);
    printf(" 3*A=%d\n", 3 * A);

    N = (int *)malloc(B * 2 * sizeof(int));
    S[5][1] = 100;
    N[11] = 100;
    M = (int *)S;                                  // * M point to the same memory as S[B][2]
    printf(" %d %d  %d\n", S[5][1], N[11], M[11]); // * M[11] == S[5][1]

    for (i = 0; i < 10; i++)
    {
        printf("i = %d LEB = %d\n", i, LBE(i));
    }
    printf("LBE(100) = %d\n", LBE(100));

    i = 10, j = 20, k = 30;

#ifdef WIN
    printf("i=%d\n", i);
#endif
#ifdef LINUX
    printf("i=%d\n", LBE(i));
#endif

    int a = 10, b = 20;
    double c = 30; // 角度0-360

    c -= 360;
    printf("Sub(%d, %d)=%d\n", a, a, Sub(a, b));
    printf("sin1(%f)=%f\n", c, sin1(c));
    printf("cos1(%f)=%f\n", c, cos1(c));
    c = c * 3.14159 / 180;
    printf("sin(%f)=%f\n", c, sin(c));
    printf("cos(%f)=%f\n", c, cos(c));
    return 0;
}