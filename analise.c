#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Esse programa vai montar o relatório de vendas e disponibilizar os dados para um terceiro programa que irá criar o relatório final.
// Não recebe parâmetros.

// ------------------------------------ Protótipos das funções aqui ------------------------------------ //

// ----------------------------------------------------------------------------------------------------- //
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
    int quantidadeVendedores = 0;
    int colunasCSV = 6;
    char bufferLinhas[100]; // Esse buffer vai ser usado temporariamente para armazenar os dados pegos do STDIN
    int contadorDeChar = 0;
    char ch;

    // Lê de linha em linha
    while ((ch = getchar()) != EOF) {
        // Quando encontrar uma quebra de linha, termina a linha com '\0' 
        if (ch != '\n') {
            // Armazenar o caractere no buffer
            bufferLinhas[contadorDeChar] = ch;
            contadorDeChar++;
        } else { // Passar de linha e armazena a linha atual no buffer
            bufferLinhas[contadorDeChar] = '\0';
            contadorDeChar = 0;

            // Armazenar cada informação separada por vírgulas dentro de token
            char *token = strtok(bufferLinhas, ",");
            int col = 0;
            // Preencher o array de vendedores com os dados do arquivo CSV
            while (token != NULL && col < colunasCSV) {
                if (col == 0) {
                    vendedores[quantidadeVendedores].id_vendedor = atoi(token);
                } else if (col == 1) {
                    strncpy(vendedores[quantidadeVendedores].nome, token, sizeof(vendedores[quantidadeVendedores].nome) - 1);
                    vendedores[quantidadeVendedores].nome[sizeof(vendedores[quantidadeVendedores].nome) - 1] = '\0';
                } else if (col == 2) {
                    strncpy(vendedores[quantidadeVendedores].cargo, token, sizeof(vendedores[quantidadeVendedores].cargo) - 1);
                    vendedores[quantidadeVendedores].cargo[sizeof(vendedores[quantidadeVendedores].cargo) - 1] = '\0';
                } else if (col == 3) {
                    vendedores[quantidadeVendedores].equipe = atoi(token);
                } else if (col == 4) {
                    vendedores[quantidadeVendedores].id_venda = atoi(token);
                } else if (col == 5) {
                    vendedores[quantidadeVendedores].valor_venda = atof(token);
                }
                token = strtok(NULL, ",");
                col++;
            }
                // Próxima linha (incrementa o vendedor)
                quantidadeVendedores++;

                // Checagem de segurança
                if (quantidadeVendedores >= 100) {
                    printf("Quantidade de vendedores excedida.\n");
                    return 1;
                }
        }
    }

    // ------------------------------------ USAR FUNÇÕES AQUI ------------------------------------ //
    
    // (DEBUG) Imprimindo os dados de cada vendedor, agora armazenados na struct
    for (int i = 0; i < quantidadeVendedores; i++) {
        printf("Vendedor %d:\n", i + 1);
        printf("ID: %d\n", vendedores[i].id_vendedor);
        printf("Nome: %s\n", vendedores[i].nome);
        printf("Cargo: %s\n", vendedores[i].cargo);
        printf("Equipe: %d\n", vendedores[i].equipe);
        printf("ID da venda: %d\n", vendedores[i].id_venda);
        printf("Valor da venda: %.2f\n", vendedores[i].valor_venda);
        printf("\n");
    }

    /*
    // Lê o que recebeu de leitura.c na entrada padrão (STDIN)
    while ((ch = getchar()) != EOF) {
        //(DEBUG) Imprimindo o conteúdo recebido no console 
        // printf("%c", ch); // ------> retorna dados binários ao invés de texto >:c
        putchar(ch);
    }
    */
   
    return 0;
}

// ------------------------------------ CRIAR FUNÇÕES AQUI ------------------------------------ //
