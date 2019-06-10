#----------------- Makefile do Filipera -----------------#
all: inf_to_pos
inf_to_pos:	main.o	inf_to_pos.o
	gcc -o prog main.o inf_to_pos.o

inf_to_pos.o:	inf_to_pos.c
	gcc -o inf_to_pos.o -c inf_to_pos.c -W -Wall -ansi -pedantic -ggdb3
main.o:	main.c	inf_to_pos.h
	gcc -o main.o -c main.c -W -Wall -ansi -pedantic -ggdb3	
clean:
	rm -rf *.o
	rm -rf inf_to_pos
exec:
	valgrind ./prog input.txt output.txt

# all:       nome das regras a serem executadas
#
# clean:     apaga arquivo intermediário
#
# TAB: 	     espaços devem ser feitos com TAB
#
# -Wall:     Ativa avisos não comuns, pode dar conselhos úteis.
#
# -pedantic: Ativa avisos de acordo com o padrao C
#
# -ansi:     Compila o programa de acordo com o padrão ANSI
#
# ggdb3:     Adiciona informações extras no debug
