//---------------------------------------------------------------------
// Arquivo	: mat.c
// Conteudo	: implementacao do TAD MAT
// Autor	: Wagner Meira Jr. (meira@dcc.ufmg.br)
// Historico	: 2021-10-18 - arquivo criado
//		: 2021-10-21 - estrutura de diretorios
//              : 2021-11-14 - adequacao para versao 1.1 memlog
//---------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
//#include <cstdio  >
#include "mat.h"
#include "memlog.h"
#include "msgassert.h"

// limite superior da inicializacao aleatoria
#define INITRANDOMRANGE 10
// Macro que realiza swap sem variavel auxiliar
#define ELEMSWAP(x, y) (x += y, y = x - y, x -= y)

void criaMatriz(mat_tipo *mat, int tx, int ty, int id)
// Descricao: cria matriz com dimensoes tx X ty
// Entrada: mat, tx, ty, id
// Saida: mat
{
  // verifica se os valores de tx e ty são validos
  erroAssert(tx > 0, "Dimensao nula");
  erroAssert(ty > 0, "Dimensao nula");

  // inicializa as dimensoes da matriz
  mat->tamx = tx;
  mat->tamy = ty;
  mat->id = id;
  // aloca a matriz
  mat->m = malloc(mat->tamx * sizeof(double *));
  int i;
  for (i = 0; i < mat->tamx; i++)
  {
    mat->m[i] = malloc(sizeof(double) * mat->tamy);
  }
  erroAssert(mat->m != NULL, "Malloc falhou");
}

void inicializaMatrizNula(mat_tipo *mat)
// Descricao: inicializa mat com valores nulos
// Entrada: mat
// Saida: mat
{
  int i, j;
  // inicializa todos os elementos da matriz com 0, por seguranca
  for (i = 0; i < mat->tamx; i++)
  {
    for (j = 0; j < mat->tamy; j++)
    {
      mat->m[i][j] = 0;
      ESCREVEMEMLOG((long int)(&(mat->m[i][j])), sizeof(double), mat->id);
    }
  }
}

void atribuiValoresMatriz(mat_tipo *mat, char arq[])
// Descricao: inicializa mat com valores aleatorios
// Entrada: mat
// Saida: mat
{
  inicializaMatrizNula(mat);
  int i = 0, j = 0;
  double elemento;
  FILE *matriz = fopen(arq, "r");
  erroAssert(matriz != NULL, "Não foi possivel abrir o arquivo");
  fscanf(matriz, "%lf", &elemento);
  fscanf(matriz, "%lf", &elemento);
  int x = 0;
  for (int alfa = 0; alfa < (mat->tamx * mat->tamy); alfa++)
  {
    if (x == mat->tamx)
    {
      x = 0;
      i++;
      j = 0;
    }
    fscanf(matriz, "%lf", &elemento);
    mat->m[i][j] = elemento;
    ESCREVEMEMLOG((long int)(&(mat->m[i][j])), sizeof(double), mat->id);
    x++;
    j++;
  }
  fclose(matriz);
}

double acessaMatriz(mat_tipo *mat)
// Descricao: acessa mat para fins de registro de acesso
// Entrada: mat
// Saida: mat
{
  int i, j;
  double aux, s = 0.0;
  for (i = 0; i < mat->tamx; i++)
  {
    for (j = 0; j < mat->tamy; j++)
    {
      aux = mat->m[i][j];
      s += aux;
      LEMEMLOG((long int)(&(mat->m[i][j])), sizeof(double), mat->id);
    }
  }
  return s; // apenas para evitar que acesso seja eliminado
}

void imprimeMatriz(mat_tipo *mat)
// Descricao: imprime a matriz com a identificacao de linhas e colunas
// Entrada: mat
// Saida: impressao na saida padrao (stdout)
{
  int i, j;

  // imprime os identificadores de coluna
  printf("%9s", " ");
  for (j = 0; j < mat->tamy; j++)
    printf("%8d ", j);
  printf("\n");

  // imprime as linhas
  for (i = 0; i < mat->tamx; i++)
  {
    printf("%8d ", i);
    for (j = 0; j < mat->tamy; j++)
    {
      printf("%8.2f ", mat->m[i][j]);
      LEMEMLOG((long int)(&(mat->m[i][j])), sizeof(double), mat->id);
    }
    printf("\n");
  }
}

void criaArquivoresultado(mat_tipo *mat, char arq[])
{
  int i, j;
  FILE *resultado;
  resultado = fopen(arq, "w");
  erroAssert(resultado != NULL, "Não foi possivel abrir o arquivo");
  // imprime o tamanho da saida
  fprintf(resultado, "%d %d \n", mat->tamx, mat->tamy);

  // escreve as linhas no arquvivo
  for (i = 0; i < mat->tamx; i++)
  {
    for (j = 0; j < mat->tamy; j++)
    {
      fprintf(resultado, "%8.2f ", mat->m[i][j]);
      LEMEMLOG((long int)(&(mat->m[i][j])), sizeof(double), mat->id);
    }
    fprintf(resultado, "\n");
  }
}
void escreveElemento(mat_tipo *mat, int x, int y, double v) // o que ela faz?????
// Descricao: atribui o valor v ao elemento (x,y) de mat
// Entrada: mat, x, y, v
// Saida: mat
{
  // verifica se x e y sao validos
  erroAssert((x < 0) || (x >= mat->tamx), "Indice invalido");
  erroAssert((y < 0) || (y >= mat->tamy), "Indice invalido");

  mat->m[x][y] = v;
  ESCREVEMEMLOG((long int)(&(mat->m[x][y])), sizeof(double), mat->id);
}

