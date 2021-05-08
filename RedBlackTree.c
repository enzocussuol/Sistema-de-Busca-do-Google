//
// Created by bonella on 25/04/2021.
//

#include "RedBlackTree.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define TAMHASH 67

struct rbt{
    char* chave;
    Lista* PaginasOcorrencia;
    char color;
    struct rbt* esquerda, *direita;
};

RBT* inicializaRBT(){
    return NULL;
}

static int compare(char* a, char* b){
    return strcmp(a,b);
}

RBT* insereRBT( RBT* rbtree,Pagina* pagina , char* chave){
    if(rbtree == NULL){
        RBT* novo = malloc(sizeof(*novo));
        novo->PaginasOcorrencia = criaLista();
        novo->PaginasOcorrencia = insereLista(novo->PaginasOcorrencia,pagina);
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
        //caso ele tenha recebido a msm palavra da pagina
        if(retornaItem(rbtree->PaginasOcorrencia )!= pagina)
            rbtree->PaginasOcorrencia = insereLista(rbtree->PaginasOcorrencia,pagina);
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

Lista* buscaRBTLista(RBT * rbtree, char* chave){
    while(rbtree != NULL) {
        int comp;
        comp = compare(chave,rbtree->chave);
        if(comp < 0) rbtree = rbtree->esquerda;
        else if(comp > 0) rbtree = rbtree->direita;
        else return rbtree->PaginasOcorrencia;
    }
    return NULL;
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
    printf("\n");

    imprimeRBT(rbtree->direita);
}

void liberaRBT(RBT* rbtree){
    if(rbtree != NULL){
        free(rbtree->chave);
        liberaLista(rbtree->PaginasOcorrencia);
        liberaRBT(rbtree->esquerda);
        liberaRBT(rbtree->direita);
    }
    free(rbtree);
}