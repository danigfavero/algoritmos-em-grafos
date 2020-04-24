// MAC0328 (2019) Algoritmos em Grafos
// Aluno:      DANIELA GONZALEZ FAVERO
// Número USP: 10277443
// Tarefa:     B
// Data:       2019-08-15
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
////////////////////////////////////////////////////////////////////////

// Essa tarefa foi realizada em grupo juntamente ao aluno
// BENTO BRUNO PEREIRA 
// Pensamos juntos no que o programa deveria fazer, programamos
// juntos a função tperm(). Depois de já termos discutido as
// soluções, ele fez a função top() e eu fiz o rastreamento da
// DFS. Depois debuggamos juntos e ele escreveu a prova
// do algoritmo.

#include "GRAPHlists.h"

/* EXERCÍCIO 1 */

// A função tperm() recebe um grafo e uma permutação dos seus
// vértices e devolve se a permutação é topológica.
bool tperm (Graph G, int* vv)
{
	int V = G->V;
	int* wgt = calloc(V, sizeof(int));

	for (int i = 0; i < V; i++) {
		wgt[vv[i]] = i + 1;
		for (link a = G->adj[vv[i]]; a != NULL; a = a->next) {
			if (wgt[a->w] != 0) {
        free(wgt);
				return 0;
			} 
		}
	}
	free(wgt);
	return 1;
}

/* EXERCÍCIO 2 */

// A função top() recebe um grafo e devolve se é um 
// grafo topológico ou não. A função remove fontes do grafo
// repetidamente até decidir o que retornará. O vetor "q" é
// uma representação de uma fila
bool top (Graph G)
{
	int V = G->V, pos = 0, sz = 0;
	int* q = calloc(V, sizeof(int));
	int* indegs = calloc(V, sizeof(int));

	for (int i = 0; i < V; i++) {
		indegs[i] = GRAPHindeg(G, i);
		if (indegs[i] == 0) {
			q[sz++] = i;
		}
	}

	while (pos < sz) {
		int v = q[pos++];
		for (link a = G->adj[v]; a != NULL; a = a->next) {
			if (--indegs[a->w] == 0) {
				q[sz++] = a->w;
			} 
		}	
	}
  
  free(q);
  free(indegs);
	
  if (pos == V) return 1;
	return 0;

}

/* Vamos realizar duas provas para a corretude do algoritmo.
  1. O algoritmo retorna que um DAG é topológico.
    Realizaremos essa prova por indução no número de vértices. 
    Seja o caso base quando n = 1, onde n é o número de vértices.
    Então, é óbvio que o algoritmo funciona, pois nosso vértice
    sera uma fonte irá para a fila e o tamanho  desta será igual 
    a n. Suponha agora que temos um dag com k vértices, e que vale 
    que para qualquer DAG com menos de k vértices o algoritmo 
    dá uma resposta correta. Segue que como temos um DAG ele não
    contém ciclos, logo existe pelo menos uma fonte. Assim, se 
    removermos fonte de menor valor do nosso grafo, segue que 
    agora temos um DAG com k-1 vértices, pois não é possível
    que um ciclo seja formado pela remoção de uma fonte. Segue 
    que nosso algoritmo dá uma resposta correta para este grafo, 
    e, assim, como tiramos a "menor" fonte, temos que pelo fato
    do resto do algoritmo estar correta, segue que teremos inse-
    rido k-1 + 1 vértices (da fonte removida primeiramente) na fila,
    e nosso algoritmo dará a resposta correta.
  2. O algoritmo retorna que um grafo com ciclo não é topológico.
    Seja um grafo G com ciclo e um vértice v de algum ciclo. Vamos
    assumir por contradição que, em algum momento, nosso algoritimo
    vai colocar o vértice v na fila. Trivialmente, isso implica 
    que já removemos todos os vértices que tem arestas que vão 
    para v. Como v pertence a um ciclo, segue que seja u o 
    antecessor de v no ciclo. Então, temos que já ter tirado u
    do ciclo. Mas claramente pelo fato do ciclo ser finito 
    chegaremos que, para remover v, teremos que já ter tirado ele, 
    visto que o caminho dos ancestrais no ciclo de v em algum 
    momento voltará para v, como estamos em um ciclo. Logo,
    por contradição segue que nunca removeremos um vértice v que 
    pertença há algum ciclo, logo nosso algoritmo não colocará
    todos os vértices do grafo na fila e retornará que ele não é 
    topológico, como queríamos.    

*/

/* EXERCÍCIO 3

Aplicando GRAPHdfs() no grafo pedido:

v-w dfs (G, w)                        pa[w]

7 dfsR (G, 7)                         7
7-5 dfsR (G, 5)                       7
   5-7                              
   5-4 dfsR (G, 4)                    5          
      4-7                           
      4-5
      4
   5-1 dfsR (G, 1)                    5
      1-3 dfsR (G, 3)                 1
         3-6 dfsR (G, 6)              3
            6-4
            6-2 dfsR (G, 2)           6      
               2-7
               2
            6-0 dfsR (G, 0)           6
               0-4
               0-2
               0
            6
         3
      1
   5
7-3
7  


w           0   1   2   3   4   5   6   7
pre[w]      7   3   6   2   5   1   5   0

w           0   1   2   3   4   5   6   7
pa[w]       6   5   6   1   5   7   3   7

*/