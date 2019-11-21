#include <stdio.h>
#include <stdlib.h>

double Eval2(char *expr, char **end)
{
    double Eval0(char *, char **);
    double res = 0;
    if (*(*end = expr) == '(')
    {
        res = Eval0(*end + 1, end);
        if (**end == ')')
            ++*end;
    }
    else
    {
        res = strtod(*end, end);
    }
    return res;
}

double Eval1(char *expr, char **end)
{
    double res = Eval2(expr, end);
    while (**end == '*' || **end == '/')
        (**end == '*') ? (res *= Eval2(*end + 1, end)) : (res /= Eval2(*end + 1, end));
    return res;
}

double Eval0(char *expr, char **end)
{
    double res = Eval1(expr, end);
    while (**end == '+' || **end == '-')
        res += (**end == '+') ? Eval1(*end + 1, end) : -Eval1(*end + 1, end);
    return res;
}

int main()
{
    char expr[128] = {0}, *pos = 0;
    printf("Exp : ");
    scanf("%s", expr);
    printf("Ans : %f\n", Eval0(expr, &pos));
}