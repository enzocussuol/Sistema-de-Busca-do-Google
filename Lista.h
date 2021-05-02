//
// Created by bonella on 14/12/2020.
//

#ifndef EXERCICIO12_LISTA_H
#define EXERCICIO12_LISTA_H
#include <stdlib.h>
#include <stdio.h>

typedef struct lista Lista;

Lista* criaLista(void);

Lista* insereLista(Lista* lista,void* item);

Lista* retiraLista(Lista* lista, int (*cb)(void*,void*),void* chave);

void* percorreListaRetornaDado(Lista* lista, int (*cb)(void*, void*), void* dado);

int percorreLista(Lista* lista,int (*cb)(void*, void*),void* dado);

Lista* retornaProx(Lista* lista);

void* retornaItem(Lista* lista);

void liberaLista(Lista* lista);

#endif //EXERCICIO12_LISTA_H
