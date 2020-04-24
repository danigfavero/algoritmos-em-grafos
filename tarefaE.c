// MAC0328 (2019) Algoritmos em Grafos
// Aluno:      DANIELA GONZALEZ FAVERO
// Número USP: 10277443
// Tarefa:     E
// Data:       2019-09-12
//
// Solução baseada em ... <se for o caso> ...
//
// DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESTE PROGRAMA. TODAS
// AS PARTES DO PROGRAMA, EXCETO AS QUE FORAM FORNECIDAS PELO PROFESSOR
// OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE SEDGEWICK OU ROBERTS,
// FORAM DESENVOLVIDAS POR MIM.  DECLARO TAMBÉM QUE SOU RESPONSÁVEL POR
// TODAS AS EVENTUAIS CÓPIAS DESTE PROGRAMA E QUE NÃO DISTRIBUI NEM
// FACILITEI A DISTRIBUIÇÃO DE CÓPIAS. 
//
///////////////////////////////////////////////////////////////////////

#include "GRAPHlists.h"

// A função isEdgeBiconnected() recebe como parâmetro um grafo
// não-dirigido e decide se ele é aresta-biconexo.
bool isEdgeBiconnected (UGraph G)
{
    if (!UGRAPHisConnected(G))
        return false;

    for (vertex v = 0; v < G->V; ++v) {
        link a = G->adj[v];
        while (a != NULL) {   
            link anext = a->next; 
            vertex aux = a->w;
            UGRAPHremoveEdge(G, v, a->w);
            if (!GRAPHreach(G, v, aux)) {
                UGRAPHinsertEdge(G, v, aux);
                return false;
            }    
            UGRAPHinsertEdge(G, v, aux);
            a = anext;
        }
    }
    return true;
}