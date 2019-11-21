#include <stdio.h>
#include <stdlib.h>
struct threeNum
{
    int n1, n2, n3;
};

int main()
{
    float fVar = 1.2;
    int iVar;

    iVar = fVar; // iVar = 1
    printf("%d\n", iVar);

    // ! save "float fVar" into the memory sapce of iVar
    // *get address -> typecasting -> get value
    iVar = *(int *)&fVar;
    // ? do it in another way
    // ? *(float*)&iVar = fVar;

    printf("%d\n", iVar);
    return 0;
}