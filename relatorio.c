#include <stdio.h>

// Esse programa é responsável por criar o arquivo final de relatório no formato TXT.
// O parâmetro recebido é o nome do arquivo a ser gerado (ex: relatorio.txt).

int main() {
    /* Esse programa deve receber os dados atualizados pelo programa analise 
       e produzir o arquivo relatorio.txt (sendo que esse nome pode ser definido pelo usuario) */

    // Abrir o arquivo relatorios.txt para escrita
    FILE *dados_escrita = fopen("relatorio.txt", "w");
    
    // Verificando se o arquivo relatorio.txt foi gerado com sucesso
    if (dados_escrita == NULL) {
        printf("Erro ao criar o arquivo de saída!\n");
        return 1;
    }

    char ch;

    // Lê o que recebeu de analise.c na entrada padrão (STDIN) e escreve no arquivo
    while ((ch = getchar()) != EOF) {
        // Escrevendo o conteúdo no arquivo aberto: relatorio.txt
        fputc(ch, dados_escrita);
    }

    fclose(dados_escrita);

    return 0;
}
