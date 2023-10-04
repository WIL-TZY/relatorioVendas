#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id_vendedor;
    char* nome;
    char* cargo;
    int equipe;
    int id_venda;
    double valor_venda;
} vendedor;


int main() {
    printf("Ola\n");
    char ch;
    vendedor fulano;
    //fulano.id_vendedor =

    FILE* dados_leitura = fopen("vendas.csv", "r");
    FILE* dados_escrita = fopen("relatorio.txt", "w");

    while (!feof(dados_leitura)) {
        ch = fgetc(dados_leitura);
        printf("%c", ch);

        fputc(ch, dados_escrita);
    }
    


}

