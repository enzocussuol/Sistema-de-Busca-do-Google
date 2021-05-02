//
// Created by bonella on 28/04/2021.
//

#ifndef TRABALHO_3_DE_ED2_GRAFO_H
#define TRABALHO_3_DE_ED2_GRAFO_H
#include <stdio.h>
#include <stdlib.h>
#include "pagina.h"
#include "tabelaHash.h"
#include "Lista.h"
#include "Buscador.h"

typedef struct grafo Grafo;

Grafo* inicializaGrafo();
void preencheGrafo(Grafo * g , Buscador * buscador);
void calculaPageRankPM(Buscador*b, Grafo* grafo);
void imprimeGrafo(Grafo*);
void liberaGrafo(Grafo*);

#endif //TRABALHO_3_DE_ED2_GRAFO_H
