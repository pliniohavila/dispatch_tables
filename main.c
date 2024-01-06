#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*fptr) (int, int); 
typedef struct  operator
{
    char    opt;
    fptr    math_f;
}       Operator;

int     usage(void);
fptr    get_op_func(char op);
int     sum(int n1, int n2);
int     min(int n1, int n2);
int     mul(int n1, int n2);
int     divide(int n1, int n2);

int     main(int argc, char **argv)
{
    int     n1;
    int     n2;
    char    op;
    fptr    op_func;

    if (argc < 4)
        return usage();
    n1 = atoi(argv[1]);
    n2 = atoi(argv[3]);
    op = argv[2][0];
    printf("[INFO] Input: %d %c %d\n", n1, op, n2);
    op_func = get_op_func(op);
    if (op_func == NULL)
    {
        fprintf(stderr, "Operator %c not available\n", op);
        return (1);
    }
    printf("[INFO] Result: %d\n", op_func(n1, n2));

    return (0);
}

int     usage(void)
{
    fprintf(stderr, "[ERRO] Usage: ./main <int> <op> <int> - To div operator use '//'\n");
    return (1);
}

fptr    get_op_func(char op)
{
    int         i;
    Operator    opts[4] = {
        {'+', sum}, 
        {'-', min}, 
        {'*', mul}, 
        {'/', divide}, 
    }; 

    i = 0;
    while (i < 4)
    {
        if (op == opts[i].opt)
            return (opts[i].math_f);
        i++;
    }   
    return (NULL);
}

int     sum(int n1, int n2) { return (n1 + n2);}
int     min(int n1, int n2) { return (n1 - n2);}
int     mul(int n1, int n2) { return (n1 * n2);}
int     divide(int n1, int n2) { return (n1 / n2);}