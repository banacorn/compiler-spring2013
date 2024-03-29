TARGET = parser
OBJECT = parser.tab.c parser.tab.o lex.yy.c alloc.o functions.o symboltable.o
CC = gcc -g
LEX = flex
YACC = bison -v
YACCFLAG = -d
LIBS = -ll 

TEST = case/test.c

parser: parser.tab.o alloc.o functions.o symboltable.o
	$(CC) -o $(TARGET) parser.tab.o alloc.o functions.o symboltable.o $(LIBS)

parser.tab.o: parser.tab.c lex.yy.c alloc.o functions.c symboltable.c
	$(CC) -c parser.tab.c

lex.yy.c: lexer3.l
	$(LEX) lexer3.l

parser.tab.c: parser.y 
	$(YACC) $(YACCFLAG) parser.y

alloc.o: alloc.c
	$(CC) -c alloc.c
	
symboltable.o: symboltable.c
	$(CC) -c symboltable.c

functions.o: functions.c
	$(CC) -c functions.c

clean:
	rm -f $(TARGET) $(OBJECT) 

go:
	make
	./parser $(TEST)

