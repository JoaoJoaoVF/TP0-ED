//---------------------------------------------------------------------
// Arquivo      : matop.c
// Conteudo     : programa de avaliacao do TAD MAT
// Autor        : Wagner Meira Jr. (meira@dcc.ufmg.br)
// Historico    : 2021-10-18 - arquivo criado
//              : 2021-10-21 - estrutura de diretorios
//              : 2021-10-25 - opcoes de linha de comando
//              : 2021-11-14 - adequacao para versao 1.1 memlog
//---------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>
#include <string.h>
#include "mat.h"
#include "memlog.h"
#include "msgassert.h"

// definicoes de operacoes a serem testadas
#define OPSOMAR 1
#define OPMULTIPLICAR 2
#define OPTRANSPOR 3

// variaveis globais para opcoes
static int opescolhida;
char lognome[100];
char nomearq1[100];
char nomearq2[100];
char nomearqres[100];
int optx, opty, regmem;
int *obs;

void uso()
// Descricao: imprime as opcoes de uso
// Entrada: nao tem
// Saida: impressao das opcoes de linha de comando
{
  fprintf(stderr, "matop\n");
  fprintf(stderr, "\t-s \t(soma matrizes) \n");
  fprintf(stderr, "\t-m \t(multiplica matrizes) \n");
  fprintf(stderr, "\t-t \t(transpoe matriz 1)\n");
  fprintf(stderr, "\t-1 <m1.txt>\t(matriz 1)\n");
  fprintf(stderr, "\t-2 <m2.txt>\t(matriz 2)\n");
  fprintf(stderr, "\t-o <res.out>\t(matriz resultante)\n");
  fprintf(stderr, "\t-p <log.out>\t(registro de desempenho)\n");
  fprintf(stderr, "\t-l \t(padrao de acesso e localidade)\n");
}

double le_dado_matriz_x(char arq[])
{
  // printf("func x %s\n\n", arq);
  FILE *matriz = fopen(arq, "r");
  erroAssert(matriz != NULL, "Não foi possivel abrir o arquivo");
  int linhas, colunas, x;
  fscanf(matriz, "%d %d", &linhas, &colunas);
  fclose(matriz);
  x = linhas;
  // printf("func x %d\n\n", x);
  return x;
}
double le_dado_matriz_y(char *arq)
{
  // printf("func y %s\n\n", arq);
  FILE *matriz = fopen(arq, "r");
  erroAssert(matriz != NULL, "Não foi possivel abrir o arquivo");
  int linhas, colunas, y;
  fscanf(matriz, "%d %d", &linhas, &colunas);
  fclose(matriz);
  y = colunas;
  //  printf("func y %d\n\n", y);
  return y;
}

void parse_args(int argc, char **argv)
// Descricao: le as opcoes da linha de comando e inicializa variaveis
// Entrada: argc e argv
// Saida: optescolhida, optx, opty, regmem, lognome
{
  // variaveis externas do getopt
  extern char *optarg;
  extern int optind;

  // variavel auxiliar
  int c;

  // inicializacao variaveis globais para opcoes
  opescolhida = -1;
  optx = -1;
  opty = -1;
  regmem = 0;
  lognome[0] = 0;
  nomearq1[0] = 0;
  nomearq2[0] = 0;
  nomearqres[0] = 0;
  obs = 0;

  // getopt - letra indica a opcao, : junto a letra indica parametro
  // no caso de escolher mais de uma operacao, vale a ultima
  while ((c = getopt(argc, argv, "smtp:1:2:o:lh")) != EOF)
    switch (c)
    {
    case 'm':
      avisoAssert(opescolhida == -1, "Mais de uma operacao escolhida");
      opescolhida = OPMULTIPLICAR;
      break;
    case 's':
      avisoAssert(opescolhida == -1, "Mais de uma operacao escolhida");
      opescolhida = OPSOMAR;
      break;
    case 't':
      avisoAssert(opescolhida == -1, "Mais de uma operacao escolhida");
      opescolhida = OPTRANSPOR;
      break;
    case 'p':
      strcpy(lognome, optarg);
      break;
    case '1':
      strcpy(nomearq1, optarg);
      optx = le_dado_matriz_x(nomearq1);
      opty = le_dado_matriz_y(nomearq1);
      break;
    case '2':
      strcpy(nomearq2, optarg);
      optx = le_dado_matriz_x(nomearq2);
      opty = le_dado_matriz_y(nomearq2);
      break;
    case 'l':
      regmem = 1;
      break;
    case 'o':
      strcpy(nomearqres, optarg);
      break;
    case 'h':
    default:
      uso();
      exit(1);
    }
  // verificacao da consistencia das opcoes
  erroAssert(opescolhida > 0, "matop - necessario escolher operacao");
  erroAssert(strlen(lognome) > 0,
             "matop - nome de arquivo de registro de acesso tem que ser definido");
  erroAssert(optx > 0, "matop - dimensao X da matriz tem que ser positiva");
  erroAssert(opty > 0, "matop - dimensao Y da matriz tem que ser positiva");
}

