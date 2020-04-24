// MAC0328 (2019) Algoritmos em Grafos
// Aluno:      DANIELA GONZALEZ FAVERO
// Número USP: 10277443
// Tarefa:     I
// Data:       2019-11-20
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

// A. MACARRONADA, explicada em português.
// Enquanto houver caminhos, faça:
// 1. Tente construir um macarrão a partir do vértice s, sempre
// checando se ainda há fluxo restante na matriz de fluxo para enviar.
// 2. Se ainda for possível enviar fluxo, armazene o fluxo mínimo que
// pode ser enviado, para que este seja o valor.
// 3. Se não for possível chegar ao vértice t enviando uma quantia > 0
// de fluxo, quebre o laço e tente outro caminho. Caso contrário, 
// devolva o vetor de pais e o fluxo enviado por esse macarrão.
// 4. Percorra o vetor de pais para imprimir o macarrão e seu fluxo.
// A cada iteração, faça a checagem se ainda há caminhos, verificando
// se estamos olhando para o vértice s e se não há caminho a seguir.

// Função privada auxiliar recursiva, que a cada chamada devolve se há
// caminhos possíveis a partir do vértice v. Além disso, constrói o 
// vetor de pais pa[] e armazena o fluxo máximo daquele caminho.
static bool caminhos (Graph G, vertex v, vertex t, vertex *pa, 
                      int **fluxo, int *visited, int *min)
{
    if (v == t) {
        return true;
    }
    for (link a = G->adj[v]; a != NULL; a = a->next) {
        if (fluxo[v][a->w] <= 0 || visited[a->w]) {
            continue;
        }
        pa[a->w] = v; 
        visited[a->w] = 1;
        int aux = *min;
        if (fluxo[v][a->w] < *min) {
            *min = fluxo[v][a->w];
        }
        if (caminhos(G, a->w, t, pa, fluxo, visited, min)) {
            return true;
        }  
        *min = aux;  
    }

    return false;   
}


// A função macarronada recebe um fluxo f[][] num grafo que tem vértice
// inicial s e vértice final t e imprima uma macarronada de caminhos
// que represente o fluxo. Ela faz isso a partir da função auxiliar
// caminhos(), que devolve se ainda há caminhos possíveis, os caminhos
// obtidos e seus respectivos fluxos.
void macarronada (int **f, Graph G, vertex s, vertex t) 
{
    int min = INT_MAX;
    vertex *pa = malloc(G->V * sizeof (int));
    pa[s] = s;
    int *visited = calloc(G->V, sizeof (int));

    printf("MACARRONADA\t FLUXO\n");
    while (caminhos(G, s, t, pa, f, visited, &min)) {
        vertex *macarrao = malloc(G->V * sizeof (int));
        int i = G->V;
        for (vertex v = t; v != s; v = pa[v]) {
            f[pa[v]][v] -= min;
            macarrao[--i] = v;
        }
        macarrao[--i] = s;
        for (int j = i; macarrao[j] != t; j++) {
            printf("%d-", macarrao[j]);
        }
        printf("%d\t\t %d\n", t, min);
        min = INT_MAX;
        free(macarrao);
        free(visited);
        visited = calloc(G->V, sizeof (int));
    }

    free(pa);
    free(visited);
}

// B. FLUXO EM QUASE-ÁRVORE, explicado em português.
// Primeiro fazemos uma dfs na árvore G-t. Nela, armazenamos o vetor de
// pais e o vetor de capacidades (sendo que a capacidade de um vértice
// é o valor da capacidade do arco que chega nele. Também guardamos um
// vetor de folhas para usar posteriormente.
// Dada esta dfs, basta iterar pelo vetor de folhas fazendo:
// 1. Subindo pelo vetor de pais até a raiz para encontrar a
// intensidade do fluxo máximo daquele caminho.
// 2. Comparando este fluxo máximo com o a capacidade do arco da folha
// examinada em t, e atualizando este fluxo.
// 3. Somando o fluxo do caminho à intensidade do fluxo máximo do grafo.

// Esta função auxiliar recursiva faz uma dfs diferenciada na árvore
// G-t, preenchendo o vetor pa[], cap[] (tal que cap[v] = (u-v)->cst,
// se u for pai de v) e folhas[]. 
static void fluxomaximoR (Graph G, vertex s, vertex t, vertex *pa,
                      int *cap, int *folhas, int *cnt)
{        
    for (link a = G->adj[s]; a != NULL; a = a->next) {
        if (a->w == t) {
            folhas[(*cnt)++] = s;
            continue;
        }
        pa[a->w] = s;
        cap[a->w] = a->cst;

        fluxomaximoR(G, a->w, t, pa, cap, folhas, cnt);
    }
}

// Esta função recebe um grafo capacitado G, com vértice inicial s e
// vértice final t, sendo que G-t é uma árvore radicada com raiz s. Ela
// calcula um fluxo máximo que respeite as capacidades e devolve a
// intensidade do fluxo máximo. Ela faz isso a partir do vetor de pais,
// capacidades e folhas (calculados por uma dfs diferenciada).
int fluxomaximo (Graph G, vertex s, vertex t) 
{
    int *cap = malloc(G->V * sizeof (int));
    vertex *pa = malloc(G->V * sizeof (int));
    pa[s] = s;
    vertex *folhas = malloc(G->V * sizeof (int));
    int cnt = 0;

    fluxomaximoR(G, s, t, pa, cap, folhas, &cnt);
    int fluxo = 0;
    for (int i = 0; i < cnt; i++) {
        vertex v = folhas[i];
        int min = G->adj[v]->cst;
        for (vertex w = v; w != s; w = pa[w]) {
            if (cap[w] < min) {
                min = cap[w];
            }
        }
        fluxo += min;
    }

    free(cap);
    free(pa);
    free(folhas);

    return fluxo;
}


