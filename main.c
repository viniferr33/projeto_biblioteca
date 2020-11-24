/* ### GRUPO 3 ###
Felipe Moraes Marcello                  RA: 200370
Vinicius Ferreira Gomes                 RA: 200603
Yuri Carlos Achnitz Batista Belinski    RA: 200262
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// ## Esse trecho de código é executado durante a compilação ##
#if defined(_WIN32) || defined(_WIN64) // Testa se o SO é Windows
const char *clear = "cls";             // Define os comandos do sistema windows
#include <conio.h>
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

/*
Funções genericas do algoritmo
*/
void pause();
void flush();
char retorna_char();

/*
Funções relacionadas a manipulação da struct "Aluno"
*/
void aloca_aluno(aluno **p, int qtd);
void mostra_alunos(aluno *p, int qtd);
void cadastra_aluno(aluno *p);
void consulta_total(aluno *p, int qtd);
void consulta_parcial(aluno *p, int qtd);
int busca_aluno(aluno *p, int qtd);
int quantia_aluno();
void grava_aluno(aluno *p);

/*
Funções para a struct "livro"
*/
int quantia_livro();
void cadastra_livro(livro *livros, int qtd);
void gravar_livro(livro *livros);
void consulta_livro(livro *livros, int qtd);
int busca_livro(livro *livros, int qtd);
int compara_string(char *principal, char *outra);
void status_livro(struct info_aluno *status);
void aloca_livro(livro **p, int qtd);

/*
Funções relacionadas a emprestimo de livros
*/
void empresta(aluno *p, int qtd_a, livro *livros, int qtd_l);

// ## MAIN ##
int main(int argc, char const *argv[])
{
    char opt = '\0';
    char op = '\0';

    aluno *alunos = NULL;
    int qtd_a;
    aloca_aluno(&alunos, 1);

    int qtd_livro;
    livro *livros = NULL;
    aloca_livro(&livros, 1);

    do
    {
        system(clear);

        printf("Ola, essa e a \033[0;35mBIBLIOTECA\033[0m\n\nVoce tem tres opcoes:\n[1] - Trabalhar com alunos\n[2] - Trabalhar com livros\n[0] - Sair");
        opt = retorna_char();

        switch (opt)
        {
        case '0':
            break;

        case '1':
            do
            {
                system(clear);
                printf("ALUNOS\n\n[1] - Adicionar\n[2] - Pesquisa total\n[3] - Pesquisa Parcial\n[0] - Sair");
                op = retorna_char();

                switch (op)
                {
                case '0':
                    break;

                case '1':
                    cadastra_aluno(alunos);
                    qtd_a++;
                    break;

                case '2':
                    qtd_a = quantia_aluno();
                    consulta_total(alunos, qtd_a);
                    break;

                case '3':
                    qtd_a = quantia_aluno();
                    consulta_parcial(alunos, qtd_a);
                    break;

                default:
                    printf("\n\n\033[0;31mDigite uma opcao valida.\033[0m\n\n");
                    pause();
                    break;
                }
            } while (op != '0'); //switch dos alunos
            break;

        case '2':
            do
            {
                system(clear);
                printf("LIVROS\n\n[1] - Cadastrar livros\n[2] - Consultar livros\n[0] - Sair");

                op = retorna_char();

                switch (op)
                {
                case '0':
                    break;

                case '1':
                    qtd_livro = quantia_livro();
                    cadastra_livro(livros, qtd_livro);
                    break;

                case '2':
                    qtd_livro = quantia_livro();
                    consulta_livro(livros, qtd_livro);
                    break;

                default:
                    printf("\n\n\033[0;31mDigite uma opcao valida.\033[0m\n\n");
                    pause();
                    break;
                }
            } while (op != '0'); //switch dos livros
            break;

        case '3':
            // ##### DEBUG #####
            empresta(alunos, quantia_aluno(), livros, quantia_livro());
            break;

        default:
            printf("\n\n\033[0;31mDigite uma opcao valida.\033[0m\n\n");
            pause();
            break;
        }
    } while (opt != '0'); //switch de tudo

    return 0;
} //MAIN

