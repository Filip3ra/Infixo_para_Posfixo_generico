#ifndef INF_TO_POS_H
#define INF_TO_POS_H

/* PILHA */

typedef struct stack TStack;
struct stack
{
	int size;
	int top;
	void **S;
};

TStack *build_stack(int t);
void push (TStack *s, void *elem);
void *pop (TStack *s);
void free_stack (TStack *s, void (*free_elem)());
int  stack_empty(TStack *s);




/* FILA */

typedef struct queue TQueue;
struct queue
{
    int size;
	int head;
	int tail;
    void **Q;
};

TQueue * build_queue(int size);
int  queue_empty(TQueue *q);
int  full_queue (TQueue *q);
void *dequeue   (TQueue *q);
void enqueue    (TQueue *q, void* elem);
void free_queue (TQueue *q, void (*free_elem)());




/* CONVERSÃO INFIXO PARA POSFIXO */

void infix_to_posfix(TQueue *q, TStack *s, FILE *file_output );
char void_to_char(char *c);
int  prioridade_operador(char *c);
int  verifica_caracter  (char *c);
int  verifica_operandos (char *c);

#endif
