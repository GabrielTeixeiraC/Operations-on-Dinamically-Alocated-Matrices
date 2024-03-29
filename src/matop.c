//---------------------------------------------------------------------
// Arquivo	: matop.c
// Conteudo	: definicoes do TAD MAT 
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2021-11-02 - arquivo criado
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
int regmem, opcaoP, opcao2;
char nomeArquivoMatriz1[100], nomeArquivoMatriz2[100], nomeArquivoSaida[100], lognome[100];
FILE *arquivoSaida;

void uso()
// Descricao: imprime as opcoes de uso
// Entrada: nao tem
// Saida: impressao das opcoes de linha de comando
{
    fprintf(stderr,"matop\n");
    fprintf(stderr,"\t-s \t(soma matrizes) \n");
    fprintf(stderr,"\t-m \t(multiplica matrizes) \n");
    fprintf(stderr,"\t-t \t(transpoe matriz 1)\n");
    fprintf(stderr,"\t-1 m1.txt \t(matriz 1)\n");
    fprintf(stderr,"\t-2 m2.txt \t(matriz 2)\n");
    fprintf(stderr,"\t-o res.out \t(matriz resultante)\n");
    fprintf(stderr,"\t-p log.out \t(registro de desempenho)\n");
    fprintf(stderr,"\t-l \t(padrao de acesso e localidade)\n");
}

void parse_args(int argc,char ** argv)
// Descricao: le as opcoes da linha de comando e inicializa variaveis
// Entrada: argc e argv
// Saida: optescolhida, regmem, nomeArquivoMatriz1, m2noome, nomeArquivoSaida, lognome
{
    // variaveis externas do getopt
    extern char * optarg;
    extern int optind;

    // variavel auxiliar
    int c;

    // inicializacao variaveis globais para opcoes
    opescolhida = -1;
    regmem = 0;
    nomeArquivoMatriz1[0] = 0;
    nomeArquivoMatriz2[0] = 0;
    nomeArquivoSaida[0] = 0;
    lognome[0] = 0;

    // getopt - letra indica a opcao, : junto a letra indica parametro
    // no caso de escolher mais de uma operacao, vale a ultima
    while ((c = getopt(argc, argv, "smt1:2:o:p:l")) != EOF)
        switch(c) {
            case 's':
		        avisoAssert(opescolhida==-1,"Mais de uma operacao escolhida");
                opescolhida = OPSOMAR;
                break;
            case 'm':
		        avisoAssert(opescolhida==-1,"Mais de uma operacao escolhida");
                opescolhida = OPMULTIPLICAR;
                break;
            case 't':
		        avisoAssert(opescolhida==-1,"Mais de uma operacao escolhida");
	            opescolhida = OPTRANSPOR;
                break;
            case '1':
                strcpy(nomeArquivoMatriz1, optarg);
                break;
            case '2':
                strcpy(nomeArquivoMatriz2, optarg);
                opcao2 = 1;
                break;
            case 'o':
                strcpy(nomeArquivoSaida, optarg);
                break;
            case 'p': 
	            strcpy(lognome,optarg);
                opcaoP = 1;
		        break;
            case 'l': 
                regmem = 1;
		        break;
            case 'h':
                default:
                    uso();
                    exit(1);
        }

        // verificacao da consistencia das opcoes
        erroAssert(opescolhida>0, "matop - necessario escolher operacao");

        // verificação de existência dos nomes dos arquivos obrigatórios
        erroAssert(strlen(nomeArquivoMatriz1) > 0, "matop - nome de arquivo da matriz 1 tem que ser definido");
        erroAssert(strlen(nomeArquivoSaida) > 0, "matop - nome de arquivo do resultado tem que ser definido");
        erroAssert(strlen(lognome) > 0, "matop - nome de arquivo de registro de acesso tem que ser definido");

        // verificação do tamanho máximo dos nomes dos arquivos necessários
        erroAssert(strlen(nomeArquivoMatriz1) <= 100, "matop - nome de arquivo da matriz 1 excede o limite de caracteres");
        erroAssert(strlen(nomeArquivoSaida) <= 100, "matop - nome de arquivo do resultado excede o limite de caracteres");
        erroAssert(strlen(lognome) <= 100, "matop - nome de arquivo de registro de acesso excede o limite de caracteres");
        
        // verificação das opções não obrigatórias
        if (opescolhida == OPSOMAR || opescolhida == OPMULTIPLICAR){
            // verificação de existência do nome do arquivo da matriz 2
            erroAssert(strlen(nomeArquivoMatriz2) > 0, "matop - nome de arquivo da matriz 2 tem que ser definido");

            // verificação do tamanho máximo do nome do arquivo da matriz 2
            erroAssert(strlen(nomeArquivoMatriz2) <= 100, "matop - nome de arquivo da matriz 2 excede o limite de caracteres");
        }
}

