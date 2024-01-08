# [Estudos de C] Breves notas sobre 'Dispatch Tables'


Antes de nos adentrarmos na implementação de uma _Dispatch Tables_, primeiro vamos conhecer as funções que retornam ponteiros paras outras funções. 
Ou seja, diferentemente das funções tradicionais, nesta, não é retornado um dado, mas sim um ponteiro para outra função que será chamada no fluxo de execução da aplicação. 

# Funções que retornam ponteiros para outras funções

Inicialmente vamos revisar os conceitos de ponteiros para funções. 
Segundo Ananda Gunawardena, "_Functions like variables, can be associated with an address in the memory. We call
this a function pointer._"

Uma função normal tem o seguinte protótipo:

```
<tipo_de_retorno> <nome_da_função>(declaração_de_parâmetros) 
``` 
Por exemplo:

```c
int    sum(int a, int b);
```
Onde: 

`int`: é o tipo de dado que será retornado pela função;
`sum`: é o nome da função;
`(int, a, int b)`: são os argumentos da função. 

Sua utilização é simples, basta chamar a função passando os respectivos argumentos. 

Agora, um ponteiro para função poderá ser declarado da seguinte pseudo-forma:

```
<tipo_de_retorno> (*nome_do_ponteiro_para_a_função)(declaração_de_parâmetros) 
```  
Um exemplo pratico:

```c 
int     (*op)(int a, int b);
```

Acima, nos definimos um ponteiro para função cujo nome é `op`. O qual pode ser inicializado apontado para qualquer função que receba dois inteiros como parâmetros e devolve um inteiro como resposta.
Como se pode ver, por meio do ponteiro `op`, podemos assinalar para a função `sum` exemplificada acima.

Vemos, que difere da forma tradicional de declarar uma variável. Dessa forma, o nome da variável fica entre parênteses, seguido pela declaração dos parâmetros que a função apontada aceita.  

Vejamos um exemplo: 
```c
#include<stdio.h> 

int     sum(int a, int b) 
{
    return (a + b);
}

int     main(void)
{
    int     (*op)(int a, int b);
    
    op = sum;
    printf("2 + 2 = %d\n", op(2, 2));
    return (0);
}
```
No exemplo acima é declarada a variável `op` que receberá um ponteiro para uma função que aceita dois inteiros como argumento e devolve 
um inteiro. Em seguida, assinalamos para o endereço da função — veja que é simples: indicamos apenas o nome — e em seguida a 
chamamos.

Em resumo, essa é a forma simples de se iniciar na utilização de ponteiros para funções. 

Explicando um pouco mais: 

Declaração da função: `int sum(int, int);`
Declaração do ponteiro para a função: `int (fp)(int, int);`;
Inicializa o ponteiro da função apontando para o endereço da função desejada: `fp = sum;`;
Utiliza a função apontada: `ft(int, int);`;  

Uma outra forma, é definindo um tipo específico para essas variáveis, por meio da _keyword_ `typedef`. Assim, o código fica mais claro e 
conciso. 

```
typedef <tipo_de_retorno> (*nome_do_ponteiro_)(declaração_de_parâmetros);
```

Nesse sentido, agora podemos declarar a variável que receberá o ponteiro desta maneira:

```
<nome_do_ponteiro_> <nome_da_variável>;
```

Veja o exemplo abaixo, no qual definimos o tipo `fptr`:

```c
#include<stdio.h> 

typedef int (*fptr) (int, int); 

int     sum(int a, int b);

int     main(void)
{
    fptr    op;
    
    op = sum;
    printf("2 + 2 = %d\n", op(2, 2));
    return (0);
}

int     sum(int a, int b) 
{
    return (a + b);
}
```

### Casos de uso de ponteiros para funções

Um exemplo prático de uso de ponteiros para funções é na função `qsort`, presente na biblioteca `stdlib.h`. No qual dentre os seus argumentos, exige-se um ponteiro para a função de comparação. 

Vejamos:
```c 
#include <stdlib.h>

void qsort(void *base, size_t nmemb, size_t size,
    int (*compar)(const void *, const void *));
```

Feitas as revisões acima, vamos agora compreender um pouco mais sobre funções que devolve ponteiros para outras funções.

A forma comum de declarar uma função que devolve ponteiros para outras funções é da seguinte forma: 
 
```c
int     (*get_op_func(char))(int, int);
```

Explicando:

`int`: tipo de dado a ser retornado pelas funções apontadas, ou seja, será retornado um ponteiro para uma função que retorna dado do tipo inteiro;
`(*get_op_func(char op))`: Aqui, indica que temos uma função cujo nome é `*get_op_func`, com o operador indicando que retorna um ponteiro, e que ela recebe um `char` como argumento na sua chamada. 
`(int, int)`: esse último, indica que o ponteiro retornado apontará para uma função que tem como parâmetros dois inteiros. 

A variável de ponteiro que receberá o resultado é declarada da seguinte forma:

```c

int     (*op_func)(int a, int b);

```

E chamamos a função para acessar o ponteiro da função desejada desta maneira:

