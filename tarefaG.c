// MAC0328 (2019) Algoritmos em Grafos
// Aluno:      DANIELA GONZALEZ FAVERO
// Número USP: 10277443
// Aluno:      BENTO BRUNO PEREIRA
// Número USP: 09783608
// Tarefa:     GG
// Data:       2019-10-12
//
// DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESTE PROGRAMA. TODAS
// AS PARTES DO PROGRAMA, EXCETO AS QUE FORAM FORNECIDAS PELO PROFESSOR
// OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE SEDGEWICK, FORAM
// DESENVOLVIDAS POR MIM. DECLARO TAMBÉM QUE SOU RESPONSÁVEL POR TODAS
// AS EVENTUAIS CÓPIAS DESTE PROGRAMA E QUE NÃO DISTRIBUI NEM FACILITEI
// A DISTRIBUIÇÃO DE CÓPIAS. 
//
////////////////////////////////////////////////////////////////////////

// Este programa procura resolver o problema da coloração mínima de
// vértices:  dado um grafo não-dirigido G, encontrar uma coloração
// válida de G com o menor número de cores possível. Utilizando várias
// heurísticas e uma função que checa se as colorações são possíveis,
// vários testes são feitos para comparar as heurísticas.

#include "GRAPHlists.h"
#include <time.h>

// FUNÇÕES AUXILIARES
///////////////////////////////////////////////////////////////////////

// Esta função privada auxiliar devolve um vértice aleatório do grafo G.
// (Vamos supor que G->V <= RAND_MAX.) Ela é apenas um invólucro para a
// função rand() da biblioteca stdlib, que produz um número inteiro
// aleatório no intervalo fechado 0..RAND_MAX.
static vertex randV (Graph G)
{ 
   double r = rand()/(RAND_MAX + 1.0);
   return r * G->V;
}

// Esta função privada auxiliar devolve uma cor aleatória no intervalo
// de 0 à cor. (Vamos supor que cor <= RAND_MAX.) Ela é apenas um 
// invólucro para a função rand() da biblioteca stdlib, que produz um
// número inteiro aleatório no intervalo fechado 0..RAND_MAX.
static int randColor (int cor)
{
   double r = rand()/(RAND_MAX + 1.0); 
   return r * cor;
}

// Esta função privada auxiliar verifica se a coloração encontrada por
// alguma heusrítica é válida. Recebe um grafo, um vetor de cores e um
// inteiro k que representa o número de cores necesário para colorir o
// grafo.
static bool checker (UGraph G, int* color, int k)
{
    for (vertex v = 0; v < G->V; v++) {
        for (link a = G->adj[v]; a != NULL; a = a->next) {
            if (color[v] == -1 || color[v] >= k) return false;
            if (color[v] == color[a->w]) return false;
        }
    }
    return true;
}

// Esta função privada auxiliar automatiza os testes das heurísticas
// sem a necessidade de duplicar código na main(). A função test()
// recebe a função de encontrar coloração para um grafo, o grafo a ser
// colorido e o vetor de cores que será utilizdo pela função passada.
// Ela mede o tempo gasto pelas funções e imprime o número de cores
// necessárias para colorir o grafo.
static void test (int (*f)(UGraph, int*), UGraph G, int *color)
{
    clock_t t = clock();
    int cor = (*f)(G, color);
    t = clock() - t;
    double time_taken = ( (double) t)/CLOCKS_PER_SEC;

    if (!checker(G, color, cor)) printf("Coloração inválida!\n");

    printf("Tempo gasto: %lf\n", time_taken);
    printf("Número de cores utilizadas: %d\n\n", cor);
} 

// HEURÍSTICAS PARA COLORIR GRAFOS
// As funções a seguir calculam uma coloração válida dos vértices do
// grafo não-dirigido G e devolve o número de cores efetivamente
// usadas. A coloração é armazenada no vetor color[].
///////////////////////////////////////////////////////////////////////

