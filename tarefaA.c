// MAC0328 (2019) Algoritmos em Grafos
// Aluno:      DANIELA GONZALEZ FAVERO
// Número USP: 10277443
// Tarefa:     A
// Data:       2019-08-07
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
// Pensamos juntos no que o programa deveria fazer, depois
// eu estruturei a função main enquanto que ele fez as
// funções GRAPHoutDegree e GRAPHinDegree desse arquivo.
// Dividimos as funções da biblioteca entre nós e cada
// um debuggou um pouco.

/* O QUE O PROGRAMA FAZ:
    Esse programa gera dois grafos aleatórios e exibe na tela o número 
de vértices e o número de arcos dos grafos gerados. 
    Em seguida, exibe uma tabela com  graus de saída e entrada dos 
vértices e os o número de vértices com esses graus.
    Se o número de vértices for menor que 30, exibe as listas de 
adjacência do grafo.*/

#include <time.h>
#include "GRAPHlists.h"

int main(int argc, const char* argv[]) {

    (void)argc;

    // Gera o grafo aleatório com GRAPHrand1
    int V = atoi(argv[1]);
    int A = atoi(argv[2]);
    clock_t t = clock();
    Graph G = GRAPHrand1(V, A);
    t = clock() - t;
    double time_taken = ( (double) t)/CLOCKS_PER_SEC;

    printf("///////// Usando GRAPHrand1: /////////\n");
    printf("\nNúmero de vértices: %d\n", G->V);
    printf("Número de arcos: %d\n", G->A);
    printf("Tempo gasto: %lf\n\n", time_taken);

    printf("\nTabela dos graus de saída:\n");
    printf("Grau g \t Número de Vértices\n");

    int* plc = calloc((V), sizeof(int));
    int mx = 0;
    
    for (int i = 0; i < V; i++) {
        int outdeg = GRAPHoutdeg(G, i);
        if (outdeg > mx) mx = outdeg;
        plc[outdeg]++;
    }

    for (int i = 0; i <= mx; i++){
        if (i <= 3){
            printf("%d \t %d\n", i, plc[i]);
        }
        else if (mx - i <= 3){
            printf("%d \t %d\n", i, plc[i]);
        }
    }

    free(plc);

    printf("\nTabela dos graus de entrada:\n");
    printf("Grau g \t Número de Vértices\n");
    
    plc = calloc((V), sizeof(int));
    mx = 0;
    
    for (int i = 0; i < V; i++) {
        int indeg = GRAPHindeg(G, i);
        if (indeg > mx) mx = indeg;
        plc[indeg]++;
    }

    for (int i = 0; i <= mx; i++) {
        if (i <= 3){
            printf("%d \t %d\n", i, plc[i]);
        }
        else if (mx - i <= 3){
            printf("%d \t %d\n", i, plc[i]);
        }
    }

    free(plc);    


    if (V < 30) {
        printf("\nListas de adjacências:\n");
        GRAPHshow(G);
    }

    GRAPHdestroy(G);

    // Usando a GRAPHrand2

    t = clock();
    Graph H = GRAPHrand2(V, A);
    t = clock() - t;
    time_taken = ( (double) t)/CLOCKS_PER_SEC;

    printf("\n\n///////// Usando GRAPHrand2: /////////\n");


    printf("\nNúmero de vértices: %d \n", H->V);
    printf("Número de arcos: %d \n", H->A);
    printf("Tempo gasto: %f\n\n", time_taken);

    printf("\nTabela dos graus de saída:\n");
    printf("Grau g \t Número de Vértices\n");

    plc = calloc((V), sizeof(int));
    mx = 0;
    
    for (int i = 0; i < V; i++) {
        int outdeg = GRAPHoutdeg(H, i);
        if (outdeg > mx) mx = outdeg;
        plc[outdeg]++;
    }

    for (int i = 0; i <= mx; i++) {
        if (i <= 3){
            printf("%d \t %d\n", i, plc[i]);
        }
        else if (mx - i <= 3){
            printf("%d \t %d\n", i, plc[i]);
        }
    }

    free(plc);

    printf("\nTabela dos graus de entrada:\n");
    printf("Grau g \t Número de Vértices\n");
    
    plc = calloc((V), sizeof(int));
    mx = 0;
    
    for (int i = 0; i < V; i++) {
        int indeg = GRAPHindeg(H, i);
        if (indeg > mx) mx = indeg;
        plc[indeg]++;
    }

    for (int i = 0; i <= mx; i++) {
        if (i <= 3){
            printf("%d \t %d\n", i, plc[i]);
        }
        else if (mx - i <= 3){
            printf("%d \t %d\n", i, plc[i]);
        }
    }

    free(plc);

    if (H->V < 30) {
        printf("\nListas de adjacências:\n");
        GRAPHshow(H);
    }
   
    GRAPHdestroy(H);

}