#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa matop
# Autor		: Wagner Meira Jr. (meira@dcc.ufmg.br)
# Histórico	: 2021-10-18 - arquivo criado
#		: 2021-10-21 - estrutura de diretórios
#               : 2021-11-15 - Versao 1.1 memlog
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#               : make mem - gera arquivos de registro de acesso
#               : make prof - faz medidas de tempo de desempenho
#               : make gprof - ilustra uso do gprof para depuração
#		: make clean - remove objetos e executável
#---------------------------------------------------------------------

CC = gcc
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/matop.o $(OBJ)/mat.o $(OBJ)/memlog.o
HDRS = $(INC)/mat.h $(INC)/memlog.h $(INC)/msgassert.h
CFLAGS = -pg -Wall -c -I$(INC)
#ANALISAMEM = ../analisamem/bin/analisamem

EXE = $(BIN)/matop

all:  mem perf gprof

mem: $(EXE)
#	$(EXE) -s -p /tmp/somalog.out -l -1 m21.txt -2 m22.txt -o res1.txt -l
#	rm -rf /tmp/somadin
#	mkdir /tmp/somadin
#	$(ANALISAMEM) -i /tmp/somalog.out -p /tmp/somadin/somadin
#	$(EXE) -m -p /tmp/multiplicacaolog.out -l -1 m21.txt -2 m22.txt -o res2.txt -l
#	rm -rf /tmp/multiplicacaodin
#	mkdir /tmp/multiplicacaodin
#	$(ANALISAMEM) -i /tmp/multiplicacaolog.out -p /tmp/multiplicacaodin/multiplicacaodin
#	$(EXE) -t -p /tmp/transposicaolog.out -l -1 m21.txt -o res3.txt -l
#	rm -rf /tmp/transposicaodin
#	mkdir /tmp/transposicaodin
#	$(ANALISAMEM) -i /tmp/transposicaolog.out -p /tmp/transposicaodin/transposicaodin

perf: $(EXE)
	$(EXE) -s -p /tmp/soma.out -1 m1.txt -2 m2.txt -o res1.txt
	$(EXE) -m -p /tmp/mult.out -1 m1.txt -2 m2.txt -o res2.txt
	$(EXE) -t -p /tmp/transp.out -1 m1.txt -o res3.txt

gprof: $(BIN)/matop
#	$(EXE) -s -p /tmp/soma5000gprof.out -1 m21.txt -2 m22.txt -o res34.txt
#	gprof $(EXE) gmon.out > /tmp/soma5000gprof.txt
#	$(EXE) -m -p /tmp/mult5000gprof.out -1 m21.txt -2 m22.txt -o res35.txt
#	gprof $(EXE) gmon.out > /tmp/mult5000gprof.txt
#	$(EXE) -t -p /tmp/transp5000gprof.out -1 m21.txt -o res36.txt
#	gprof $(EXE) gmon.out > /tmp/transp5000gprof.txt
	

$(BIN)/matop: $(OBJS)
	$(CC) -pg -o $(BIN)/matop $(OBJS) $(LIBS)

$(OBJ)/matop.o: $(HDRS) $(SRC)/matop.c
	$(CC) $(CFLAGS) -o $(OBJ)/matop.o $(SRC)/matop.c 

$(OBJ)/mat.o: $(HDRS) $(SRC)/mat.c
	$(CC) $(CFLAGS) -o $(OBJ)/mat.o $(SRC)/mat.c 

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.c
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.c 
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out