void empresta(aluno *alunos, int qtd_a, livro *livros, int qtd_l)
{
    int pos_a, pos_l; //POSIÇÃO DO PONTEIRO DENTRO DOS ARQUIVOS

    system(clear);
    qtd_a = quantia_aluno();
    pos_a = busca_aluno(alunos, qtd_a);

    if (pos_a == -1)
        printf("\n\nO aluno informado nao foi encontrado no sistema! Verifique se o mesmo foi cadastrado anteriormente!\n\n");
    else if (alunos->emprestado > 3 && alunos->reservado == 1)
        print("\n\nO aluno informado ja possui o numero maximo de emprestimos e reservas!\n\n");

    else
    {
        qtd_l = quantia_livro();
        pos_l = busca_livro(livros, qtd_l);

        if (pos_l == -1)
            printf("\n\nO livro informado nao foi encontrado no sistema! Verifique se o mesmo foi cadastrado anteriormente!\n\n");

        else
        {
            // ## VALIDAÇÕES ##
            if ((livros->status + 0)->sigla == 'L')
            {
                //Primeiro status ta livre -> EMPRESTAR
                (livros->status + 0)->sigla = 'E';
                strcpy((livros->status + 0)->RA, alunos->RA);
                alunos->emprestado++;
                (alunos->tabela + alunos->emprestado)->reg = livros->reg;
                (alunos->tabela + alunos->emprestado)->sigla = 'E';
            }
            else
            {
                if ((livros->status + 1)->sigla == 'R')
                    printf("O livro encontra-se indisponivel até dia:\n\n");
                else
                {
                    //Não tinha nada no segundo status -> RESERVAR
                    if (alunos->reservado == 1)
                        printf("\n\nO aluno ja possui o numero maximo de reservas!\n\n");
                    else
                    {
                        (livros->status + 1)->sigla = 'R';
                        strcpy((livros->status + 1)->RA, alunos->RA);
                        alunos->reservado++;
                        (alunos->tabela + 3)->reg = livros->reg;
                        (alunos->tabela + 3)->sigla = 'R';
                    }
                    
                }
            }
        }
    }
    //
    //
    //  INSIRA UMA FUNÇÂO DE EDITAR OS ARQUIVOS AQUI
    //
    //
    pause();
}

/*
Aloca Aluno - Função da Struct Aluno
 - Realiza alocação dinamica da struct aluno.
*/
void aloca_aluno(aluno **p, int qtd)
{
    if ((*p = (aluno *)realloc(*p, qtd * sizeof(aluno))) == NULL)
    {
        printf("\033[0;31mErro de alocação!\033[0m");
        pause();
        exit(1);
    }
}

/*
Cadastra Aluno - Função da Struct Aluno
 - Cadastra um novo aluno na lista de alunos
*/
void cadastra_aluno(aluno *p)
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
        fgets(p->RA, 7, stdin);
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
        (p->tabela + i)->sigla = 'L';
    }
    system(clear);
    printf("\033[0;32m### Cadastro Realizado com sucesso!! ###\033[0m\n\n");
    printf("Nome:\t\033[0;36m%s\033[0;0m\t", p->nome);
    printf("RA: \t\033[0;36m%s\033[0;0m\n\n", p->RA);

    grava_aluno(p);
    pause();
}

/*
Consulta Total - Função da Struct Aluno
 - Imprime todos os alunos da lista de alunos
*/
void consulta_total(aluno *p, int qtd)
{

    FILE *fl = NULL;
    int i, j, regis = -1;
    system(clear);

    if ((fl = fopen("aluno.bin", "rb")) == NULL)
        printf("Nao existem alunos no cadastro!\n\n");

    else
    {
        for (i = 0; i < qtd; i++)
        {
            fseek(fl, i * sizeof(aluno), 0);
            fread(p, sizeof(aluno), 1, fl);

            printf("Nome:\t\033[0;36m%s\033[0;0m\t", p->nome);
            printf("RA: \t\033[0;36m%s\033[0;0m\n", p->RA);
            printf("Livros emprestados: \t\033[0;36m%i\033[0;0m", p->emprestado);

            for (j = 0; j < 4; j++)
            {
                if ((p->tabela + j)->sigla == 'E')
                    printf("\n\t- Reg: \033[0;36m%i\033[0;0m", (p->tabela + j)->reg);
                else if ((p->tabela + j)->sigla == 'R')
                    regis = (p->tabela + j)->reg;
            }

            printf("\nLivros reservados: \t\033[0;36m%i\033[0;0m", p->reservado);
            if (regis > 0)
                printf("\n\t- Reg: \033[0;36m%i\033[0;0m", regis);
            printf("\n\n");
        }
    }
    fclose(fl);
    pause();
}

