//---------------------------------------------------------------------
// Arquivo	: mat.cpp
// Conteudo	: implementacao do TAD MAT 
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2021-11-02 - arquivo criado
//---------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mat.h"
#include "memlog.h"
#include "msgassert.h"

#define INITRANDOMRANGE 10

void criaMatriz(mat_tipo * mat, int linhas, int colunas)
// Descricao: cria matriz com dimensoes tx X ty
// Entrada: mat, tx, ty
// Saida: mat
{
    // verifica se os valores de tx e ty são validos
    erroAssert(linhas > 0, "Dimensao nula");
    erroAssert(colunas > 0, "Dimensao nula");
    
    // inicializa as dimensões da matriz
    mat->linhas = linhas;
    mat->colunas = colunas;

    // aloca a memória necessária para os ponteiros para double* 
    mat->matriz = malloc(linhas * sizeof(double*));
    erroAssert(!(mat->matriz == NULL), "Ponteiro nao foi alocado");
    
    // aloca a memória necessária para os ponteiros para double
    for (int i = 0; i < linhas; i++){
        mat->matriz[i] = malloc(colunas * sizeof(double));
        erroAssert(!(mat->matriz[i] == NULL), "Ponteiro nao foi alocado");
    }
}

void inicializaMatrizNula(mat_tipo * mat)
// Descricao: inicializa mat com valores nulos 
// Entrada: mat
// Saida: mat
{
    // inicializa todos os elementos da matriz com 0, por seguranca 
    for (int i = 0; i < mat->linhas; i++){
        for (int j = 0; j < mat->colunas; j++){
            mat->matriz[i][j] = 0;
            escreveMemLog( (long int) (&(mat->matriz[i][j])), sizeof(double));
        }
    }
}

void inicializaMatrizAleatoria(mat_tipo * mat)
// Descricao: inicializa mat com valores aleatorios
// Entrada: mat 
// Saida: mat
{
    // inicializa matriz com valores aletorios entre 0 e INITRANDOMRANGEs
    for (int i = 0; i < mat->linhas; i++){
        for (int j = 0; j < mat->colunas; j++){
            mat->matriz[i][j] = drand48() * INITRANDOMRANGE;
            escreveMemLog( (long int) (&(mat->matriz[i][j])), sizeof(double));
        }
    }
}

void imprimeMatrizNoArquivo(mat_tipo * mat, FILE * arquivo)
// Descricao: imprime a matriz no arquivo de saída
// Entrada: mat, arquivo
// Saida: impressão no arquivo especificado
{
    // imprime a quantidade de linhas e colunas 
    fprintf(arquivo, "%d %d", mat->linhas, mat->colunas);
    fprintf(arquivo, "\n");
    
    // imprime as linhas e colunas
    for (int i = 0; i < mat->linhas; i++){
        for(int j = 0; j < mat->colunas; j++){
            fprintf(arquivo, "%lf ", mat->matriz[i][j]);
            leMemLog( (long int) (&(mat->matriz[i][j])), sizeof(double));
        }
        if(i != mat->linhas - 1){
            fprintf(arquivo, "\n");
        }
    }   
}

void escreveElemento(mat_tipo * mat, int x, int y, double valor)
// Descricao: atribui o valor v ao elemento (x,y) de mat
// Entrada: mat, x, y, v
// Saida: mat
{
    // verifica se x e y sao validos
    erroAssert(!( (x < 0) || (x >= mat->linhas) ), "Indice invalido");
    erroAssert(!( (y < 0) || (y >= mat->colunas) ), "Indice invalido");

    // atribui o valor ao elemento (x, y) de mat
    mat->matriz[x][y] = valor;
    escreveMemLog( (long int) (&(mat->matriz[x][y])), sizeof(double));
}

double leElemento(mat_tipo * mat, int x, int y)
// Descricao: retorna o elemento (x,y) de mat 
// Entrada: mat, x, y
// Saida: mat[x][y] 
{
    // verifica se x e y sao validos
    erroAssert(!( (x < 0) || (x >= mat->linhas) ), "Indice invalido");
    erroAssert(!( (y < 0) || (y >= mat->colunas) ), "Indice invalido");

    // retorna o elemento (x, y) de mat
    leMemLog( (long int) (&(mat->matriz[x][y])), sizeof(double));
    return mat->matriz[x][y];
}

