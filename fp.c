#include <stdio.h>

typedef int (*fptr) (int, int); 

fptr    get_op_func(char);
int     sum(int, int);
int     min(int, int);

int     main(void)
{
    fptr     op_func;

    op_func = get_op_func('+');
    printf("Result: 10 + 5 = %d\n", op_func(10, 5));
    op_func = get_op_func('-');
    printf("Result: 10 - 5 = %d\n", op_func(10, 5));
    return (0);
}

fptr    get_op_func(char op)
{
    if (op == '+') 
        return (sum);
    if (op == '-') 
        return (min);
    return (NULL);
}

int     sum(int n1, int n2) { return (n1 + n2);}
int     min(int n1, int n2) { return (n1 - n2);}