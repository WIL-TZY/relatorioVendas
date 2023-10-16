#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Esse programa vai montar o relatório de vendas e disponibilizar os dados para um terceiro programa que irá criar o relatório final.
// Não recebe parâmetros.

// Valores --- Comissão
const double COMISSAO_JUNIOR = 0.01;
const double COMISSAO_PLENO = 0.02;
const double COMISSAO_SENIOR = 0.03;
const double COMISSAO_GERENTE = 0.05;

typedef struct {
    int id_vendedor;
    char nomeVendedor[100];
    char cargo[20];
    int equipe;
    int id_venda;
    double valor_venda;
    double comissao;
} DefinaVenda;

// ------------------------------------ Protótipos das funções aqui ------------------------------------ //
double calcularTotalVendas(DefinaVenda venda[], int qtdVendas);
void ordenarVendedoresPorVendas(DefinaVenda venda[], int qtdVendas);
void gerarRelatorio(DefinaVenda venda[], int qtdVendas);
// ----------------------------------------------------------------------------------------------------- //

int main() {
    DefinaVenda venda[100];
    int linha = 0;
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
            // Preencher o array de venda com os dados do arquivo CSV
            while (token != NULL && col < colunasCSV) {
                if (col == 0) {
                    venda[linha].id_vendedor = atoi(token);
                } else if (col == 1) {
                    strncpy(venda[linha].nomeVendedor, token, sizeof(venda[linha].nomeVendedor) - 1);
                    venda[linha].nomeVendedor[sizeof(venda[linha].nomeVendedor) - 1] = '\0';
                } else if (col == 2) {
                    strncpy(venda[linha].cargo, token, sizeof(venda[linha].cargo) - 1);
                    venda[linha].cargo[sizeof(venda[linha].cargo) - 1] = '\0';
                } else if (col == 3) {
                    venda[linha].equipe = atoi(token);
                } else if (col == 4) {
                    venda[linha].id_venda = atoi(token);
                } else if (col == 5) {
                    venda[linha].valor_venda = atof(token);
                }
                token = strtok(NULL, ",");
                col++;
            }
                // Próxima linha (incrementa o vendedor)
                linha++;

                // Checagem de segurança
                if (linha >= 100) {
                    printf("Quantidade de venda excedida.\n");
                    return 1;
                }
        }
    }

    // ------------------------------------ USAR FUNÇÕES AQUI ------------------------------------ //
    
    // (DEBUG) Imprimindo os dados de cada struct
    for (int i = 0; i < linha; i++) {
        printf("Venda %d:\n", i + 1);
        printf("ID: %d\n", venda[i].id_vendedor);
        printf("Nome: %s\n", venda[i].nomeVendedor);
        printf("Cargo: %s\n", venda[i].cargo);
        printf("Equipe: %d\n", venda[i].equipe);
        printf("ID da venda: %d\n", venda[i].id_venda);
        printf("Valor da venda: %.2f\n", venda[i].valor_venda);
        printf("\n");
    }

        gerarRelatorio(venda, linha);


    return 0;
}

// ------------------------------------ CRIAR FUNÇÕES AQUI ------------------------------------ //


double calcularTotalVendas(DefinaVenda venda[], int qtdVendas) {
    double totalVendas = 0.0;
    for (int i = 0; i < qtdVendas; i++) {
        totalVendas += venda[i].valor_venda;
    }
    return totalVendas;
}

// Outra função parecida com a de cima só que por equipe (?)

void ordenarVendedoresPorVendas(DefinaVenda venda[], int qtdVendas) {
    // Dar uma olhada em algoritmos de ordenação??
    // Ou só comparar valor_venda de um com outro já dá?
}

void gerarRelatorio(DefinaVenda venda[], int qtdVendas) {
    // Calcular total de vendas
    double totalVendas = calcularTotalVendas(venda, qtdVendas);

    // Ordenar vendedores por vendas
    ordenarVendedoresPorVendas(venda, qtdVendas);

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
    printf("Nome\t\t\t\tCargo\t\tEquipe\t\tTotal de Vendas\t\tMaior DefinaVenda\t\tComissão\n");

    for (int i = 0; i < qtdVendas; i++) {
        // Formatar e escrever os detalhes para cada vendedor (usando tabs tava dando inconsistência)
        printf("%-30s %-20s %02d \t\tR$ %12.2f \tR$ %12.2f \tR$ %10.2f\n", 
            venda[i].nomeVendedor, 
            venda[i].cargo, 
            venda[i].equipe, 
            venda[i].valor_venda, 
            venda[i].valor_venda, 
            (venda[i].valor_venda * 0.03)
        );
    }
}
