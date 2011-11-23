GCC = gcc -Wall
OBJ = $(GCC) -c

good_shell: main.c prompt.o readline.o parser.o execute.o redirect.o
	$(GCC) -o good_shell main.c prompt.o readline.o parser.o execute.o redirect.o

prompt.o: prompt.c prompt.h
	$(OBJ) prompt.c

readline.o: readline.c readline.h
	$(OBJ) readline.c

parser.o: parser.c parser.h
	$(OBJ) parser.c

execute.o: execute.c execute.h parser.h prompt.h redirect.h
	$(OBJ) execute.c

redirect.o: redirect.c redirect.h
	$(OBJ) redirect.c

clean:
	rm *.o
