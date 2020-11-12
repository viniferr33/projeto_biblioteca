/* ### GRUPO 3 ###
Felipe Moraes Marcello                  RA: 
Vinicius Ferreira Gomes                 RA: 200603
Yuri Carlos Achnitz Batista Belinsky    RA: 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

void pause();
void flush();
void aloca_aluno(aluno **p, int qtd);
void mostra_alunos(aluno *p, int qtd);
void cadastra_aluno(aluno *p, int qtd);

int main(int argc, char const *argv[])
{
    aluno *alunos = NULL;
    aloca_aluno(&alunos, 1);
    cadastra_aluno(alunos, 1);
    return 0;
} //MAIN

void aloca_aluno(aluno **p, int qtd)
{
    if ((*p = (aluno *)realloc(*p, qtd * sizeof(aluno))) == NULL)
    {
        printf("\033[0;31mErro de alocação!\033[0m");
        pause();
        exit(1);
    }
}

void cadastra_aluno(aluno *p, int qtd)
{
    system(clear);
    printf("### Cadastro de alunos ###\n\n");

    printf("Digite o nome do aluno:\t");
    fgets(p->nome, 79, stdin);
    flush();
    *(p->nome + strlen(p->nome) - 1) = '\0';

    printf("\nDigite o RA do aluno:\t");
    int aux_ra = 0;
    do
    {
        flush();
        scanf("%s", p->RA);
        flush();

        if (strlen(p->RA) == 6)
        {
            int j;
            for (j = 0; j < 6; j++)
            {
                if (isdigit(*(p->RA + j)) == 0)
                {
                    printf("\nO RA deve ser composto por digitos numericos!\nDigite o RA do aluno: ");
                    aux_ra = 0;
                    break;
                }
                else
                    aux_ra = 1;
            }
        }

        else
        {
            printf("\nO RA deve conter 6 digitos!\nDigite o RA do aluno: ");
        }

    } while (aux_ra == 0);

    p->emprestado = 0;
    p->reservado = 0;

    int i;
    for (i = 0; i < 4; i++)
    {
        p->tabela[i].sigla = 'L';
    }
    system(clear);
    printf("\033[0;32m### Cadastro Realizado com sucesso!! ###\033[0m\n");
    printf("Nome:\t\033[0;36m%s\033[0;0m\t", p->nome);
    printf("RA: \t\033[0;36m%s\033[0;0m\n", p->RA);

    pause();
}

// Esta função serve para limpar o buffer em ambos os sistemas operacionais
void flush()
{
// ## Esse trecho de código é executado durante a compilação ##
#if defined(_WIN32) || defined(_WIN64) // Testa se o SO é Windows
    fflush(stdin);                     // Caso o SO seja Windows ele executa o fflush
#else
#ifdef __linux // Testa se o SO é Linux
    __fpurge(stdin);         // Caso o SO seja linux executa o fpurge
#endif
#endif
}

void pause()
{
    flush();
    printf("Pressione qualquer tecla para continuar. . .");
    getchar();
    flush();
}

