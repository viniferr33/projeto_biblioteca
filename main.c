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
void consulta_total(aluno *p, int qtd);
void consulta_parcial(aluno *p, int qtd);

int main(int argc, char const *argv[])
{
    aluno *alunos = NULL;
    int opt = -1;
    int qtd_a = 0;

    do
    {
        system(clear);
        printf("0 - Sair\n1 - Adicionar\n2 - Pesquisa total\n3 - Pesquisa Parcial\n");
        scanf("%i", &opt);
        flush();

        switch (opt)
        {
        case 1:
            aloca_aluno(&alunos, qtd_a + 1);
            cadastra_aluno(alunos, qtd_a);
            qtd_a++;
            break;
        
        case 2:
            consulta_total(alunos, qtd_a);
            break;

        case 3:
            consulta_parcial(alunos, qtd_a);
            break;

        default:
            break;
        }

    } while (opt != 0);
    
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
    fgets((p+qtd)->nome, 79, stdin);
    flush();
    *((p+qtd)->nome + strlen((p+qtd)->nome) - 1) = '\0';

    printf("\nDigite o RA do aluno:\t");
    int aux_ra = 0;
    do
    {
        flush();
        scanf("%s", (p+qtd)->RA);
        flush();

        if (strlen((p+qtd)->RA) == 6)
        {
            int j;
            for (j = 0; j < 6; j++)
            {
                if (isdigit(*((p+qtd)->RA + j)) == 0)
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

    (p+qtd)->emprestado = 0;
    (p+qtd)->reservado = 0;

    int i;
    for (i = 0; i < 4; i++)
    {
        (p+qtd)->tabela[i].sigla = 'L';
    }
    system(clear);
    printf("\033[0;32m### Cadastro Realizado com sucesso!! ###\033[0m\n");
    printf("Nome:\t\033[0;36m%s\033[0;0m\t", (p+qtd)->nome);
    printf("RA: \t\033[0;36m%s\033[0;0m\n", (p+qtd)->RA);

    pause();
}

void consulta_total(aluno *p, int qtd)
{
    system(clear);
    int i;
    for(i = 0; i < qtd; i++)
    {
        printf("Nome:\t\033[0;36m%s\033[0;0m\t", (p+i)->nome);
        printf("RA: \t\033[0;36m%s\033[0;0m\n", (p+i)->RA);
        printf("Livros emprestados: \t\033[0;36m%i\033[0;0m", (p+i)->emprestado);
        
        int j; int regis = -1;
        for(j = 0; j < 4; j++)
        {
            if((p+i)->tabela[j].sigla == 'E') printf("\n\t- Reg: \033[0;36m%i\033[0;0m", (p+i)->tabela[j].reg);
            else if((p+i)->tabela[j].sigla == 'R') regis = (p+i)->tabela[j].reg;
        }

        printf("\nLivros reservados: \t\033[0;36m%i\033[0;0m", (p+i)->reservado);
        if(regis > 0) printf("\n\t- Reg: \033[0;36m%i\033[0;0m", regis);
        printf("\n\n");
    }
    pause();
}

void consulta_parcial(aluno *p, int qtd)
{
    system(clear);
    printf("\nDigite o RA do aluno:\t");
    int aux_ra = 0;
    char RA[7];
    do
    {
        flush();
        scanf("%s", RA);
        flush();

        if (strlen(RA) == 6)
        {
            int j;
            for (j = 0; j < 6; j++)
            {
                if (isdigit(*(RA + j)) == 0)
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

    int i; int flag = 0;
    for(i = 0; i < qtd; i++)
    {
        if(strcmp((p+i)->RA, RA) == 0)
        {
            printf("Nome:\t\033[0;36m%s\033[0;0m\t", (p+i)->nome);
            printf("RA: \t\033[0;36m%s\033[0;0m\n", (p+i)->RA);
            printf("Livros emprestados: \t\033[0;36m%i\033[0;0m", (p+i)->emprestado);
            
            int j; int regis = -1;
            for(j = 0; j < 4; j++)
            {
                if((p+i)->tabela[j].sigla == 'E') printf("\n\t- Reg: \033[0;36m%i\033[0;0m", (p+i)->tabela[j].reg);
                else if((p+i)->tabela[j].sigla == 'R') regis = (p+i)->tabela[j].reg;
            }

            printf("\nLivros reservados: \t\033[0;36m%i\033[0;0m", (p+i)->reservado);
            if(regis > 0) printf("\n\t- Reg: \033[0;36m%i\033[0;0m", regis);
            printf("\n\n");
            flag = 1;
            break; 
        }
    }
    if(flag == 0) printf("\nO aluno referente a esse RA não existe!");
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