int main(int argc, char **argv)
// Descricao: programa principal para execucao de operacoes de matrizes
// Entrada: argc e argv
// Saida: depende da operacao escolhida
{
  // ate 3 matrizes sao utilizadas, dependendo da operacao
  mat_tipo a, b, c;
  // avaliar linha de comando
  parse_args(argc, argv);
  // iniciar registro de acesso
  iniciaMemLog(lognome);

  // ativar ou nao o registro de acesso
  if (regmem)
  {
    ativaMemLog();
  }
  else
  {
    desativaMemLog();
  }

  // execucao dependente da operacao escolhida
  switch (opescolhida)
  {
  case OPSOMAR:
    // cria matrizes a e b aleatorias, que sao somadas para a matriz c
    // matriz c é impressa e todas as matrizes sao destruidas
    defineFaseMemLog(0);
    criaMatriz(&a, optx, opty, 0);
    atribuiValoresMatriz(&a, nomearq1);
    criaMatriz(&b, optx, opty, 1);
    atribuiValoresMatriz(&b, nomearq2);
    criaMatriz(&c, optx, opty, 2);
    inicializaMatrizNula(&c);
    defineFaseMemLog(1);
    acessaMatriz(&a);
    acessaMatriz(&b);
    acessaMatriz(&c);
    somaMatrizes(&a, &b, &c);
    defineFaseMemLog(2);
    acessaMatriz(&c);
    if (regmem)
      imprimeMatriz(&c);
    criaArquivoresultado(&c, nomearqres);
    destroiMatriz(&a);
    destroiMatriz(&b);
    destroiMatriz(&c);
    break;
  case OPMULTIPLICAR:
    // cria matrizes a e b aleatorias, que sao multiplicadas para matriz c
    // matriz c é impressa e todas as matrizes sao destruidas
    defineFaseMemLog(0);
    criaMatriz(&a, optx, opty, 0);
    atribuiValoresMatriz(&a, nomearq1);
    criaMatriz(&b, opty, optx, 1);
    atribuiValoresMatriz(&b, nomearq2);
    criaMatriz(&c, optx, optx, 2);
    inicializaMatrizNula(&c);
    defineFaseMemLog(1);
    acessaMatriz(&a);
    acessaMatriz(&b);
    acessaMatriz(&c);
    multiplicaMatrizes(&a, &b, &c);
    defineFaseMemLog(2);
    acessaMatriz(&c);
    if (regmem)
      imprimeMatriz(&c);
    criaArquivoresultado(&c, nomearqres);
    destroiMatriz(&a);
    destroiMatriz(&b);
    destroiMatriz(&c);
    break;
  case OPTRANSPOR:
    // cria matriz a aleatoria, que e transposta, impressa e destruida
    defineFaseMemLog(0);
    criaMatriz(&a, optx, opty, 0);
    atribuiValoresMatriz(&a, nomearq1);
    defineFaseMemLog(1);
    acessaMatriz(&a);
    transpoeMatriz(&a);
    defineFaseMemLog(2);
    acessaMatriz(&a);
    if (regmem)
      imprimeMatriz(&a);
    criaArquivoresultado(&a, nomearqres);
    destroiMatriz(&a);
    break;
  default:
    // nao deve ser executado, pois ha um erroAssert em parse_args
    uso();
    exit(1);
  }

  // conclui registro de acesso
  return finalizaMemLog();
}
