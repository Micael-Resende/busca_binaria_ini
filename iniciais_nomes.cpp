#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NOMES 1000
#define MAX_TAM_NOME 100

void swap(char nomes[MAX_NOMES][MAX_TAM_NOME], int x, int y) {
    char temp[MAX_TAM_NOME];
    strcpy(temp, nomes[x]);
    strcpy(nomes[x], nomes[y]);
    strcpy(nomes[y], temp);
}

void bubbleSort(char nomes[MAX_NOMES][MAX_TAM_NOME], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (stricmp(nomes[j], nomes[j + 1]) > 0) {//stricmp() compare substrings sem distinção entre maiúsculas e minúsculas
                swap(nomes, j, j + 1);
            }
        }
    }
}

int buscaBinaria(char nomes[][MAX_TAM_NOME], int n, char *sequencia) {
    int esquerda = 0;
    int direita = n - 1;
    int primeiroIndice = -1;

    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        char *nome = nomes[meio];

        if (strnicmp(nome, sequencia, strlen(sequencia)) == 0) {
            primeiroIndice = meio;
            direita = meio - 1;     
        } else if (stricmp(nome, sequencia) < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    return primeiroIndice;
}

int main() {
    FILE *arquivo = fopen("../nomes.txt", "rt");

    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    char nomes[MAX_NOMES][MAX_TAM_NOME];
    int numNomes = 0;

    while (fgets(nomes[numNomes], sizeof(nomes[0]), arquivo) != NULL) {
        numNomes++;
    }

    fclose(arquivo);

    bubbleSort(nomes, numNomes);

    printf("Digite as iniciais para a busca: ");
    char iniciais[MAX_TAM_NOME];
    scanf("%s", iniciais);

    int primeiroIndice = buscaBinaria(nomes, numNomes, iniciais);

    printf("Nomes encontrados com a sequencia '%s':\n", iniciais);

    if (primeiroIndice != -1) {
        int indice = primeiroIndice;
        while (indice < numNomes && strnicmp(nomes[indice], iniciais, strlen(iniciais)) == 0) {
            printf("%s", nomes[indice]);
            indice++;
        }
    } else {
        printf("Nenhum nome encontrado com a sequencia '%s'.\n", iniciais);
    }

    return 0;
}
