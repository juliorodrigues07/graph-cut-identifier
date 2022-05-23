#include "utilities.h"

// ----------------------------------------------  FUNÇÕES PRINCIPAIS  -------------------------------------------------

bool fluxo_floyd_warshall(Grafo *g, int **D) {

    // Supõe-se que os vértices raiz e anti-raiz são o de menor índice
    // e o de maior índice, respectivamente
    bool check = 0;
    int s = 0;
    int t = g->v - 1;

    for (int i = 0; i < g->v; i++) {
        for (int j = 0; j < g->v; j++) {

            if (j != i && D[j][i] < INF) {

                for (int k = 0; k < g->v; k++) {

                    // Se o caminho passando pelo vértice i é menor -> atualiza distância mínima entre j e k
                    if (D[j][i] + D[i][k] < D[j][k])
                        D[j][k] = D[j][i] + D[i][k];
                }
            }
        }
    }

    /* Se não existe caminho entre s e t, o conjunto de arestas é um corte
       pois está impedindo a passagem de s para t (INF) */
    if (D[s][t] == INF)
        check = 1;

    return check;
}

void analisa_corte(Corte *c, int n, bool cut) {

    int capacidade = 0;

    if (cut) {
        printf("O conjunto de arestas é um corte! \n");

        // Soma a capacidade de cada aresta que pertence ao conjunto de corte
        for (int i = 0; i < n; i++)
            capacidade += c[i].capacidade;

        printf("\nCapacidade: %d \n", capacidade);
    }
    else
        printf("O conjunto de arestas não é um corte! \n");
}

// -----------------------------------  CRIAÇÃO E MANIPULAÇÃO DOS CORTES NO GRAFO  -------------------------------------

Corte *aloca_cortes(int n) {

    Corte *c = (Corte *) malloc(n * sizeof(Corte));

    // Inicialização dos atributos de cada corte
    for (int i = 0; i < n; i++) {
        c[i].origem = 0;
        c[i].destino = 0;
        c[i].capacidade = 0;
    }

    return c;
}

void cria_corte(Grafo *g, Corte *c, int origem, int destino, int pos, int **D) {

    if ((origem <= 0 || origem > g->v) || (destino <= 0 || destino > g->v)) {
        printf("Corte inválido encontrado: %d ---> %d \n", origem, destino);
        exit(1);
    }

    c[pos].origem = origem;
    c[pos].destino = destino;

    // Correção para os índices da matriz
    origem--;
    destino--;

    /*
    Realização do corte, removendo a aresta entre origem e destino.
    É atribuída a constante INF para calcular a matriz de distâncias mínimas
    com o algoritmo de Floyd-Warshall
    */
    c[pos].capacidade = D[origem][destino];
    D[origem][destino] = INF;
}

// -----------------------------------------  LEITURA DOS DADOS DO GRAFO  -------------------------------------------

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
