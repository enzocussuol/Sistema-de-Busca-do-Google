#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

struct celula{
    Pagina* pagina;
    Celula* proxCel;
};

struct lista{
    Celula* primCel;
    Celula* ultCel;
    int tam;
};

Lista* inicializaLista(){
    Lista* novaLista = (Lista*) malloc(sizeof(Lista));

    novaLista->primCel = NULL;
    novaLista->ultCel = NULL;
    novaLista->tam = 0;

    return novaLista;
}

int listaVazia(Lista* lista){
    if(lista->tam == 0) return 1;
    return 0;
}

void insereLista(Lista* lista, Pagina* pagina){
    Celula* novaCelula = (Celula*) malloc(sizeof(Celula));

    novaCelula->pagina = pagina;
    novaCelula->proxCel = NULL;

    if(listaVazia(lista)){
        lista->primCel = novaCelula;
        lista->ultCel = novaCelula;
    }else{
        lista->ultCel->proxCel = novaCelula;
        lista->ultCel = lista->ultCel->proxCel;
    }

    lista->tam++;
}

void imprimeLista(Lista* lista){
    Celula* celAux;

    for(celAux = lista->primCel; celAux != NULL; celAux = celAux->proxCel){
        imprimePagina(celAux->pagina);
    }
}

static void liberaCelulas(Celula* cel){
    if(cel){
        liberaCelulas(cel->proxCel);

        liberaPagina(cel->pagina);
        free(cel);
    }
}

void liberaLista(Lista* lista){
    liberaCelulas(lista->primCel);
    free(lista);
}