//
// Created by bonella on 01/05/2021.
//

#ifndef TRABALHO_3_DE_ED2_BUSCADOR_H
#define TRABALHO_3_DE_ED2_BUSCADOR_H


#include <ctype.h>
#include <string.h>

#include "Lista.h"

#include "RedBlackTree.h"
#include "stopword.h"

typedef struct buscador Buscador;

Buscador* initBuscador();
Lista* retornaListaPaginas(Buscador* b);
Hash* retornaHashPaginas(Buscador* b);
int retornaNumPaginas(Buscador* b);
RBT* retornaRBT(Buscador* b);
void LePaginas(Buscador* buscador);
void MapeiaPalavras(Buscador * buscador);
void buscadordeTermos(Buscador*b);
void imprimeBuscador(Buscador* buscador);
void LiberaBuscador(Buscador *b);

#endif //TRABALHO_3_DE_ED2_BUSCADOR_H
