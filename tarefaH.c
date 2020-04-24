// MAC0328 (2019) Algoritmos em Grafos
// Aluno:      DANIELA GONZALEZ FAVERO
// Número USP: 10277443
// Tarefa:     H
// Data:       2019-10-30
//
// DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESTE PROGRAMA. TODAS
// AS PARTES DO PROGRAMA, EXCETO AS QUE FORAM FORNECIDAS PELO PROFESSOR
// OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE SEDGEWICK, FORAM
// DESENVOLVIDAS POR MIM. DECLARO TAMBÉM QUE SOU RESPONSÁVEL POR TODAS
// AS EVENTUAIS CÓPIAS DESTE PROGRAMA E QUE NÃO DISTRIBUI NEM FACILITEI
// A DISTRIBUIÇÃO DE CÓPIAS. 
//
////////////////////////////////////////////////////////////////////////

#include "GRAPHlists.h"

// Esta função recursiva recebe uma árvore radicada T e a raiz r da
// árvore e devolve a altura da árvore. Ela faz isso percorrendo a
// árvore e comparando a altura devolvida com a altura máxima dos
// filhos de cada vértice.
int altura (Graph T, vertex r)
{
    int max = -1;
    for (link a = T->adj[r]; a != NULL; a = a->next) {
        int height = altura(T, a->w) + 1;
        if (height >= max)
            max = height;
    }
    return max;
}

// Calcula um emparelhamento maximal num grafo arbitrário. O
// emparelhamento é representado pelo vetor match[]. A função devolve o
// tamanho do emparelhamento percorrendo todos os vizinhos de cada
// vértice, verificando se ele já foi emparelhado e, caso contrário,
// emparelhando-o.
int emparMaximal (UGraph G)
{
    int *match = calloc(G->V, sizeof (int));
    int matching = 0;
    for (vertex v = 0; v < G->V; ++v)
        match[v] = -1;
    for (vertex v = 0; v < G->V; ++v) {
        if (match[v]!= -1)
            continue;
        for (link a = G->adj[v]; a != NULL; a = a->next) {
            if (match[a->w] == -1) {
                match[v] = a->w;
                match[a->w] = v;
                matching++;
                break;
            }
        }
    }
    free(match);
    return matching;
}

/* 

                    FIM DO ALGORITMO HÚNGARO

  Sim, no fim da última iteração do algoritmo húngaro para
emparelhamento máximo em grafo bipartido, é possível que o conjunto X
seja vazio. O conjunto X seria vazio se, na função augmentMatch() todos
os vértices de cor 0 estiverem emparelhados e, consequentemente, não
entrarem na fila.

  Sim, é possível que X seja o conjunto de todos os vértices pois pode
acontecer de, na última iteração do algoritmo, sobrar pelo menos um
vértice de cor 0 não emparelhado e nenhum vértice de cor 1 solteiro
(porque não seria a última iteração). Ou seja, todos os vértices foram
visitados e o algoritmo está garantidamente na última iteração.

*/