HT: main.o tree_operations.o printing.o utils.o
	gcc main.o tree_operations.o printing.o utils.o -o HT -Wall -ansi -lm -W
main.o: main.c utils.h printing.h tree_operations.h
	gcc main.c -c -Wall -ansi -lm -W
tree_operations.o: tree_operations.c tree_operations.h printing.h
	gcc tree_operations.c -c -Wall -ansi -lm -W
printing.o: printing.c printing.h utils.h
	gcc printing.c -c -Wall -ansi -lm -W
utils.o: utils.c utils.h
	gcc utils.c -c -Wall -ansi -lm -W
