#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define INF 1E08

// ------------------------------------------  ESTRUTURA DE DADOS DO GRAFO  --------------------------------------------

typedef struct XGrafo {
    int v;
    int **matriz_adj;
} Grafo;

// -----------------------------------------  ESTRUTURA DE DADOS DOS CORTES  -------------------------------------------

typedef struct XCorte {
    int origem;
    int destino;
    int capacidade;
} Corte;

// ----------------------------------------------  FUNÇÕES PRINCIPAIS  -------------------------------------------------

bool fluxo_floyd_warshall(Grafo *g, int **D);
void analisa_corte(Corte *c, int n, bool check);

// -----------------------------------  CRIAÇÃO E MANIPULAÇÃO DOS CORTES NO GRAFO  -------------------------------------

Corte *aloca_cortes(int n);
void cria_corte(Grafo *g, Corte *c, int origem, int destino, int pos, int **D);

// -----------------------------------  CRIAÇÃO E MANIPULAÇÃO DO GRAFO E ARESTAS  --------------------------------------

Grafo *cria_grafo(int v) {

    Grafo *g = (Grafo *) malloc(sizeof(Grafo));
    g->v = v;

    g->matriz_adj = (int **) malloc(v * sizeof(int *));
    for(int i = 0; i < v; i++)
        g->matriz_adj[i] = (int *) malloc(v * sizeof(int));

    for (int i = 0 ; i < v; i++) {
        for (int j = 0; j < v; j++)
            g->matriz_adj[i][j] = 0;
    }

    return g;
}

void cria_aresta(Grafo *g, int origem, int destino, int capacidade) {

    if ((origem <= 0 || origem > g->v) || (destino <= 0 || destino > g->v)) {
        printf("Aresta inválida encontrada: %d ---> %d \n", origem, destino);
        exit(1);
    }

    // Correção para os índices da matriz
    origem--;
    destino--;

    g->matriz_adj[origem][destino] = capacidade;      // Grafo direcionado
}

void free_graph(Grafo *g) {

    for (int i = 0; i < g->v; i++)
        free(g->matriz_adj[i]);

    free(g->matriz_adj);
    free(g);
}

// ---------------------------------  INCIALIZAÇÃO DA MATRIZ DE DISTÂNCIAS MÍNIMAS  ------------------------------------

void inicializa_matriz(Grafo *g, int **D) {

    for (int i = 0; i < g->v; i++) {
        for (int j = 0; j < g->v; j++) {

            if (i != j && g->matriz_adj[i][j] == 0)
                D[i][j] = INF;
            else
                D[i][j] = g->matriz_adj[i][j];
        }
    }
}