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

// --------------------------------------------  DECLARAÇÕES DAS FUNÇÕES  -------------------------------------------

void read_edges_file(Grafo *g, const char *file_name);
void read_cutting_file(Grafo *g, Corte *c, int **D, const char *file_name);
Grafo *cria_grafo(int v);
void cria_aresta(Grafo *g, int origem, int destino, int capacidade);
void free_graph(Grafo *g);
void inicializa_matriz(Grafo *g, int **D);
bool fluxo_floyd_warshall(Grafo *g, int **D);
void analisa_corte(Corte *c, int n, bool check);
Corte *aloca_cortes(int n);
void cria_corte(Grafo *g, Corte *c, int origem, int destino, int pos, int **D);
