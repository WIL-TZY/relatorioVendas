#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    int indiceLeitura;
    int existeIndiceL = 0;
    char ch;

    // loop para identiicar quantidade de argumentos.
    for(int i = 0; i < argc; i++){
        if(strcmp(argv[i], "./leitura") == 0){
            indiceLeitura = i;
            printf("%i\n", indiceLeitura);
            existeIndiceL++;
        }
    }

    if(existeIndiceL){
        for(int i = indiceLeitura + 1; i < (indiceLeitura + 2); i++){
            printf("%s", argv[i]);       
            FILE *dados_leitura = fopen(argv[i], "r");
            FILE* dados_escrita = fopen("relatorio.txt", "w");
            while (!feof(dados_leitura)) {
                ch = fgetc(dados_leitura);
                printf("%c", ch);

                fputc(ch, dados_escrita);
            }
        }
        return 0;
    }
    else {
        printf("Adicione o comando leitura!");

        return 1;
    }
}
