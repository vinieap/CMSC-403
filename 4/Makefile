OBJS	= Analyzer.o Givens.o Parser.o Tokenizer.o
SOURCE	= Analyzer.c Givens.c Parser.c Tokenizer.c
HEADER	= Analyzer.h Givens.h Parser.h Tokenizer.h
OUT	= compiler.out
CC	 = gcc
FLAGS	 = -g -c
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Analyzer.o: Analyzer.c
	$(CC) $(FLAGS) Analyzer.c -std=c99

Givens.o: Givens.c
	$(CC) $(FLAGS) Givens.c -std=c99

Parser.o: Parser.c
	$(CC) $(FLAGS) Parser.c -std=c99

Tokenizer.o: Tokenizer.c
	$(CC) $(FLAGS) Tokenizer.c -std=c99


clean:
	rm -f $(OBJS) $(OUT)
