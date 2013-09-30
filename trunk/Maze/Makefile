EXENAME = maze

COMPILER = g++
WARNINGS = -Wchar-subscripts -Wparentheses -Wreturn-type -Wmissing-braces -Wundef -Wshadow
COMPILER_OPTS = -c -g -O0 -Wfatal-errors -Werror $(WARNINGS)
LINKER = g++

MAIN_OBJS = main.o search.o tree.o io.o

CODE_CLN = *.o $(EXENAME)

all: $(EXENAME)

$(EXENAME) : main.o
	$(LINKER) $(MAIN_OBJS) -lpng -o $(EXENAME)

main.o : search.o tree.o io.o main.cpp
	$(COMPILER) $(COMPILER_OPTS) main.cpp

search.o : tree.o io.o search.h search.cpp
	$(COMPILER) $(COMPILER_OPTS) search.cpp

tree.o : io.o tree.h tree.cpp
	$(COMPILER) $(COMPILER_OPTS) tree.cpp

io.o : io.h io.cpp
	$(COMPILER) $(COMPILER_OPTS) io.cpp

clean:
	-rm -f $(CODE_CLN)