// A função seqColoring() utiliza a heurística gulosa dada em aula para
// tentar colorir o grafo, rodando um algoritmo sequencial.
int seqColoring (UGraph G, int *color)
{ 
    int k = 0;
    for (vertex v = 0; v < G->V; ++v)
        color[v] = -1;

    for (vertex v = 0; v < G->V; ++v) {
        bool *disponivel = malloc(k * sizeof(int));
        int i;
        for (i = 0; i < k; ++i) 
            disponivel[i] = true;
        for (link a = G->adj[v]; a != NULL; a = a->next) {
            i = color[a->w];
            if (i != -1) disponivel[i] = false;
        } 
        for (i = 0; i < k; ++i) {
            if (disponivel[i]) break;
        }
        if (i < k) color[v] = i;
        else color[v] = k++;
        free(disponivel);
    }

    return k;
}

// A função aleaVertexColoring() seleciona os vértices em uma ordem
// aleatória para colori-los, sorteando-os pelo randV().
int aleaVertexColoring (UGraph G, int *color)
{
    int k = 0;
    bool *usado = calloc(G->V, sizeof(bool));
    for (vertex v = 0; v < G->V; ++v)
        color[v] = -1;

    for (int j = 0; j < G->V; ++j) {
        vertex v;
        do {
            v = randV(G);
        } while(usado[v]);
        usado[v] = true;
        
        bool *disponivel = malloc(k * sizeof(int));
        int i;
        for (i = 0; i < k; ++i)
            disponivel[i] = true;
        for (link a = G->adj[v]; a != NULL; a = a->next) {
            i = color[a->w];
            if (i != -1) disponivel[i] = false;
        }
        for (i = 0; i < k; ++i) {
            if (disponivel[i]) {
                color[v] = i;
                i = -1;
                break;
            }
        }
        if (i != -1) color[v] = k++;
        free(disponivel);
    }

    free(usado);
    return k;
}

// A função aleaColorColoring() seleciona as cores em uma ordem
// aleatória para colorir os vértices, sorteanda-os pelo randColor().
int aleaColorColoring (UGraph G, int *color)
{
    int k = 0;
    for (vertex v = 0; v < G->V; ++v)
        color[v] = -1;

    for (vertex v = 0; v < G->V; ++v) {

        bool *disponivel = malloc(k * sizeof(int));
        int i;
        for (i = 0; i < k; ++i)
            disponivel[i] = true;
        for (link a = G->adj[v]; a != NULL; a = a->next) {
            i = color[a->w];
            if (i != -1)
                disponivel[i] = false;
        } 
        for (i = 0; i < k; ++i) {
            if (disponivel[i]) {
                do {
                    i = randColor(k);
                } while(!disponivel[i]);
                color[v] = i;
                i = -1;
                break;
            }
        }
        if (i != -1)
            color[v] = k++;
        free(disponivel);

    }

    return k;
}

// A função aleaColoring() é uma junção de aleaVertexColoring() e
// aleaColorColoring(), ou seja, além de selecionar os vértices em uma
// ordem aleatória, seleciona suas respectivas cores também em uma
// ordem aleatória.
int aleaColoring (UGraph G, int *color)
{
    int k = 0;
    bool *usado = calloc(G->V, sizeof(bool));
    for (vertex v = 0; v < G->V; ++v)
        color[v] = -1;

    for (int j = 0; j < G->V; ++j) {
        vertex v;
        do {
            v = randV(G);
        } while(usado[v]);
        usado[v] = true;
        
        bool *disponivel = malloc(k * sizeof(int));
        int i; 
        for (i = 0; i < k; ++i)
            disponivel[i] = true;
        for (link a = G->adj[v]; a != NULL; a = a->next) {
            i = color[a->w];
            if (i != -1) disponivel[i] = false;
        }
        for (i = 0; i < k; ++i) {
            if (disponivel[i]) {
                do {
                    i = randColor(k);
                } while(!disponivel[i]);
                color[v] = i;
                i = -1;
                break;
            }
        }
        if (i != -1) color[v] = k++;
        free(disponivel);
    }

    free(usado);
    return k;
}

