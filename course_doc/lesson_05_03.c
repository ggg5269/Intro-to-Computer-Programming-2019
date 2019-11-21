#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include <stdbool.h>

#define N 50
#define OP 5

char op[OP] = {
    '(',
    '+',
    '-',
    '*',
    '/',
};
int op_priority[OP] = {0, 1, 1, 2, 2}; //set op's priority

int priority(char c);
void to_postfix(char infix[], char postfix[]);

char stack[N]; // This is a global variable.
int top = -1;
// -------------------------
// put data into stack
// -------------------------

void push(char item)
{
    if (top >= N - 1)
    {
        printf("Stack full!\n");
        exit(-1);
    }
    stack[++top] = item;
}
// ------------------------------------
// return the element in the top of stack
// ------------------------------------
int pop()
{
    if (top == -1)
    {
        printf("Stack empty!\n");
        exit(-1);
    }
    return stack[top--];
}

void stackPrint()
{
    int i;
    printf("stack =");
    for (i = 0; i <= top; i++)
        printf(" %c", stack[i]);
    printf("\n");
}

// ----------------------
// is empty?
// ----------------------
bool IsEmpty(void)
{
    return (top < 0) ? true : false;
}

// ----------------------
//  stack is full?
// ----------------------
bool IsFull()
{
    return (top >= N - 1) ? true : false;
}

// --------------------------
// send stack
// --------------------------
char top_data()
{
    return stack[top];
}

// ---------------------------
// set priority
// ---------------------------
int priority(char c)
{
    int i;

    for (i = 0; i < OP; i++)
        if (op[i] == c)
            return op_priority[i];
    return -1;
}

void to_postfix(char infix[], char postfix[])
{
    int i = 0, j = -1;
    char x, y;

    while ((x = infix[i++]) != '\0')
    {
        switch (x)
        {
        case '(':
            push(x);
            break;
        case ')':
            while (!IsEmpty() && (x = pop()) != '(')
                postfix[++j] = x;
            break;
        case '+':
        case '-':
        case '*':
        case '/':
            y = top_data();
            while (priority(y) >= priority(x))
            {
                postfix[++j] = pop();
                y = top_data();
            }
            push(x);
            break;
        default:
            postfix[++j] = x;
        }
    }
    while (!IsEmpty())
        postfix[++j] = pop();
    postfix[++j] = '\0';
}
bool IsDight(char c)
{
    return c >= '0' && c <= '9';
}
int calculate(char postfix[])
{
    int point = 0;
    while (postfix[point] != '\0')
    {
        while (IsDight(postfix[point]))
            push(postfix[point++]);
        int a = pop() - '0', b = pop() - '0', c = 0;
        switch (postfix[point])
        {
        case '+':
            c = b + a;
            break;
        case '-':
            c = b - a;
            break;
        case '*':
            c = b * a;
            break;
        case '/':
            c = b / a;
            break;
        }
        push(c + '0');
        point++;
    }
    return pop() - '0';
}

int main(void)
{
    char infix[50], postfix[50];

    printf("input function: ");
    scanf("%s", infix);
    to_postfix(infix, postfix);
    printf("\n\ninfix: %s \tprefix: %s\n", infix, postfix);
    printf("ans: %d\n", calculate(postfix));
    return 0;
}