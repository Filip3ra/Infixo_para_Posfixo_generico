#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>  /* isdigt e isalpha */
#include "inf_to_pos.h"

/** FUNÇÕES PILHA **/

TStack *build_stack(int t)
{
	TStack *aux = (TStack*)malloc(sizeof(TStack));
	aux->top = -1;
	aux->S = (void**)malloc(sizeof(void*) * t);
	aux->size = t;

	return aux;
}

int stack_empty(TStack *s)
{
	if(s->top >= 0)
		return 0;
	return 1;
}

void push(TStack *s, void *elem)
{
	if(s->top != s->size-1)
	{
		s->top++;
		s->S[s->top] = elem;
	}
	else
		printf("Stack full!\n");
}

void *pop(TStack *s)
{
	void *aux;

	if(!stack_empty(s))
	{
		aux = s->S[s->top];
		s->top--;

		return aux;
	}
	else
	{
		printf("Stack empty!\n");

		return NULL;
	}
}

void free_stack(TStack *s, void (*free_elem)())
{
	void *aux;

	while(!stack_empty(s))
	{
		aux = pop(s);
		free_elem(aux);
	}

	free(s->S);
	free(s);
}





/** FUNÇÕES FILA **/

TQueue *build_queue(int size)
{
	TQueue *aux = (TQueue*)malloc(sizeof(TQueue ));
    aux->Q = (void**)malloc(sizeof(void*) * size);
    aux->size = size;
	aux->head = -1;
	aux->tail = -1;

	return aux;
}

int queue_empty(TQueue *q)
{
	if(q->head == -1)
		return 1;
	return 0;
}

void enqueue(TQueue *q, void *elem)
{
    if(queue_empty(q))
    {
        q->head++;
        q->tail++;
        q->Q[q->head] = elem;
    }
    else if(!(q->tail == q->size - 1))
    {
        q->tail++;
        q->Q[q->tail] = elem;
    }
    else
        printf("Queue full!\n");
}

void *dequeue(TQueue *q)
{
    void *aux;

    if(!queue_empty(q))
    {
        aux = q->Q[q->head];
        q->head++;

        if(q->head > q->tail)
        {
            q->head = -1;
            q->tail = -1;
        }
        return aux;
    }
    else
    {
        printf("Queue empty!\n");

        return NULL;
    }

}

void free_queue(TQueue *q, void (*free_elem)())
{
    while(!queue_empty(q))
    {
        free_elem(dequeue(q));
    }

    free(q->Q);
    free(q);
}





/** FUNÇÕES CONVERSÃO INFIXA PARA POSFIXA **/

int verifica_caracter(char *c)
{
    switch(*c)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
            return 1;
        case '(':
            return 2;
        case ')':
            return 3;
    }
    return 0;
}

int prioridade_operador(char *c)
{
    switch(*c)
    {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
    }
    return 0;
}

int verifica_operandos(char *c)
{
    /* o caractere '.' é para tratar números reais
    *  isdigit verifica se é um número.
    *  isalpha verifica se é uma letra.     */
    if(isdigit(*c) || isalpha(*c) || *c == '.')
        return 1;
    return 0;
}

/* basicamente um typecasting
*  para acessar o conteúdo do void* */
char void_to_char(char *c)
{
    return *c;
}

void infix_to_posfix(TQueue *q, TStack *s, FILE *file_output)
{
    void *aux;
    void *c;
    char cha;

    c = q->Q[q->head];

    while(q->head != q->tail) /* lê expressão até o final */
    {

        if(verifica_caracter(c) == 2) /* se é parentese inicial ( */
        {
            push(s,c);
        }
        else if(verifica_operandos(c)) /* se é numero ou letra */
        {
            cha = void_to_char(c);
            fputc(cha, file_output);
        }
        else if(verifica_caracter(c) == 1) /* se é operador + - * / ou ^ */
        {
            /* verifica se temos dois operadores e suas prioridades.
             * se o operador do topo da pilha tiver maior precedência, vai pra nova expressão */
            aux = pop(s);
            while(verifica_caracter(aux) == 1 && prioridade_operador(aux) >= prioridade_operador(c))
            {
                cha = void_to_char(aux);
                fputc(cha, file_output);
                aux = pop(s);
            }
                push(s,aux); /* empilha o de menor precedência */

            push(s,c);  /* caso contrário, empilha o operador encontrado */

        }
        else if(verifica_caracter(c) == 3) /* se é parentese final ) */
        {
            aux = pop(s);
            while(verifica_caracter(aux) != 2) /* se é parentese inicial ( */
            {
                cha = void_to_char(aux);
                fputc(cha, file_output);
                aux = pop(s);
            }
        }

        q->head = q->head + 1;
        c = q->Q[q->head];

    }
    q->head = 0;
    fputc('\n', file_output); /* organiza expressões na saída */
}


