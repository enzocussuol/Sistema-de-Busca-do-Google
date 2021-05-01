//
// Created by bonella on 01/05/2021.
//

#ifndef TRABALHO_3_DE_ED2_BUSCADOR_H
#define TRABALHO_3_DE_ED2_BUSCADOR_H

typedef struct buscador Buscador;

Buscador* initBuscador();
void LePaginas(Buscador* buscador);
void MapeiaPalavras(Buscador * buscador);
void imprimeBuscador(Buscador* buscador);
void LiberaBuscador(Buscador *b);

#endif //TRABALHO_3_DE_ED2_BUSCADOR_H