// A função brelazColoring() utiliza a heurística de Brelaz, ou seja,
// em cada iteração, escolhe um vértice incolor v que seja adjacente ao
// maior número de cores. Isso é feito utilizando uma fila de
// prioridade (do arquivo PQ.c).
int brelazColoring (UGraph G, int *color)
{
    int k = 0;
    PQinit(G->V);
    int *prty = calloc(G->V, sizeof(int));

    for (vertex v = 0; v < G->V; ++v) {
        color[v] = -1;
        PQinsert(v, prty);
    }

    for (int j = 0; j < G->V; ++j) {
        vertex v = PQdelmin(prty);
        bool *disponivel = malloc(k * sizeof(int));
        int i; 
        for (i = 0; i < k; ++i) 
            disponivel[i] = true;
        for (link a = G->adj[v]; a != NULL; a = a->next) {
            i = color[a->w];
            if (i != -1) disponivel[i] = false;
        }
        for (i = 0; i < k; ++i) {
            if (disponivel[i]) break;
        }
        if (i < k) color[v] = i;
        else color[v] = k++;

        for (link a = G->adj[v]; a != NULL; a = a->next) {
            if (color[a->w] != -1) continue;
            prty[a->w]--;
            PQdec(a->w, prty);
        }
        free(disponivel);
    }
    PQfree();
    free(prty);
    return k;
}

// A função degreeColoring() utiliza a heurística de Brelaz, ou seja,
// em cada iteração, escolhe um vértice incolor v que seja adjacente ao
// maior número de cores. Isso é feito utilizando uma fila de
// prioridade (do arquivo PQ.c).
int degreeColoring (UGraph G, int *color)
{
    int k = 0;
    PQinit(G->V);
    int *prty = calloc(G->V, sizeof(int));

    for (vertex v = 0; v < G->V; ++v) {
        color[v] = -1;
        int deg = 0;
        for (link a = G->adj[v]; a != NULL; a = a->next) {
            deg--;
        }
        prty[v] = deg;
        PQinsert(v, prty);
    }

    for (int j = 0; j < G->V; ++j) {
        vertex v = PQdelmin(prty);
        bool *disponivel = malloc(k * sizeof(int));
        int i;
        for (i = 0; i < k; ++i)
            disponivel[i] = true;
        for (link a = G->adj[v]; a != NULL; a = a->next) {
            i = color[a->w];
            if (i != -1) disponivel[i] = false;
        }
        for (i = 0; i < k; ++i) {
            if (disponivel[i]) break;
        }
        if (i < k) color[v] = i;
        else color[v] = k++;
        free(disponivel);
    }
    PQfree();
    free(prty);
    return k;
}

int main (int argc, const char* argv[])
{

    if (argc < 4) {
        printf("Argumentos faltando!\n");
        return 0;
    }

    int V = atoi(argv[1]);
    int E = atoi(argv[2]);
    int s = atoi(argv[3]);
    srand(s);

    UGraph G = UGRAPHrand1(V, E);
    int* color = malloc(V * sizeof(int));

    printf("HEURÍSTICA 1: seqColoring()\n");
    test(seqColoring, G, color);

    printf("HEURÍSTICA 2: aleaVertexColoring()\n");
    test(aleaVertexColoring, G, color);

    printf("HEURÍSTICA 3: aleaColorColoring()\n");
    test(aleaColorColoring, G, color);

    printf("HEURÍSTICA 4: aleaColoring()\n");
    test(aleaColoring, G, color);

    printf("HEURÍSTICA 5: degreeColoring()\n");
    test(degreeColoring, G, color);

    printf("HEURÍSTICA 6: brelazColoring()\n");
    test(brelazColoring, G, color);
    
    UGRAPHdestroy(G);
    free(color);
    return 1;
} 

