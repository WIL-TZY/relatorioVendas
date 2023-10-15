#include <stdio.h>

// Esse programa vai montar o relatório de vendas e disponibilizar os dados para um terceiro programa que irá criar o relatório final.
// Não recebe parâmetros.

typedef struct {
    int id_vendedor;
    char nome[100];
    char cargo[20];
    int equipe;
    int id_venda;
    double valor_venda;
} Vendedor;

int main() {
    Vendedor vendedores[100];
    int num_vendedores = 0;
    int colunasCSV = 6;

    // Ler os dados dos vendedores a partir da entrada padrão (STDIN)
    /*
    while (scanf("%d", &vendedores[num_vendedores].id_vendedor) == colunasCSV) {
        num_vendedores++;
    }
    */

    char ch;

    // Lê o que recebeu de leitura.c na entrada padrão (STDIN)
    while ((ch = getchar()) != EOF) {
        //(DEBUG) Imprimindo o conteúdo recebido no console 
        // printf("%c", ch); // ------> retorna dados binários ao invés de texto >:c
        putchar(ch);
    }

    return 0;
}
