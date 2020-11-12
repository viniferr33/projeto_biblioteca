/* ### GRUPO 3 ###
Felipe Moraes Marcello                  RA: 
Vinicius Ferreira Gomes                 RA: 200603
Yuri Carlos Achnitz Batista Belinski    RA: 200262
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

int main(int argc, char const *argv[])
{

    return 0;
}

void cadastra_livro(livro *livros)
{
    static int registro = 0;

    
    livros->status->sigla = 'L';
}