// Alguns dos testes feitos:
// (Realizamos muitos testes, registramos aqui aqueles que pareceram
// mais interessante para a construção desse relatório).
//
//       INPUT A:    100 100 3
//    HEURÍSTICA                CORES           TEMPO
//    seqColoring()               4            0.000030
//    aleaVertexColoring()        4            0.000087
//    aleaColorColoring()         4            0.000058
//    aleaColoring()              4            0.000084
//    degreeColoring()            3            0.000101
//    brelazColoring()            3            0.000110
//
//       INPUT B:    100 2000 7
//    HEURÍSTICA                CORES           TEMPO
//    seqColoring()               18           0.000264
//    aleaVertexColoring()        16           0.000287
//    aleaColorColoring()         19           0.000230
//    aleaColoring()              19           0.000260
//    degreeColoring()            17           0.000535
//    brelazColoring()            18           0.000506
//
//       INPUT C:    100 2000 3
//    HEURÍSTICA                CORES           TEMPO
//    seqColoring()               18           0.000205
//    aleaVertexColoring()        18           0.000218
//    aleaColorColoring()         20           0.000258
//    aleaColoring()              21           0.000344
//    degreeColoring()            16           0.000382
//    brelazColoring()            17           0.000543
//
//       INPUT D:    100 4000 9276
//    HEURÍSTICA                CORES           TEMPO
//    seqColoring()               37           0.000252
//    aleaVertexColoring()        36           0.000263
//    aleaColorColoring()         39           0.000269
//    aleaColoring()              39           0.000281
//    degreeColoring()            35           0.000409
//    brelazColoring()            35           0.000528
//
//       INPUT E:    1000 1000 821
//    HEURÍSTICA                CORES           TEMPO
//    seqColoring()               4            0.000244
//    aleaVertexColoring()        4            0.000766
//    aleaColorColoring()         5            0.000343
//    aleaColoring()              5            0.000722
//    degreeColoring()            4            0.000962
//    brelazColoring()            3            0.000850
//
//       INPUT F:    1000 10000 42
//    HEURÍSTICA                CORES           TEMPO
//    seqColoring()               55           0.019048
//    aleaVertexColoring()        54           0.019186
//    aleaColorColoring()         62           0.019587
//    aleaColoring()              62           0.020833
//    degreeColoring()            52           0.039900
//    brelazColoring()            54           0.027312
//
//       INPUT G:    10000 777777 67432
//    HEURÍSTICA                CORES           TEMPO
//    seqColoring()               52           0.265636
//    aleaVertexColoring()        52           0.270172
//    aleaColorColoring()         64           0.268291 
//    aleaColoring()              64           0.273964
//    degreeColoring()            49           0.505939
//    brelazColoring()            50           0.363737
//
// O que aprendemos com os testes:
//
//   Os grafos com menos arestas demonstraram resultados parecidos 
// (inputs A e E). A diferença começa a ficar evidente quanto mais
// populamos o grafo com arestas. Tratando dos demais inputs:
//   Aleatorizar a escolha de cores parece bem ineficiente,
// além de levar mais tempo, o número de cores utilizado acaba maior do
// que no algoritmo sequencial. Isso implica no aleaColoring()
// também, que aleatoriza escolha de vértice e cor.
//   A aleatorização apenas da escolha dos vértices, no entanto, fica
// sempre entre o algoritmo sequencial e as funções do Breláz e do
// degree. No entanto, às vezes acontece dessa heurística ser até
// melhor do que as heurísticas mais poderosas: compare os inputs B e
// C, com diferença apenas de seed.
//   O degreeColoring() se mostrou uma excelente heurística para
// minizar número de cores utilizadas, se mostrando melhor do que o
// Breláz (conforme aumenta o número de arestas). No entanto, esse
// algoritmo consome muito tempo (proporcional ao número de vértices).
//   O brelazColoring() é, de fato, uma exclente heurística, com uma
// eficiência aceitável. Mesmo "perdendo" da degreeColoring() diversas
// vezes, essa derrota foi sempre por uma diferença baixíssima, além de
// que o Breláz se mosrtrou mais rápido que a degreeColoring() em
// geral.
//   Conclusão: as heurísticas mais interessantes para o problema são
// a brelazColoring() e a degreeColoring(), apesar de que às vezes a 
// aleatorização de vértices dá conta do serviço em um tempo menor.