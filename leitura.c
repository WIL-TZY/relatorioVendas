#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Esse programa lê um arquivo CSV externo e disponibiliza os dados para o programa que fará a análise.
// O programa recebe como parâmetro o arquivo CSV que será feita a leitura dos dados.

// No PowerShell, use esse comando p/ poder exibir caracteres latinos: 65001

/*
Compila:
    gcc leitura.c -o leitura.out && gcc analise.c -o analise.out && gcc relatorio.c -o relatorio.out 
Executa:
    ./leitura.out vendas.csv | ./analise.out | ./relatorio relatorio.txt
*/
int main(int argc, char* argv[]) {
    int indicedoComandoLeitura;
    int existeIndiceL = 0;
    char ch;

    // Verificando se existe um segundo argumento
    for(int i = 0; i < argc; i++) {
        if (i >= 1) {
            existeIndiceL = 1;
        }
    }

    // Se foi adicionado um segundo argumento
    if(existeIndiceL){
        // Ler arquivo CSV
        indicedoComandoLeitura = 1; 
            FILE *dados_leitura = fopen(argv[indicedoComandoLeitura], "r");

            // Verificando se o arquivo foi aberto com sucesso
            if (dados_leitura == NULL) {
                printf("Erro ao abrir o arquivo!\n");
                return 1;
            }

            while ( (ch = fgetc(dados_leitura)) != EOF) {
                // Imprime em STDOUT
                printf("%c", ch);
            }
           
            fclose(dados_leitura);

        return 0;
    }
    // Se NÃO houver um segundo argumento
    else {
        printf("Nenhum arquivo CSV adicionado. Programa finalizado.\n");

        return 1;
    }
}
