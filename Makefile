CC = gcc
PROGRAM = my-prolog
O_FILES = $(PROGRAM).tab.o lex.yy.o $(PROGRAM).o
CLEAN_LIST = *.o lex.yy.c $(PROGRAM).tab.c $(PROGRAM).tab.h $(PROGRAM) *.gch
$(PROGRAM): $(O_FILES)
	$(CC) -o $@ $+ -lfl
lex.yy.o: lex.yy.c $(PROGRAM).tab.h
	$(CC) -c lex.yy.c
lex.yy.c: $(PROGRAM).l
	flex $+
$(PROGRAM).tab.o: $(PROGRAM).tab.c $(PROGRAM).tab.h my-prolog.h
	$(CC) -c $(PROGRAM).tab.c
$(PROGRAM).tab.c: $(PROGRAM).y
	bison -d $+
$(PROGRAM).o: my-prolog.c my-prolog.h
	$(CC) -std=c99 -c my-prolog.c
clean:
	rm -f $(CLEAN_LIST)

#implicit makefile rules erase my source code!!!
%.c: %.y
%.c: %.l
