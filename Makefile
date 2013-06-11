CC = gcc
PROGRAM = prolog
$(PROGRAM): $(PROGRAM).tab.o lex.yy.o
	$(CC) -o $(PROGRAM) $(PROGRAM).tab.o lex.yy.o -lfl
lex.yy.o: lex.yy.c
	$(CC) -c lex.yy.c
lex.yy.c:
	flex $(PROGRAM).l
$(PROGRAM).tab.o: $(PROGRAM).tab.c $(PROGRAM).tab.h
	$(CC) -c $(PROGRAM).tab.c $(PROGRAM).tab.h
$(PROGRAM).tab.c:
	bison -d $(PROGRAM).y
clean:
	rm -f *.o lex.yy.c $(PROGRAM).tab.c $(PROGRAM).tab.h $(PROGRAM) *.gch