double leElemento(mat_tipo *mat, int x, int y)
// Descricao: retorna o elemento (x,y) de mat
// Entrada: mat, x, y
// Saida: mat[x][y]
{
  // verifica se x e y sao validos
  erroAssert((x < 0) || (x >= mat->tamx), "Indice invalido");
  erroAssert((y < 0) || (y >= mat->tamy), "Indice invalido");

  LEMEMLOG((long int)(&(mat->m[x][y])), sizeof(double), mat->id);
  return mat->m[x][y];
}

void copiaMatriz(mat_tipo *src, mat_tipo *dst, int dst_id)
// Descricao: faz uma copia de src em dst
// Entrada: src, dst_id
// Saida: dst
{
  int i, j;

  // cria novamente a matriz dst para ajustar as suas dimensoes
  criaMatriz(dst, src->tamx, src->tamy, dst_id);
  // inicializa a matriz dst como nula
  inicializaMatrizNula(dst);
  // copia os elementos da matriz src
  for (i = 0; i < src->tamx; i++)
  {
    for (j = 0; j < src->tamy; j++)
    {
      dst->m[i][j] = src->m[i][j];
      LEMEMLOG((long int)(&(src->m[i][j])), sizeof(double), src->id);
      ESCREVEMEMLOG((long int)(&(dst->m[i][j])), sizeof(double), dst->id);
    }
  }
}

void somaMatrizes(mat_tipo *a, mat_tipo *b, mat_tipo *c)
// Descricao: soma as matrizes a e b e armazena o resultado em c
// Entrada: a, b
// Saida: c
{
  int i, j;
  // verifica se as dimensoes das matrizes a e b sao as mesmas
  erroAssert(a->tamx == b->tamx, "Dimensoes incompativeis");
  erroAssert(a->tamy == b->tamy, "Dimensoes incompativeis");

  // inicializa a matriz c garantindo a compatibilidade das dimensoes
  criaMatriz(c, a->tamx, a->tamy, c->id);
  inicializaMatrizNula(c);

  // faz a soma elemento a elemento
  for (i = 0; i < a->tamx; i++)
  {
    for (j = 0; j < a->tamy; j++)
    {
      c->m[i][j] = a->m[i][j] + b->m[i][j];
      LEMEMLOG((long int)(&(a->m[i][j])), sizeof(double), a->id);
      LEMEMLOG((long int)(&(b->m[i][j])), sizeof(double), b->id);
      ESCREVEMEMLOG((long int)(&(c->m[i][j])), sizeof(double), c->id);
    }
  }
}

void multiplicaMatrizes(mat_tipo *a, mat_tipo *b, mat_tipo *c)
// Descricao: multiplica as matrizes a e b e armazena o resultado em c
// Entrada: a,b
// Saida: c
{
  int i, j, k;
  // verifica a compatibilidade das dimensoes
  erroAssert(a->tamy == b->tamx, "Dimensoes incompativeis");

  // cria e inicializa a matriz c
  criaMatriz(c, a->tamx, b->tamy, c->id);
  inicializaMatrizNula(c);

  // realiza a multiplicacao de matrizes
  for (i = 0; i < c->tamx; i++)
  {
    for (j = 0; j < c->tamy; j++)
    {
      for (k = 0; k < a->tamy; k++)
      {
        c->m[i][j] += a->m[i][k] * b->m[k][j];
        LEMEMLOG((long int)(&(a->m[i][k])), sizeof(double), a->id);
        LEMEMLOG((long int)(&(b->m[k][j])), sizeof(double), b->id);
        ESCREVEMEMLOG((long int)(&(c->m[i][j])), sizeof(double), c->id);
      }
    }
  }
}

void transpoeMatriz(mat_tipo *a)
// Descricao: transpoe a matriz a
// Entrada: a
// Saida: a
{
  int i, j, dim;

  // determina a maior dimensao entre tamx e tamy
  dim = (a->tamx > a->tamy ? a->tamx : a->tamy);

  // faz a transposicao como se a matriz fosse quadrada
  for (i = 0; i < dim; i++)
  {
    for (j = i + 1; j < dim; j++)
    {
      ELEMSWAP((a->m[i][j]), (a->m[j][i]));
      ESCREVEMEMLOG((long int)(&(a->m[i][j])), sizeof(double), a->id);
      ESCREVEMEMLOG((long int)(&(a->m[j][i])), sizeof(double), a->id);
    }
  }
  // inverte as dimensoes da matriz transposta
  ELEMSWAP(a->tamx, a->tamy);
}

void destroiMatriz(mat_tipo *a)
// Descricao: destroi a matriz a, que se torna inacessível
// Entrada: a
// Saida: a
{
  // apenas um aviso se a matriz for destruida mais de uma vez
  avisoAssert(((a->tamx > 0) && (a->tamy > 0)), "Matriz já foi destruida");
  // desaloca matriz
  int i;
  for (i = 0; i < a->tamx; i++)
  {
    free(a->m[i]);
  }
  free(a->m);
  //  torna as dimensoes invalidas
  a->id = a->tamx = a->tamy = -1;
}
