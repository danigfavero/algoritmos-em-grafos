// MAC0328 (2019) 
// Altere e modifique à vontade. Mas observe o meu bom layout (veja
// www.ime.usp.br/~pf/algoritmos/aulas/layout.html) e não use tabs
// (exceto no começo das linhas).

// Este arquivo: QUEUE.h (codificação UTF-8)
// Data: 2019-07-17
// Autor: Paulo Feofiloff
//
// Esta é a interface da implementação de uma fila de vértices de um
// grafo (veja GRAPHlists.h e GRAPHlists.c).
//
// Este interface é uma adaptação do programa 4.9, p.154, do livro
// "Algorithms", 3rd.ed., part 1, de Sedgewick.
////////////////////////////////////////////////////////////////////////


#ifndef _QUEUE_h
#define _QUEUE_h

#include "MYTOOLS.h" // mallocc()

// Vértice de grafo (veja GRAPHlists.h).
#define vertex int

void 
QUEUEinit( int N);

int 
QUEUEempty( void);

void 
QUEUEput( vertex v);

vertex 
QUEUEget( void);

void 
QUEUEfree( void);

#endif
