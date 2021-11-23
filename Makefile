#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa matop
# Autor		: Wagner Meira Jr. (meira@dcc.ufmg.br)
# Histórico	: 2021-10-18 - arquivo criado
#		: 2021-10-21 - estrutura de diretórios
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#		: make clean - remove objetos e executável
#---------------------------------------------------------------------

CC = gcc
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
TMPDIR = tmp
TMP = $(TMPDIR)/res.out $(TMPDIR)/log.out
OBJS = $(OBJ)/matop.o $(OBJ)/mat.o $(OBJ)/memlog.o
HDRS = $(INC)/mat.h $(INC)/memlog.h $(INC)/msgassert.h
CFLAGS = -Wall -g -c -I$(INC) 

EXE = $(BIN)/matop

all: $(EXE)
	$(EXE) -s -1 matrizes/10x10/0.in -2 matrizes/10x10/1.in -p $(TMPDIR)/log.out -o $(TMPDIR)/res.out
	$(EXE) -m -1 matrizes/10x10/0.in -2 matrizes/10x10/1.in -p $(TMPDIR)/log.out -o $(TMPDIR)/res.out
	$(EXE) -t -1 matrizes/10x10/0.in -p $(TMPDIR)/log.out -o $(TMPDIR)/res.out

$(BIN)/matop: $(OBJS)
	$(CC) -o $(BIN)/matop $(OBJS) $(LIBS)

$(OBJ)/matop.o: $(HDRS) $(SRC)/matop.c
	$(CC) $(CFLAGS) -o $(OBJ)/matop.o $(SRC)/matop.c

$(OBJ)/mat.o: $(HDRS) $(SRC)/mat.c
	$(CC) $(CFLAGS) -o $(OBJ)/mat.o $(SRC)/mat.c 

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.c
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.c 
	
clean:
	rm $(EXE) $(OBJS) $(TMP)
