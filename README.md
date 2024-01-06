# [Estudos de C] Breves notas sobre 'Dispatch Tables'


Antes de nos adentrarmos na implementação de uma _Dispatch Tables_, primeiro vamos conhecer as funções que retornam ponteiros paras outras funções. 
Ou seja, diferentemente das funções tradicionais, nesta, não é retornado um dado, mas sim um ponteiro para outra função que será chamada no fluxo de execução da aplicação. 

# Funções que retornam ponteiros para outras funções

Inicialmente vamos revisar os conceitos de ponteiros para funções. 

Uma função normal tem o seguinte protótipo:

```
<tipo de retorno> <nome da função>(declaração de parâmetros) 
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

Agora, vamos revisar os conceitos de ponteiros para funções. O seu uso se dá declarando um ponteiro para uma função com a seguinte forma:

```
<tipo de retorno> (*nome do ponteiro para a função)(declaração de parâmetros) 
```  
Vemos, que difere da forma tradicional de declarar uma variável, aqui o nome dela vai entre parênteses, seguido pela declaração de parâmetros que a função apontada aceita.  

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
No exemplo acima é declarado a variável `op` que receberá um ponteiro para uma função que aceita dois inteiros como argumento e devolve um inteiro. Em seguida, assinalamos para o endereço da função função — veja que é simples: indicamos apenas o nome — e em seguida a chamamos.

Uma outra forma, é definindo um tipo especifico para essas variáveis, assim, o código fica mais claro e conciso. Veja o exemplo abaixo, no qual definimos o tipo `fptr`:

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
Um exemplo prático de uso de ponteiros para funções é na função `qsort`, presente na biblioteca `stdlib.h`. No qual dentre os seus argumentos, exige-se um ponteiro para a função de comparação. 

Vejamos:
```c 
#include <stdlib.h>

void qsort(void *base, size_t nmemb, size_t size,
    int (*compar)(const void *, const void *));
```

Feitas as revisões acima, vamos agora compreender um pouco mais sobre funções que devolve ponteiros para outras funções.

A forma primitiva de declarar uma função que devolve ponteiros para outras funções é da seguinte forma: 
 
```c
int     (*get_op_func(char))(int, int);
```

Explicando:

`int`: tipo de dado a ser retornado pelas funções apontadas, ou seja, será retornado um ponteiro para um função que retorna dado do tipo inteiro;
`(*get_op_func(char op))`: Aqui, indica que temos uma função cujo nome é `*get_op_func`, como o operador indicando que retorna um ponteiro, e que ela recebe um `char` como argumento na sua chamada. 
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

Agora, como vimos linhas acima quando estávamos lidando com ponteiros para funções, podemos definir um tipo específico para as funções que serão retornadas. Vejamos o mesmo código com as alterações para o uso da tipagem. 

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

# O que é uma "Dispatch Tables"