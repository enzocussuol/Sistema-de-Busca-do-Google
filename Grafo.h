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

typedef struct grafo Grafo;

Grafo* inicializaGrafo();
Grafo* preencheGrafo(Grafo * g, Hash * paginas,int qtdPag);
void setVertices(Grafo*g,Lista* lista);

#endif //TRABALHO_3_DE_ED2_GRAFO_H
