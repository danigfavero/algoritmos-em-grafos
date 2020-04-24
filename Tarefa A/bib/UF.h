// MAC0328 (2019) 
// Altere e modifique � vontade. Mas observe o meu bom layout (veja
// www.ime.usp.br/~pf/algoritmos/aulas/layout.html) e n�o use tabs
// (exceto no come�o das linhas).

// Este arquivo: UF.h (codifica��o UTF-8)
// Data: 2019-07-17
// Autor: Paulo Feofiloff
//
// Esta � a interface de uma implementa��o da estrutura Union-Find
// especializada para v�rtices de grafos (veja GRAPHlists.h e
// GRAPHlists.c).
//
// O c�digo � uma adapta��o dos programas do livro "Algorithms",
// 3rd.ed., part 1, de Sedgewick.
////////////////////////////////////////////////////////////////////////


#ifndef _UF_h
#define _UF_h

#include "MYTOOLS.h" // mallocc()

// V�rtices (de grafos) s�o n�meros inteiros n�o-negativos (veja
// GRAPHlists.h).
#define vertex int

// UFinit() inicializa a estutura de chefes fazendo com que cada v�rtice
// seja o seu pr�prio chefe.
void 
UFinit( int V);

// A fun��o UFfind() devolve o chefe de v (ou seja, o chefe da
// componente conexa a floresta geradora mst[0..k-1] que cont�m v).
vertex 
UFfind( vertex v);

// A fun��o UFunion() recebe dois chefes distintos v0 e w0 e faz a uni�o
// das correspondentes componentes conexas. Devolve 1 se v0 for o chefe
// da fus�o das componentes e 2 se w0 for o chefe da fus�o das
// componentes.
void
UFunion( vertex v0, vertex w0);

// Encerra a estrutura Union-Find e libera o espa�o auxiliar que foi
// alocado pela estrutura.
void 
UFfree( void);

#endif
