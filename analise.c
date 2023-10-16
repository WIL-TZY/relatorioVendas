#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

// ------------------------------------ Protótipos das funções aqui ------------------------------------ //
double calcularTotalVendas(Vendedor vendedores[], int quantidadeVendedores);
void ordenarVendedoresPorVendas(Vendedor vendedores[], int quantidadeVendedores);
void gerarRelatorio(Vendedor vendedores[], int quantidadeVendedores);
// ----------------------------------------------------------------------------------------------------- //

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

        gerarRelatorio(vendedores, quantidadeVendedores);


    return 0;
}

// ------------------------------------ CRIAR FUNÇÕES AQUI ------------------------------------ //


double calcularTotalVendas(Vendedor vendedores[], int quantidadeVendedores) {
    double totalVendas = 0.0;
    for (int i = 0; i < quantidadeVendedores; i++) {
        totalVendas += vendedores[i].valor_venda;
    }
    return totalVendas;
}

// Outra função parecida com a de cima só que por equipe (?)

void ordenarVendedoresPorVendas(Vendedor vendedores[], int quantidadeVendedores) {
    // Dar uma olhada em algoritmos de ordenação??
    // Ou só comparar valor_venda de um com outro já dá?
}

void gerarRelatorio(Vendedor vendedores[], int quantidadeVendedores) {
    // Calcular total de vendas
    double totalVendas = calcularTotalVendas(vendedores, quantidadeVendedores);

    // Ordenar vendedores por vendas
    ordenarVendedoresPorVendas(vendedores, quantidadeVendedores);

    // Títulos
    printf("------ Relatório de Vendas ------\n");
    printf("Total de Vendas da Empresa: R$ %.2lf\n", totalVendas);
    printf("\n\n");
    
    // Total de vendas por equipe
    // ...

    // Gerente da equipe vencedora
    // ...

    // Melhor vendedor
    // ...

    // Lista de vendedores
    printf("Lista de Vendedores (por vendas decrescentes):\n");
    printf("Nome\t\t\t\tCargo\t\tEquipe\t\tTotal de Vendas\t\tMaior Venda\t\tComissão\n");

    for (int i = 0; i < quantidadeVendedores; i++) {
        // Formatar e escrever os detalhes para cada vendedor (usando tabs tava dando inconsistência)
        printf("%-30s %-20s %02d \t\tR$ %12.2f \tR$ %12.2f \tR$ %10.2f\n", 
            vendedores[i].nome, 
            vendedores[i].cargo, 
            vendedores[i].equipe, 
            vendedores[i].valor_venda, 
            vendedores[i].valor_venda, 
            (vendedores[i].valor_venda * 0.03)
        );
    }
}
