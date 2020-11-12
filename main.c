/* ### GRUPO 3 ###
Felipe Moraes Marcello                  RA: 
Vinicius Ferreira Gomes                 RA: 200603
Yuri Carlos Achnitz Batista Belinski    RA: 200262
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// ## Esse trecho de código é executado durante a compilação ##
#if defined(_WIN32) || defined(_WIN64) // Testa se o SO é Windows
const char *clear = "cls";             // Define os comandos do sistema windows
#else
#ifdef __linux // Testa se o SO é Linux
const char *clear = "clear"; // Define os comandos do sistema linux
#endif
#endif

struct info_livro
{
    char sigla;
    int reg;
};

typedef struct aluno
{
    char nome[80];
    char RA[7];
    int emprestado;
    int reservado;
    struct info_livro tabela[4];
} aluno;

typedef struct livro
{
    int reg; //gerado automaticamente
    char titulo[80];
    char autor[80];
    struct info_aluno status[2];
} livro;

struct info_aluno
{
    char sigla;  //'L' - livre, 'E' - emprestado, 'R' - reservado (data da retirada -1 dia depois de devolver)
    char RA[7];  //
    int dia_ret; //dia max = 31
    int mes_ret; //mes fev = 28
    int dia_dev; //abril, junho, setembro, novembro = 30 dias
    int mes_dev; //o resto = 31
};

void aloca_aluno(aluno **p, int qtd);
void mostra_alunos(aluno *p, int qtd);
void cadastra_aluno(aluno *p, int qtd);

int main(int argc, char const *argv[])
{
    return 0;
} //MAIN

void aloca_aluno(aluno **p, int qtd)
{
    if ((*p = (aluno *)realloc(*p, qtd * sizeof(aluno))) == NULL)
        exit(1);
}

void cadastra_livro(livro *livros)
{
    static int registro = 0;

    livros->status->sigla = 'L';
}