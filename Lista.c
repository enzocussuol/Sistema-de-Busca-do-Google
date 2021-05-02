//
// Created by bonella on 14/12/2020.
//

#include "Lista.h"

struct lista{
    void* item;
    Lista* prox;
};

Lista* criaLista(void){
    return NULL;
}

Lista* insereLista(Lista* lista,void* item){
    Lista* nova = malloc(sizeof(*nova));
    nova->item = item;
    nova->prox = lista;
    return nova;
}

Lista* retiraLista(Lista* lista, int (*cb)(void*,void*),void* chave){
    Lista* p = lista;
    Lista* ant = NULL;

    //call back retorna 1 se achar
    while(p!=NULL && !cb(p->item,chave)){
        ant = p;
        p = p->prox;
    }
    if(p == NULL) return lista;

    if(ant == NULL) lista = p->prox;
    else ant->prox = p->prox;

    free(p);
    return lista;

}

int percorreLista(Lista* lista, int (*cb)(void*, void*), void* dado){
    Lista* p;

    for(p=lista;p!=NULL;p=p->prox){
        int r = cb(p->item, dado);
        if(r == 0) return 1;
    }
    return 0;
}
void* percorreListaRetornaDado(Lista* lista, int (*cb)(void*, void*), void* dado){
    Lista* p;

    for(p=lista;p!=NULL;p=p->prox){
        int r = cb(p->item, dado);
        if(r == 0) return p->item;
    }
    return NULL;
}

Lista* retornaProx(Lista* lista){
    return lista->prox;
}

void* retornaItem(Lista* lista){
    return lista->item;
}

void liberaLista(Lista* lista){
    Lista* p = lista;
    Lista* aux;
    while(p!=NULL){
        aux = p->prox;
        free(p);
        p = aux;
    }
}