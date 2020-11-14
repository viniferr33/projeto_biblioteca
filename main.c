/* ### GRUPO 3 ###
Felipe Moraes Marcello                  RA: 
Vinicius Ferreira Gomes                 RA: 200603
Yuri Carlos Achnitz Batista Belinski    RA: 200262
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

// ## Esse trecho de código é executado durante a compilação ##
#if defined(_WIN32) || defined(_WIN64) // Testa se o SO é Windows
const char *clear = "cls";             // Define os comandos do sistema windows
#else
#ifdef __linux // Testa se o SO é Linux
const char *clear = "clear"; // Define os comandos do sistema linux
#endif
#endif

struct info_aluno
{
    char sigla;  //'L' - livre, 'E' - emprestado, 'R' - reservado (data da retirada -1 dia depois de devolver)
    char RA[7];  //
    int dia_ret; //dia max = 31
    int mes_ret; //mes fev = 28
    int dia_dev; //abril, junho, setembro, novembro = 30 dias
    int mes_dev; //o resto = 31
};

typedef struct livro
{
    int reg; //gerado automaticamente
    char titulo[80];
    char autor[80];
    struct info_aluno status[2];
} livro;

int main(int argc, char const *argv[])
{
    system(clear);
    livro *livros = NULL;
    aloca_livro(&livros, 1);
    int qtd_livro = quantia_livro();

    //cadastra_livro(livros, qtd_livro);

    consulta_livro(livros, qtd_livro);

    return 0;
}

int quantia_livro()
{
    FILE *fptr = NULL;
    long int cont = 1;

    if ((fptr = fopen("livros.bin", "rb")) == NULL)
        return cont;
    else
    {
        fseek(fptr, 0, 2);
        cont = ftell(fptr) / sizeof(livro);
        fclose(fptr);
        return (cont + 1);
    }
}

void cadastra_livro(livro *livros, int qtd)
{
    livros->reg = qtd;

    printf("Registro de livro: %i", qtd);

    printf("\n\nInsira o titulo do livro: ");
    gets(livros->titulo);
    flush();

    printf("Insira o autor do livro: ");
    gets(livros->autor);
    flush();

    livros->status->sigla = 'L';

    gravar_livro(livros);
}

void gravar_livro(livro *livros)
{
    FILE *fptr = NULL;

    if ((fptr = fopen("livros.bin", "ab")) == NULL)
    {
        printf("\n\n\033[0;31mErro ao abrir arquivo de livros!\033[0m\n\n");
        pause();
    }
    else
        fwrite(livros, sizeof(livro), 1, fptr);

    fclose(fptr);
}

void consulta_livro(livro *livros, int qtd)
{
    FILE *fptr = NULL;
    int i, achou = 0;
    char op, status, titulo[80];

    if ((fptr = fopen("livros.bin", "rb")) == NULL)
        printf("\n\n\033[0;31mErro ao abrir arquivo de livros!\033[0m\n\n");
    else
    {
        printf("\n\nCONSULTA DE LIVROS\n\n[1] Todos os livros\n[2] Por status\n[3] Por titulo");
        flush();
        op = getch();
        ;
        flush();

        switch (op)
        {
        case '1':
            for (i = 0; i < qtd - 1; i++)
            {
                fseek(fptr, i * sizeof(livro), 0);
                fread(livros, sizeof(livro), 1, fptr);

                printf("\n\nRegistro de livro: %i\n\nTitulo: %s\nAutor: %s\n\n", livros->reg, livros->titulo, livros->autor);
                status_livro(livros->status);
            }

            printf("\n\n");
            pause();
            break;

        case '2':
            printf("\n\nDigite o status desejado (\033[0;32mL - Livre\033[0m, \033[0;31mE - Emprestado\033[0m, \033[0;33mR - Reservado\033[0m): ");

            scanf("%c", &status);
            flush();

            for (i = 0; i < qtd - 1; i++)
            {
                fseek(fptr, i * sizeof(livro), 0);
                fread(livros, sizeof(livro), 1, fptr);

                if (livros->status->sigla == status)
                {
                    printf("\n\nRegistro de livro: %i\n\nTitulo: %s\nAutor: %s\n\n", livros->reg, livros->titulo, livros->autor);
                    status_livro(livros->status);
                    achou = 1;
                }
            }

            if (achou == 0)
            {
                printf("\n\nNenhum livro encontrado.");
            }

            printf("\n\n");
            pause();
            break;

        case '3':
            printf("\n\nDigite o titulo desejado: ");
            gets(titulo);
            flush();

            for (i = 0; i < qtd - 1; i++)
            {
                fseek(fptr, i * sizeof(livro), 0);
                fread(livros, sizeof(livro), 1, fptr);

                if (compara_string(titulo, livros->titulo) == 0)
                {
                    printf("\n\nRegistro de livro: %i\n\nTitulo: %s\nAutor: %s\n\n", livros->reg, livros->titulo, livros->autor);
                    status_livro(livros->status);
                    achou = 1;
                }
            }

            if (achou == 0)
            {
                printf("\n\nNenhum livro encontrado.");
            }

            printf("\n\n");
            pause();
            break;

        default:
            break;
        }

        fclose(fptr);
    } //funcionalidade do consulta_livro
} //fim do consulta_livro

int compara_string(char *principal, char *outra) //compara duas strings ignorando maiusculas e minusculas
{                                                //vale-se notar que a enfase está no parâmetro "principal"
    int i;

    if (strlen(principal) != strlen(outra))
        return 1;

    for (i = 0; i < strlen(principal); i++)
    {
        if (tolower(*(principal + i)) != tolower(*(outra + i)))
            return 1;
    }

    return 0;
}

void status_livro(struct info_aluno *status)
{
    if (status->sigla == 'L')
    {
        printf("Status: \033[0;32mLivre\033[0m\n");
    }

    if (status->sigla == 'E')
    {
        printf("Status: \033[0;31mEmprestado\033[0m\n");
    }

    if (status->sigla == 'R')
    {
        printf("Status: \033[0;33mReservado3[0m\n");
    }
}

void aloca_livro(livro **p, int qtd) //alocação padrão para o ponteiro de livros
{
    if ((*p = (livro *)realloc(*p, qtd * sizeof(livro))) == NULL)
    {
        printf("\n\n\033[0;31mErro para alocar livro\033[0m\n\n");
        pause();
        exit(1);
    }
}

void pause()
{
    printf("Pressione qualquer tecla para continuar. . .");
    flush();
    getch();
    flush();
}

void flush()
{
// ## Esse trecho de código é executado durante a compilação ##
#if defined(_WIN32) || defined(_WIN64) // Testa se o SO é Windows
    fflush(stdin);
#else
#ifdef __linux // Testa se o SO é Linux
    __fpurge(stdin);
#endif
#endif
}