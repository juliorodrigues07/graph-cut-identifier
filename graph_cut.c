#include "graph.h"
#include "read.h"

// ----------------------------------------------------  MAIN  ---------------------------------------------------------

int main(int argc, char **argv) {

    // Entrada na linha de comando via terminal
    int v = atoi(argv[1]);
    int n = atoi(argv[2]);
    const char *arestas = argv[3];
    const char *cutting = argv[4];

    if (v <= 0) {
        printf("Número de vértices inválido! \n");
        exit(1);
    }

    // Alocação e inicialização do grafo e cortes
    Grafo *grafo = cria_grafo(v);
    Corte *cortes = aloca_cortes(n);

    // Leitura e criação das arestas do grafo a partir do arquivo de entrada
    read_edges_file(grafo, arestas);

    // Alocação e inicialização da matriz de distâncias mínimas
    int **D = (int **) malloc(v * sizeof(int *));
    for (int i = 0; i < v; i++)
        D[i] = (int *) malloc(v * sizeof(int));
    inicializa_matriz(grafo, D);

    // Leitura e realização dos cortes no grafo a partir do arquivo de entrada
    read_cutting_file(grafo, cortes, D, cutting);

    // Checagem da existência ou não de caminho entre s e t
    bool cut = fluxo_floyd_warshall(grafo, D);

    // Exibição dos resultados obtidos após aplicação do corte e cálculo de caminhos no grafo
    analisa_corte(cortes, n, cut);

    free_graph(grafo);
    return 0;
}

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