/*
Consulta Parcial - Função da Struct Aluno
 - Busca e imprime determinado RA na lista de alunos.
*/
void consulta_parcial(aluno *p, int qtd)
{
    FILE *fl = NULL;
    system(clear);

    if ((fl = fopen("aluno.bin", "rb")) == NULL)
        printf("Nao existem alunos no cadastro!\n\n");

    else
    {
        printf("Digite o RA do aluno:\t");
        int aux_ra = 0;
        char RA[7];
        do
        {
            fgets(RA, 7, stdin);
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

        int i;
        int flag = 0;
        for (i = 0; i < qtd; i++)
        {
            fseek(fl, i * sizeof(aluno), 0);
            fread(p, sizeof(aluno), 1, fl);

            if (strcmp(p->RA, RA) == 0)
            {
                printf("\nNome:\t\033[0;36m%s\033[0;0m\t", p->nome);
                printf("RA: \t\033[0;36m%s\033[0;0m\n", p->RA);
                printf("Livros emprestados: \t\033[0;36m%i\033[0;0m", p->emprestado);

                int j;
                int regis = -1;
                for (j = 0; j < 4; j++)
                {
                    if ((p->tabela + j)->sigla == 'E')
                        printf("\n\t- Reg: \033[0;36m%i\033[0;0m", (p->tabela + j)->reg);
                    else if ((p->tabela + j)->sigla == 'R')
                        regis = (p->tabela + j)->reg;
                }

                printf("\nLivros reservados: \t\033[0;36m%i\033[0;0m", p->reservado);
                if (regis > 0)
                    printf("\n\t- Reg: \033[0;36m%i\033[0;0m", regis);
                printf("\n\n");
                flag = 1;
                break;
            }
        }
        if (flag == 0)
            printf("\nO aluno referente a esse RA nao existe!\n\n");
    }
    fclose(fl);
    pause();
}

/*
Busca Aluno - Função da Struct Aluno
  - Busca um determinado aluno pelo RA no arquivo 'aluno.bin' e retorna sua posição
*/
int busca_aluno(aluno *p, int qtd)
{
    FILE *fl = NULL;
    system(clear);

    if ((fl = fopen("aluno.bin", "rb")) == NULL)
    {
        printf("Nao existem alunos no cadastro!\n\n");
        return -1;
    }

    else
    {
        printf("Digite o RA do aluno:\t");
        int aux_ra = 0;
        char RA[7];
        do
        {
            fgets(RA, 7, stdin);
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

        int i;
        int flag = 0;
        for (i = 0; i < qtd; i++)
        {
            fseek(fl, i * sizeof(aluno), 0);
            fread(p, sizeof(aluno), 1, fl);

            if (strcmp(p->RA, RA) == 0)
            {
                printf("\nNome:\t\033[0;36m%s\033[0;0m\t", p->nome);
                printf("RA: \t\033[0;36m%s\033[0;0m\n", p->RA);
                printf("Livros emprestados: \t\033[0;36m%i\033[0;0m", p->emprestado);

                int j;
                int regis = -1;
                for (j = 0; j < 4; j++)
                {
                    if ((p->tabela + j)->sigla == 'E')
                        printf("\n\t- Reg: \033[0;36m%i\033[0;0m", (p->tabela + j)->reg);
                    else if ((p->tabela + j)->sigla == 'R')
                        regis = (p->tabela + j)->reg;
                }

                printf("\nLivros reservados: \t\033[0;36m%i\033[0;0m", p->reservado);
                if (regis > 0)
                    printf("\n\t- Reg: \033[0;36m%i\033[0;0m", regis);
                printf("\n\n");
                flag = 1;
                return i;
            }
        }
        if (flag == 0)
            return -1;
    }
    fclose(fl);
    pause();
}

/*
Quantia Aluno - Função da Struct Aluno
 - Retorna a quantidade de estruturas dentro do arquivo 'aluno.bin'
*/
int quantia_aluno()
{
    FILE *arq = NULL; // Ponteiro para arquivo
    int qtd;
    if ((arq = fopen("aluno.bin", "rb")) == NULL) // Testa se o arquivo existe
        return 0;

    else
    {
        fseek(arq, 0, 2);                 // Movimenta o ponteiro dentro do arquivo
        qtd = ftell(arq) / sizeof(aluno); // Retorna o tamanho do arquivo até o ponteiro
        fclose(arq);
        return qtd;
    }
}

/*
Grava Aluno - Função da Struct Aluno
 - Salva a Struct aluno dada no ponteiro referente no arquivo 'aluno.bin'
*/
void grava_aluno(aluno *p)
{
    FILE *fl = NULL;
    if ((fl = fopen("aluno.bin", "ab")) == NULL)
    {
        printf("\033[0;31mErro ao abrir arquivo de alunos!!\033[0m");
        pause();
    }
    else
    {
        fwrite(p, sizeof(aluno), 1, fl);
    }
    fclose(fl);
}

/*
Quantifica a quantia de livros existente no arquivo de livros.
*/
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

/*
É a preparação de terreno para gravar um livro no arquivo de livros.
*/
void cadastra_livro(livro *livros, int qtd)
{
    system(clear);

    livros->reg = qtd;

    printf("CADASTRO DE LIVROS\n\nRegistro de livro: %i", qtd);

    printf("\n\nInsira o titulo do livro: ");
    gets(livros->titulo);
    flush();

    printf("Insira o autor do livro: ");
    gets(livros->autor);
    flush();

    livros->status->sigla = 'L';

    gravar_livro(livros);
}

/*
É a gravação de fato no arquivo de livros.
*/
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

/*
Consulta o arquivo de livros de diversas formas, podendo procurar informações específicas.
*/
void consulta_livro(livro *livros, int qtd)
{
    FILE *fptr = NULL;
    int i, achou;
    char op, status, titulo[80];

    if ((fptr = fopen("livros.bin", "rb")) == NULL)
    {
        printf("\n\nNao ha arquivo de livros!\n\n");
        pause();
    }
    else
    {
        do
        {
            achou = 0;
            system(clear);
            printf("CONSULTA DE LIVROS\n\n[1] - Todos os livros\n[2] - Por status\n[3] - Por titulo\n[0] - Sair");

            op = retorna_char();

            switch (op)
            {
            case '0':
                break;

            case '1': //todos os livros
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

            case '2': //livros por status
                printf("\n\nDigite o status desejado (\033[0;32mL - Livre\033[0m, \033[0;31mE - Emprestado\033[0m, \033[0;33mR - Reservado\033[0m): ");

                scanf("%c", &status);
                flush();

                for (i = 0; i < qtd - 1; i++)
                {
                    fseek(fptr, i * sizeof(livro), 0);
                    fread(livros, sizeof(livro), 1, fptr);

                    if (tolower(livros->status->sigla) == tolower(status))
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

            case '3': //livros por titulo
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
                printf("\n\n\033[0;31mDigite uma opcao valida.\033[0m\n\n");
                pause();
                break;
            }
        } while (op != '0');

        fclose(fptr);
    } //funcionalidade do consulta_livro
} //fim do consulta_livro

/*
Busca determinado livro pelo titulo e armazena no ponteiro fornecido
*/
int busca_livro(livro *livros, int qtd)
{
    FILE *fptr = NULL;
    int i, achou;
    char titulo[80];

    if ((fptr = fopen("livros.bin", "rb")) == NULL)
    {
        printf("\n\nNao ha arquivo de livros!\n\n");
        pause();
        return -1;
    }
    else
    {
        printf("\n\nDigite o titulo desejado: ");
        fgets(titulo, 80, stdin);
        flush();
        *(titulo + strlen(titulo) - 1) = '\0';

        for (i = 0; i < qtd; i++)
        {
            fseek(fptr, i * sizeof(livro), 0);
            fread(livros, sizeof(livro), 1, fptr);

            if (compara_string(titulo, livros->titulo) == 0)
            {
                printf("\n\nRegistro de livro: %i\n\nTitulo: %s\nAutor: %s\n\n", livros->reg, livros->titulo, livros->autor);
                status_livro(livros->status);
                achou = 1;
                return i;
            }
        }

        if (achou == 0)
            return -1;
    }
    fclose(fptr);
    pause();
}

/*
Compara duas strings ignorando maiusculas e minusculas.
Vale-se notar que a ênfase está no parâmetro "principal".
*/
int compara_string(char *principal, char *outra)
{
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

/*
Acessa e trabalha com o status de um livro.
*/
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

/*
Alocação dinâmica para o ponteiro de struct livro.
*/
void aloca_livro(livro **p, int qtd)
{
    if ((*p = (livro *)realloc(*p, qtd * sizeof(livro))) == NULL)
    {
        printf("\n\n\033[0;31mErro para alocar livro\033[0m\n\n");
        pause();
        exit(1);
    }
}

/*
Retorna um char, no Windows usa-se o getch(), no Linux é um scanf() normal.
*/
char retorna_char()
{
    flush();
    char op;
    flush();
// ## Esse trecho de código é executado durante a compilação ##
#if defined(_WIN32) || defined(_WIN64) // Testa se o SO é Windows
    op = getch();
    return op;
#else
#ifdef __linux // Testa se o SO é Linux
    printf("\n\nInsira a operacao desejada: ");
    scanf("%c", &op);
    flush();
    return op;
#endif
#endif
}

/*
Basicamente a função padrão system("pause"), porém com uma alternativa para Linux.
*/
void pause()
{
// ## Esse trecho de código é executado durante a compilação ##
#if defined(_WIN32) || defined(_WIN64) // Testa se o SO é Windows
    system("pause");
#else
#ifdef __linux // Testa se o SO é Linux
    printf("Pressione ENTER para continuar. . .\n");
    getchar();
#endif
#endif
}

/*
Função para limpar o buffer do teclado para ambos Windows e Linux.
*/
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