#include "utilities.h"

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
