//---------------------------------------------------------------------
// Arquivo	: mat.h
// Conteudo	: definicoes do TAD MAT
// Autor	: Wagner Meira Jr. (meira@dcc.ufmg.br)
// Historico	: 2021-10-18 - arquivo criado
//		: 2021-10-21 - estrutura de diretorios
//---------------------------------------------------------------------

#ifndef MATH
#define MATH

#include "memlog.h"

//#ifndef MAXTAM
//#define MAXTAM 500
//#endif

typedef struct mat
{
	// double m[MAXTAM][MAXTAM];
	double **m;
	int tamx, tamy;
	int id;
} mat_tipo;

void criaMatriz(mat_tipo *mat, int tx, int ty, int id);
void inicializaMatrizNula(mat_tipo *mat);
void atribuiValoresMatriz(mat_tipo *mat, char arq[]);
double acessaMatriz(mat_tipo *mat);
void imprimeMatriz(mat_tipo *mat);
void criaArquivoresultado(mat_tipo *mat, char arq[]);
void escreveElemento(mat_tipo *mat, int x, int y, double v);
double leElemento(mat_tipo *mat, int x, int y);
void copiaMatriz(mat_tipo *src, mat_tipo *dst, int dst_id);
void somaMatrizes(mat_tipo *a, mat_tipo *b, mat_tipo *c);
void multiplicaMatrizes(mat_tipo *a, mat_tipo *b, mat_tipo *c);
void transpoeMatriz(mat_tipo *a);
void destroiMatriz(mat_tipo *a);

#endif
