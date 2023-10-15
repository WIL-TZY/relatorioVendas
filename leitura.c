#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

/* Argumentos de linha de comando em C
    argc: o número de argumentos passados para o programa na linha de comando.
    O primeiro argumento é o nome do programa em si, e o valor mínimo de argc é 1 (indicando apenas o nome do programa).
    argv[]: : Um array de strings (ou seja, um array de ponteiros para caracteres) que contém os argumentos passados para o programa. 
    argv[0] normalmente contém o nome do programa e argv[1] em diante contém os argumentos adicionais.
*/
int main(int argc, char* argv[]) {
    //setlocale(LC_ALL, "Portuguese");
    // No PowerShell, usa esse comando p/ poder exibir caracteres latinos: 65001

    // Debug - pode comentar / apagar
    printf("Número de argumentos: %d\n", argc);

    for (int i = 0; i < argc; i++) {
        printf("Argumento %d: %s\n", i, argv[i]);
    }

    int indicedoComandoLeitura;
    int existeIndiceL = 0;
    char ch;

    // Verificando se existe um segundo argumento
    for(int i = 0; i < argc; i++) {
        if (i >= 1) {
            existeIndiceL = 1;
        }
    }

    if(existeIndiceL){
        indicedoComandoLeitura = 1; 
            FILE *dados_leitura = fopen(argv[indicedoComandoLeitura], "r");

            // Verificando se o arquivo foi aberto com sucesso
            if (dados_leitura == NULL) {
                printf("Erro ao abrir o arquivo!\n");
                return 1;
            }

            FILE *dados_escrita = fopen("relatorio.txt", "w");
            
            // Verificando se o arquivo relatorio.txt foi gerado com sucesso
            if (dados_escrita == NULL) {
                printf("Erro ao criar o arquivo de saída!\n");
                return 1;
            }

            /*
            while (!feof(dados_leitura)) {
                ch = fgetc(dados_leitura);
                printf("%c", ch);

                fputc(ch, dados_escrita);
            }
            */

            while ((ch = fgetc(dados_leitura)) != EOF) {
                fputc(ch, dados_escrita);
            }

            fclose(dados_leitura);
            fclose(dados_escrita);

        return 0;
    }
    else {
        printf("Adicione o arquivo CSV para ser lido pelo programa!\n");

        return 1;
    }
}
