#include "stdio.h"

int main(int argc, char *argv[])
{
    printf("EX.2 �p��\n");

    double a1, a2, a3, ave; // use double, when run out of digit
    printf("a1 =");
    scanf("%lf", &a1);
    printf("a2 =");
    scanf("%lf", &a2);
    printf("a3 =");
    scanf("%lf", &a3);

    ave = (a1 + a2 + a3) / 3;

    printf("average = %lf\n", ave); // * %a.bf �]�w��X�榡, �`���=a, �p�ƫ�b��
    return 0;
}