```c
op_func = get_op_func('+');
```
Agora temos na variável `op_func` o endereço apontado para uma função retornada pela chamada da função `get_op_func`, que nesse caso é uma função de soma. 

Vejamos um exemplo de um código completo: 

```C
#include <stdio.h>

int     (*get_op_func(char))(int, int);
int     sum(int, int);
int     min(int, int);

int     main(void)
{
    int     (*op_func)(int a, int b);

    op_func = get_op_func('+');
    printf("Result: 10 + 5 = %d\n", op_func(10, 5));
    op_func = get_op_func('-');
    printf("Result: 10 - 5 = %d\n", op_func(10, 5));
    return (0);
}

int     (*get_op_func(char op))(int n1, int n2)
{
    if (op == '+') 
        return (sum);
    if (op == '-') 
        return (min);
    return (NULL);
}

int     sum(int n1, int n2) { return (n1 + n2);}
int     min(int n1, int n2) { return (n1 - n2);}
```

Agora, como vimos linhas acima quando estávamos lidando com ponteiros para funções, podemos definir um tipo específico para as funções que serão retornadas. Vejamos o mesmo código com as alterações para o uso do tipo abstrato de dados. 

```c
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
```

Feitas essas revisões, vamos agora implementar uma _Dispatch Table_. 

# O que é uma "Dispatch Table" e como implementar

Segundo Alice Goldfuss, uma _dispatch table_, também conhecida como _jump table_ é um vetor de ponteiros para funções. 

Podemos dizer que uma _dispatch table_, é uma estrutura de dados que referencia funções ou métodos a um identificador específico. 

```
id_1 -> func_1
id_2 -> func_2
id_3 -> func_3
```

Você, caro leitor, pode encontrar material também a respeito pesquisando por: _function tables_, _dynamic dispatch_ e _jump table_.

Vamos começar a implementar uma versão simples de uma _dispatch table_ — apenas para fins didáticos. Para isso, vamos aproveitar o código utilizado para a explicação sobre ponteiros para funções e funções que retornam ponteiros para funções. 
A ele, vamos adicionar mais três funções auxiliares; são as seguintes:

```c
int     usage(void);
int     mul(int n1, int n2);
int     divide(int n1, int n2);

// {...}

int     usage(void)
{
    fprintf(stderr, "[ERRO] Usage: ./main <int> <op> <int> - To div operator use '//'\n");
    return (1);
}
int     mul(int n1, int n2) { return (n1 * n2);}
int     divide(int n1, int n2) { return (n1 / n2);}
```
 
Um vez que escrevemos as funções auxiliares, vamos agora implementar um tipo abstrato de dado do qual será composta a nossa _dispatch table_. 

```c 
typedef struct  operator
{
    char    opt;
    fptr    math_f;
}       Operator;
```

Aqui, é definido o tipo `Operator` que é uma estrutura composta por um `char` e ponteiro para função do tipo `fptr`: já definido no código. Para fins deste exemplo, `opt` é onde é armazenado o identificador, nesse caso: um operador aritmético e `math_f` será um ponteiro para a função aritmética respectiva.

Isso feito, é hora de alterar a função `get_op_func` para a implementação da nossa tabela. 

A primeira alteração é a substituição das estruturas condicionais por um vetor do tipo `Operator` e o inicializa com os respectivos identificadores e ponteiros para as funções concernentes.

```c
Operator    opts[4] = {
        {'+', sum}, 
        {'-', min}, 
        {'*', mul}, 
        {'/', divide}, 
    }; 
```

A lógica para a devolução do ponteiro da função desejada se dá mediante a atividade de interação sobre o vetor `opts`. A cada membro, é comparado com o argumento `op` informado na chamada da função. Caso encontre, retorna-se o ponteiro da função, caso contrário é retornado `NULL`.  

```c
    int         i;
    i = 0;
    while (i < 4)
    {
        if (op == opts[i].opt)
            return (opts[i].math_f);
        i++;
    }   
    return (NULL);
```

Vejamos agora o código completo: 

```c
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
    printf("[ERRO] Usage: ./main <int> <op> <int>");
    printf("\n\tTo div operator use '//'");
    printf("\n\tTo multiply operator use like form '*': 5 '*' 5\n");
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
```

# Referências
- https://www.prodevelopertutorial.com/advanced-c-pointer-programming-chapter-4-function-pointers/
- https://gist.github.com/jakelevi1996/5fddfe58c25d5edb5a1da5d414824c41
- https://linux.die.net/man/3/qsort
- https://www.cs.cmu.edu/~ab/15-123N09/lectures/Lecture%2008%20-%20Function%20Pointers.pdf 
- https://medium.com/@hatronix/function-pointers-in-c-unleashing-the-power-of-dynamic-dispatch-29672ffcf502
- https://en.wikipedia.org/wiki/Dispatch_table
- https://blog.alicegoldfuss.com/function-dispatch-tables/
- https://vandervoord.net/blog/2015/6/2/making-function-pointers-usable-in-c