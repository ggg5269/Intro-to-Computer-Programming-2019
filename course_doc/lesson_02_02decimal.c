#include "stdio.h"

int main(int argc, char *argv[])
{
    printf("EX.2 小數\n");

    double a1, a2, a3, ave; // use double, when run out of digit
    printf("a1 =");
    scanf("%lf", &a1);
    printf("a2 =");
    scanf("%lf", &a2);
    printf("a3 =");
    scanf("%lf", &a3);

    ave = (a1 + a2 + a3) / 3;

    printf("average = %lf\n", ave); // * %a.bf 設定輸出格式, 總位數=a, 小數後b位
    return 0;
}
