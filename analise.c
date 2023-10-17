#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Esse programa vai montar o relatório de vendas e disponibilizar os dados para um terceiro programa que irá criar o relatório final.
// Não recebe parâmetros.

#define MAX 100

// Valores --- Comissão
const double COMISSAO_JUNIOR = 0.01;
const double COMISSAO_PLENO = 0.02;
const double COMISSAO_SENIOR = 0.03;
const double COMISSAO_GERENTE = 0.05;

// Tô usando snake case só pras variáveis das structs, ok?
typedef struct {
    int id_vendedor;
    char nome_vendedor[MAX];
    char cargo[20];
    int equipe;
    int id_venda;
    double valor_venda;
    double comissao;
} DefinaVenda;

typedef struct {
    int equipe;
    double total_vendas;
    char nome_gerente[MAX];
} DefinaVendasDaEquipe;

// ------------------------------------ Protótipos das funções aqui ------------------------------------ //
double calcularTotalVendas(DefinaVenda venda[], int qtdVendas);
void ordenarVendedoresPorVendas(DefinaVenda venda[], int qtdVendas);
void gerarRelatorio(DefinaVenda venda[], int qtdVendas);
// ----------------------------------------------------------------------------------------------------- //

int main() {
    DefinaVenda venda[MAX];
    DefinaVendasDaEquipe vendasDaEquipe[MAX];
    int linha = 0;
    int colunasCSV = 6;
    char bufferLinhas[MAX]; // Esse buffer vai ser usado temporariamente para armazenar os dados pegos do STDIN
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
                    strncpy(venda[linha].nome_vendedor, token, sizeof(venda[linha].nome_vendedor) - 1);
                    venda[linha].nome_vendedor[sizeof(venda[linha].nome_vendedor) - 1] = '\0';
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

                // --------------------------------------- ACHANDO O GERENTE --------------------------------------- //
                // Processa apenas vendas com valor maior do que zero
                if (venda[linha].valor_venda > 0.0) { 
                    // Verifica se o cargo indica um gerente
                    if (strcmp(venda[linha].cargo, "gerente") == 0) {
                        // Armazena o nome do gerente
                        strcpy(vendasDaEquipe[venda[linha].equipe - 1].nome_gerente, venda[linha].nome_vendedor);
                    }

                    // Próxima linha (incrementa a venda)
                    linha++;
                }

                // Checagem de segurança
                if (linha >= MAX) {
                    printf("Quantidade de venda excedida.\n");
                    return 1;
                }
        }
    }

    // ------------------------------------ USAR FUNÇÕES AQUI ------------------------------------ //
    
    gerarRelatorio(venda, linha);

    // ------------------------------- Total de vendas por equipe -------------------------------- //
    // Inicializando as variáveis da struct
    for (int i = 0; i < MAX; i++) {
        vendasDaEquipe[i].equipe = i + 1;
        vendasDaEquipe[i].total_vendas = 0.0;
    }

    // Iterando de novo cada linha p/ calcular o total de vendas de cada equipe
    for (int i = 0; i < linha; i++) {
        int indiceEquipe = venda[i].equipe - 1; 
        vendasDaEquipe[indiceEquipe].total_vendas += venda[i].valor_venda;
    }

    printf("\n");
    printf("Total de Vendas por Equipe (do maior para o menor):\n");
    for (int i = 0; i < MAX; i++) { // Loop through the array of teams
        if (vendasDaEquipe[i].total_vendas > 0.0) {
            printf("Equipe %02d - Vendas: R$ %.2lf\n", vendasDaEquipe[i].equipe, vendasDaEquipe[i].total_vendas);
        }
    }

    // ------------------------------- Gerente do time vencedor -------------------------------- //
    int indiceTimeVencedor = -1;
    double maiorVendaDaEquipe = 0.0;
    char nomeGerenteTimeVencedor[MAX]; // Variável que será usada para armazenar o nome do gerente

    // Iterando o array de times
    for (int i = 0; i < MAX; i++) { 
        if (vendasDaEquipe[i].total_vendas > maiorVendaDaEquipe) {
            maiorVendaDaEquipe = vendasDaEquipe[i].total_vendas;
            indiceTimeVencedor = i;

            // Iterando o array de vendas para encontrar o nome do gerente
            for (int j = 0; j < linha; j++) {
                if (venda[j].equipe == (i + 1)) {
                    strcpy(nomeGerenteTimeVencedor, venda[j].nome_vendedor);
                    break;
                }
            }
        }
    }

    if (indiceTimeVencedor != -1) {
        printf("Gerente da Equipe Vencedora: %s\n", vendasDaEquipe[indiceTimeVencedor].nome_gerente);
    } else {
        printf("Erro: Nenhum time encontrado.\n");
    }

    // ------------------------------- Melhor vendedor(a) -------------------------------- //

    int indiceMelhorVendedor = -1;
    double maiorVenda = 0.0;

    // Iterando o array das vendas
    for (int i = 0; i < linha; i++) {
        if (venda[i].valor_venda > maiorVenda) {
            maiorVenda = venda[i].valor_venda;
            indiceMelhorVendedor = i;
        }
    }

    if (indiceMelhorVendedor != -1) {
        printf("Melhor vendedor(a): %s\n", venda[indiceMelhorVendedor].nome_vendedor);
    } else {
        printf("Erro: Nenhum(a) vendedor(a) encontrado(a).\n");
    }

    return 0;
}

// ------------------------------------ CRIAR FUNÇÕES AQUI ------------------------------------ //

double calcularTotalVendas(DefinaVenda venda[], int qtdVendas) {
    double total_vendas = 0.0;
    for (int i = 0; i < qtdVendas; i++) {
        total_vendas += venda[i].valor_venda;
    }
    return total_vendas;
}

void ordenarVendedoresPorVendas(DefinaVenda venda[], int qtdVendas) {
    // Dar uma olhada em algoritmos de ordenação??
    // Ou só comparar valor_venda de um com outro já dá?
}

void gerarRelatorio(DefinaVenda venda[], int qtdVendas) {
    // Calcular total de vendas
    double total_vendas = calcularTotalVendas(venda, qtdVendas);

    // Ordenar vendedores por vendas
    ordenarVendedoresPorVendas(venda, qtdVendas);

    // Títulos
    printf("------ Relatório de Vendas ------\n");
    printf("Total de Vendas da Empresa: R$ %.2lf\n", total_vendas);
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

    for (int i = 0; i < qtdVendas; i++) {
        // Formatar e escrever os detalhes para cada vendedor (usando tabs tava dando inconsistência)
        printf("%-30s %-20s %02d \t\tR$ %12.2f \tR$ %12.2f \tR$ %10.2f\n", 
            venda[i].nome_vendedor, 
            venda[i].cargo, 
            venda[i].equipe, 
            venda[i].valor_venda, 
            venda[i].valor_venda, 
            (venda[i].valor_venda * 0.03)
        );
    }
}