void copiaMatriz(mat_tipo * src, mat_tipo * dst)
// Descricao: faz uma copia de src em dst
// Entrada: src
// Saida: dst
{
    // cria novamente a matriz dst para ajustar as suas dimensoes
    criaMatriz(dst, src->linhas, src->colunas);

    // inicializa a matriz dst como nula
    inicializaMatrizNula(dst);
    
    // copia os elementos da matriz src
    for (int i = 0; i < src->linhas; i++){
        for (int j = 0; j < src->colunas; j++){
            dst->matriz[i][j] = src->matriz[i][j];
            leMemLog( (long int) (&(src->matriz[i][j])), sizeof(double));
            escreveMemLog( (long int) (&(dst->matriz[i][j])), sizeof(double));
        }
    }
}

void somaMatrizes(mat_tipo * a, mat_tipo * b, mat_tipo * c)
// Descricao: soma as matrizes a e b e armazena o resultado em c
// Entrada: a, b
// Saida: c
{
    // verifica se as dimensoes das matrizes a e b sao as mesmas
    erroAssert(a->linhas == b->linhas, "Dimensoes incompativeis");
    erroAssert(a->colunas == b->colunas, "Dimensoes incompativeis");

    // inicializa a matriz c garantindo a compatibilidade das dimensoes
    criaMatriz(c, a->linhas, a->colunas);
    inicializaMatrizNula(c);

    // faz a soma elemento a elemento
    for (int i = 0; i < c->linhas; i++){
        for (int j = 0; j < c->colunas; j++){
            c->matriz[i][j] = a->matriz[i][j] + b->matriz[i][j];
            leMemLog( (long int) (&(a->matriz[i][j])), sizeof(double));
            leMemLog( (long int) (&(b->matriz[i][j])), sizeof(double));
            escreveMemLog( (long int) (&(c->matriz[i][j])), sizeof(double));
        }
    }
}

void multiplicaMatrizes(mat_tipo * a, mat_tipo * b, mat_tipo * c)
// Descricao: multiplica as matrizes a e b e armazena o resultado em c
// Entrada: a,b
// Saida: c
{
    // verifica a compatibilidade das dimensoes 
    erroAssert(a->colunas == b->linhas, "Dimensoes incompativeis para multiplicacao");

    // cria e inicializa a matriz c
    criaMatriz(c, a->linhas, b->colunas);
    inicializaMatrizNula(c);

    // realiza a multiplicacao de matrizes
    for (int i = 0; i < c->linhas; i++){
        for (int j = 0; j < c->colunas; j++){
            for (int k = 0; k < a->colunas; k++){
                c->matriz[i][j] += a->matriz[i][k] * b->matriz[k][j];
                leMemLog( (long int) (&(a->matriz[i][k])), sizeof(double));
                leMemLog( (long int) (&(b->matriz[k][j])), sizeof(double));
                escreveMemLog( (long int) (&(c->matriz[i][j])), sizeof(double));                
            }     
        }
    }
}

void transpoeMatriz(mat_tipo * a)
// Descricao: transpoe a matriz a
// Entrada: a
// Saida: a
{
    // aloca espaço, cria e inicializa uma matriz auxiliar aux
    mat_tipo * aux = malloc (sizeof(mat_tipo));
    erroAssert(!(aux == NULL), "Ponteiro nao alocado");
    criaMatriz(aux, a->colunas, a->linhas);
    inicializaMatrizNula(aux);
    
    // copia os elementos da matriz a(m x n) para a matriz aux(n x m)
    for (int i = 0; i < a->linhas; i++){
        for (int j = 0; j < a->colunas; j++){
            aux->matriz[j][i] = a->matriz[i][j];
            leMemLog( (long int) (&(a->matriz[i][j])), sizeof(double));
            escreveMemLog( (long int) (&(aux->matriz[i][j])), sizeof(double));
        }
    }

    // copia os elementos da matriz aux para a matriz a transposta
    copiaMatriz(aux, a);

    // destroi a matriz aux, tornando-a inacessível
    destroiMatriz(aux);
}

void destroiMatriz(mat_tipo * a)
// Descricao: destroi a matriz a, que se torna inacessível, evitando vazamento de memória
// Entrada: a
// Saida: a
{
    // apenas um aviso se a matriz for destruida mais de uma vez
    avisoAssert(a->matriz != NULL, "Matriz ja foi destruida");

    // libera o espaço alocado para as colunas da matriz
    for (int i = 0; i < a->linhas; i++){
        free(a->matriz[i]);
    }

    // libera o espaço alocado para as linhas da matriz
    free(a->matriz);

    // torna o ponteiro da matriz nulo, por segurança
    a->matriz = NULL;
}