void leMatrizDoArquivo(const char * nomeDoArquivoPonteiro, mat_tipo * mat, int id)
// Descricao: le os dados do arquivo "nomeDoArquivoPonteiro" e cria uma matriz mat com esses dados
// Entrada: nomeDoArquivoPonteiro, mat
// Saida: mat
{
    // arquivo a ser utilizado
    FILE * arquivo;

    // numero de linhas e colunas da matriz no arquivo
    int linhas, colunas;
    
    // copia o nome do arquivo para um vetor de char para facilitar o uso
    // os nomes dos arquivos já foram verificados na função parse args
    char nomeDoArquivo[100] = "";
    strcpy(nomeDoArquivo, nomeDoArquivoPonteiro);
    
    // abre arquivo para leitura de texto
    arquivo = fopen(nomeDoArquivo, "rt");
    erroAssert(arquivo != NULL, "Arquivo de matriz nao pode ser aberto");
    
    // cria matriz com o numero de linhas e colunas especificado no arquivo
    fscanf(arquivo, "%d %d", &linhas, &colunas);
    criaMatriz(mat, linhas, colunas, id);

    // preenche as linhas e colunas de mat com os dados do arquivo
    for (int i = 0; i < mat->linhas; i++){
        for (int j = 0; j < mat->colunas; j++){
            fscanf(arquivo, "%lf", &mat->matriz[i][j]);
            escreveMemLog( (long int) (&(mat->matriz[i][j])), sizeof(double), mat->id);
        }
    }    

    // fecha arquivo de leituras
    fclose(arquivo);
}

int main(int argc, char ** argv)
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

    // ativar registro de acesso
    if (regmem == 1){
        ativaMemLog();
    }
    else desativaMemLog();
    
    
    // abre arquivo de resultado
    arquivoSaida = fopen(nomeArquivoSaida, "wt");
    erroAssert(arquivoSaida != NULL,"Arquivo de resultado nao pode ser aberto");

    // execucao dependente da operacao escolhida
    switch (opescolhida){
        case OPSOMAR:
            // recebe de arquivos matrizes a e b, que sao somadas para a 
	        // matriz c, matriz c é impressa e todas as matrizes sao destruidas
            defineFaseMemLog(0);
            leMatrizDoArquivo(nomeArquivoMatriz1, &a, 0);
            leMatrizDoArquivo(nomeArquivoMatriz2, &b, 1);
            // inicializa a matriz c garantindo a compatibilidade das dimensoes
            criaMatriz(&c, a.linhas, a.colunas, 2);
            inicializaMatrizNula(&c);
            
            defineFaseMemLog(1);
            acessaMatriz(&a);
            acessaMatriz(&b);
            acessaMatriz(&c);
            somaMatrizes(&a, &b, &c);

            defineFaseMemLog(2);
            acessaMatriz(&c);
            imprimeMatrizNoArquivo(&c, arquivoSaida);

            destroiMatriz(&a);
            destroiMatriz(&b);
            destroiMatriz(&c);
            break;
        case OPMULTIPLICAR:
            // recebe de arquivos matrizes a e b, que sao multiplicadas para a 
	        // matriz c, matriz c é impressa e todas as matrizes sao destruidas
            defineFaseMemLog(0);
            leMatrizDoArquivo(nomeArquivoMatriz1, &a, 0);
            leMatrizDoArquivo(nomeArquivoMatriz2, &b, 1);
            // cria e inicializa a matriz c
            criaMatriz(&c, a.linhas, b.colunas, 2);
            inicializaMatrizNula(&c);


            defineFaseMemLog(1);
            acessaMatriz(&a);
            acessaMatriz(&b);
            acessaMatriz(&c);
            multiplicaMatrizes(&a, &b, &c);

            defineFaseMemLog(2);
            acessaMatriz(&c);
            imprimeMatrizNoArquivo(&c, arquivoSaida);

            destroiMatriz(&a);
            destroiMatriz(&b);
            destroiMatriz(&c);
            break;
        case OPTRANSPOR:
            // recebe de arquivo matriz a, que é transposta, impressa e destruida
            defineFaseMemLog(0);
            leMatrizDoArquivo(nomeArquivoMatriz1, &a, 0);

            defineFaseMemLog(1);
            acessaMatriz(&a);
            transpoeMatriz(&a);
            
            defineFaseMemLog(2);
            acessaMatriz(&a);
            imprimeMatrizNoArquivo(&a, arquivoSaida);
            
            destroiMatriz(&a);
            break;
        default:
            // nao deve ser executado, pois ha um erroAssert em parse_args
            uso();
            exit(1);
    }

    // fecha arquivo de saída
    fclose(arquivoSaida);

    // conclui registro de acesso
    finalizaMemLog();  
    return 0;
}