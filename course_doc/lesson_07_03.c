#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct box
{
    float height;
    float length;
    float width;
    float vol;
} box;

int main()
{
    box a, b, *c;
    double w;

    a.height = 8;
    a.length = 7;
    a.width = 5;
    printf("a box height= %f\n", a.height);

    printf("input box height, length, weight:\n");
    scanf("%f %f %f", &b.height, &b.length, &b.width);
    /*
    b.height = 10;
    b.length = 5;
    b.width = 9;
    */
    b.vol = b.height * b.length * b.width;
    printf("box's volume = %5.2f\n", b.vol);

    c = &a;
    w = c->height;
    printf("%.2f\n", w);
}