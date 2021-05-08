//
// Created by bonella on 25/04/2021.
//

#ifndef TRABALHOVSH_REDBLACKTREE_H
#define TRABALHOVSH_REDBLACKTREE_H

#include "pagina.h"
#include "tabelaHash.h"

#define RED 1
#define BLACK 0

#include "tabelaHash.h"
typedef struct rbt RBT;

RBT* inicializaRBT();
RBT* insereRBT(RBT* rbtree,Pagina* pagina , char* chave);
int buscaRBT(RBT * rbtree, char* chave);
Lista* buscaRBTLista(RBT * rbtree, char* chave);
int isRed(RBT*);
RBT* rotateLeft(RBT*);
RBT* rotateRight(RBT*);
void flipColors(RBT*);
void imprimeRBT(RBT*);
void liberaRBT(RBT*);

#endif //TRABALHOVSH_REDBLACKTREE_H
