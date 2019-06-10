# infixo_para_posfixo_generico
Conversão de expressões infixas para posfixas (Polonesa Reversa) com pilha e fila genéricas

Este programa converte uma expressão em notação infixa para posfixa (polonesa reversa).
O algoritmo trabalha utilizando a leitura de um arquivo "input.txt" com as expressçoes,
e como saída é gerado um outro arquivo "output.txt" com as respectivas expressões convertidas.

Foi utilizado uma fila e uma pilha, onde o primeiro armazena a expressão infixa  e o segundo
armazena os caracteres no momento da conversão. A expressão convertida será escrita no arquivo output.txt.
Os argumentos para execução são enviados no terminal em sua chamada: ./prog intput.txt output.txt

Na descrição do trabalho ficou definido que:
> O tamanho máximo para expressões será de 256 caracteres, portanto, os vetores de tamanho fixos foram
alocados com uma folga de segurança, ficando com 300 posições.

> As expressões de entrada estão todas corretas, logo, não houve tratamento de caso de erro com
uma expressão inválida. Entretanto, foi feito tratamente de erro na abertura do arquivo por segurança.

Filipi Maciel Rodrigues Jardim - AED's II - IFNMG CCOMP - 2019
