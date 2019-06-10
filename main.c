/*  Este programa converte uma expressão em notação infixa para posfixa (polonesa reversa).
*   O algoritmo trabalha utilizando a leitura de um arquivo "input.txt" com as expressçoes,
*   e como saída é gerado um outro arquivo "output.txt" com as respectivas expressões convertidas.
*
*   Foi utilizado uma fila e uma pilha, onde o primeiro armazena a expressão infixa  e o segundo
*   armazena os caracteres no momento da conversão. A expressão convertida será escrita no arquivo output.txt.
*   Os argumentos para execução são enviados no terminal em sua chamada: ./prog intput.txt output.txt
*
*   Na descrição do trabalho ficou definido que:
*   > O tamanho máximo para expressões será de 256 caracteres, portanto, os vetores de tamanho fixos foram
*     alocados com uma folga de segurança, ficando com 300 posições.
*
*   > As expressões de entrada estão todas corretas, logo, não houve tratamento de caso de erro com
*     uma expressão inválida. Entretanto, foi feito tratamente de erro na abertura do arquivo por segurança.
*
*   Filipi Maciel Rodrigues Jardim - AED's II - IFNMG CCOMP - 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include "inf_to_pos.h"

void free_elem(void *elem)
{
    free(elem);
}

int main(int argc, char *argv[])
{

	FILE *file_input;
	FILE *file_output;
	TStack *s;  /* armazena os caracteres na conversão */
	TQueue *q;  /* armazena a expressão                */
	char *c;    /* recebe caractere por caractere      */
	int   i;    /* percorre vetor com expressão infixa */

	char infix[300]; /* armazena a expressão infixa */
	argc = argc;     /* isso é só pelo warning      */

	file_input  = fopen(argv[1],"r");
	file_output = fopen(argv[2],"w");

    /* Se arquivo foi aberto com sucesso */
    if(file_input)
    {
        /* lê uma linha do arquivo e guarda expressão em "infix" */
        while(fgets(infix, sizeof(infix), file_input))
        {
            s = build_stack(300);
            q = build_queue(300);
            i = 0;

            /* enquanto não chegar ao final da linha
             * vou alocar cada caractere e enfileirar */
            while(infix[i] != '\0')
            {
                 c = (char*)malloc(sizeof(char));
                *c = infix[i];
                 enqueue(q,c);
                i++;
            }

            infix_to_posfix(q, s, file_output);

            free_queue(q, &free_elem);
            free_stack(s, &free_elem);

        }

        fclose(file_input);
        fclose(file_output);
    }
    else
    {
        printf("Error trying to open the file\n");
    }

	return 0;
}
