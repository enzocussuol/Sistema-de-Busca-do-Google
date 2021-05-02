//
// Created by bonella on 25/04/2021.
//

#include "RedBlackTree.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAMHASH 1489

struct rbt{
    char* chave;
    Hash* PaginasOcorrencia;
    int color;
    struct rbt* esquerda, *direita;
};

RBT* inicializaRBT(){
    return NULL;
}

static int compare(char* a, char* b){
    return strcmp(a,b);
}

RBT* insereRBT( RBT* rbtree,Pagina* pagina , char* chave ){
    if(rbtree == NULL){
        RBT* novo = malloc(sizeof(*novo));
        novo->PaginasOcorrencia = inicializaHash(TAMHASH);
        acessaHash(novo->PaginasOcorrencia, (int (*)(void *, int)) hashPagina,(int (*)(void *, void *)) comparaPagina, pagina);
        novo->chave = strdup(chave);
        novo->direita = NULL;
        novo->esquerda = NULL;
        novo->color = RED;
        return novo;
    }

    int cmp = compare(chave, rbtree->chave);
    if(cmp < 0) rbtree->esquerda = insereRBT(rbtree->esquerda, pagina,chave);
    else if(cmp > 0) rbtree->direita = insereRBT(rbtree->direita,pagina,chave);
    else{
        acessaHash(rbtree->PaginasOcorrencia, (int (*)(void *, int)) hashPagina,(int (*)(void *, void *)) comparaPagina, pagina);
    }

    //LEAN LEFT
    if(isRed(rbtree->direita) && !isRed(rbtree->esquerda)) rbtree = rotateLeft(rbtree);
    // BALANCE 4 NODE
    if(isRed(rbtree->esquerda) && isRed(rbtree->esquerda->esquerda)) rbtree = rotateRight(rbtree);
    //SPLIT 4 NODE
    if(isRed(rbtree->esquerda) && isRed(rbtree->direita)) flipColors(rbtree);

    return rbtree;
}

int buscaRBT(RBT * rbtree, char* chave){
    while(rbtree != NULL) {
        int comp;
        comp = compare(chave,rbtree->chave);
        if(comp < 0) rbtree = rbtree->esquerda;
        else if(comp > 0) rbtree = rbtree->direita;
        else return 1;
    }

    return -1;
}

int isRed(RBT* rbtree){
    if(rbtree == NULL) return BLACK;
    return rbtree->color;
}

RBT* rotateLeft(RBT* rbtree){
    RBT* aux = rbtree->direita;
    rbtree->direita = aux->esquerda;
    aux->esquerda = rbtree;

    aux->color = aux->esquerda->color;
    aux->esquerda->color = RED;

    return aux;
}

RBT* rotateRight(RBT* rbtree){
    RBT* aux = rbtree->esquerda;
    rbtree->esquerda = aux->direita;
    aux->direita = rbtree;

    aux->color = aux->direita->color;
    aux->direita->color = RED;

    return aux;
}

void flipColors(RBT* rbtree){
    rbtree->color = RED;
    rbtree->esquerda->color = BLACK;
    rbtree->direita->color = BLACK;
}

void imprimeRBT(RBT* rbtree){
    if(rbtree == NULL){
        return;
    }

    imprimeRBT(rbtree->esquerda);
    printf("PALAVRA: ");
    printf("%s\t|\t",rbtree->chave);
    printf("Paginas: \n");
    imprimeHash(rbtree->PaginasOcorrencia, (void (*)(void *, void *)) imprimePagina);
    printf("\n");

    imprimeRBT(rbtree->direita);
}

void liberaRBT(RBT* rbtree){
    if(rbtree != NULL){
        free(rbtree->chave);
        liberaHash(rbtree->PaginasOcorrencia,NULL);
        liberaRBT(rbtree->esquerda);
        liberaRBT(rbtree->direita);
    }
    free(rbtree);
}