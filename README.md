# Identificador de cortes em grafos
 
 Um algoritmo capaz de identificar se dado conjunto de arestas induz ou não um corte em um grafo com fluxo, ou seja, a retirada de arestas impede a passagem de fluxo de um vértice forte o vértice destino. Além disso, no caso em que o conjunto de arestas retiradas produz um corte, é calculada a soma de seus pesos. (Atividade 5 da disciplina de Grafos - DCOMP/UFSJ)
 
# Compilação

       make

# Execução para instâncias de exemplo

Grafo 1:

       ./main 6 2 ./graph1/grafo_1.txt ./graph1/corte_1.txt
       
       ./main 6 2 ./graph1/grafo_1.txt ./graph1/corte_2.txt
      
       ./main 6 2 ./graph1/grafo_1.txt ./graph1/corte_3.txt
       
       ./main 6 2 ./graph1/grafo_1.txt ./graph1/corte_4.txt
       
Grafo 2:

       ./main 7 3 ./graph2/grafo_2.txt ./graph2/corte_1.txt
       
       ./main 7 3 ./graph2/grafo_2.txt ./graph2/corte_2.txt
       
       ./main 7 5 ./graph2/grafo_2.txt ./graph2/corte_3.txt
