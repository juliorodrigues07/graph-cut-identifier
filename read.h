#include <stdio.h>
#include <stdlib.h>

void read_edges_file(Grafo *g, const char *file_name) {

    FILE *arquivo;
    arquivo = fopen(file_name, "r");

    if (!arquivo) {
        printf("O arquivo %s não pode ser aberto! \n", file_name);
        exit(1);
    }

    int aresta[3];
    int valor, i = 0;

    while (!feof(arquivo)) {

        if (!fscanf(arquivo, "%d\n", &valor)) {
            printf("Falha na leitura! \n");
            exit(1);
        }

        aresta[i] = valor;
        i++;

        if (i == 3) {
            i = 0;
            cria_aresta(g, aresta[0], aresta[1], aresta[2]);
        }
    }

    fclose(arquivo);
}

void read_cutting_file(Grafo *g, Corte *c, int **D, const char *file_name) {

    FILE *arquivo;
    arquivo = fopen(file_name, "r");

    if (!arquivo) {
        printf("O arquivo %s não pode ser aberto! \n", file_name);
        exit(1);
    }

    int corte[2];
    int valor, i = 0;
    int pos = 0;        // Índice do vetor da estrutura de dados dos cortes

    while (!feof(arquivo)) {

        if (!fscanf(arquivo, "%d\n", &valor)) {
            printf("Falha na leitura! \n");
            exit(1);
        }

        corte[i] = valor;
        i++;

        if (i == 2) {
            i = 0;
            cria_corte(g, c, corte[0], corte[1], pos, D);
            pos++;
        }
    }

    fclose(arquivo);
}