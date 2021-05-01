//
// Created by bonella on 26/04/2021.
//

#include "tabelaHash.h"

struct tabelahash{
    Lista** conteudo;
    int tam;
};

Hash * inicializaHash(int tam){
    Hash * novaHash = (Hash*) malloc(sizeof(Hash));
    novaHash->conteudo = (Lista**) malloc(sizeof(Lista*) * tam);

    for(int i = 0; i < tam; i++){
        novaHash->conteudo[i] = criaLista();
    }
    novaHash->tam = tam;

    return novaHash;
}


int acessaHash(Hash * hash, int findHash(void*, int), int compare(void*, void*), void * dado){
    int pos = findHash(dado, hash->tam);

    int flag = percorreLista(hash->conteudo[pos],compare,dado);
    if(flag) return 1;

    hash->conteudo[pos] = insereLista(hash->conteudo[pos],dado);

    return 0;
}

int buscaHash(Hash * hash, int findHash(void*, int), int compare(void*, void*), void * dado){
    int pos = findHash(dado, hash->tam);

    int flag = percorreLista(hash->conteudo[pos],compare,dado);
    if(flag) return 1;


    return 0;
}

void liberaHash(Hash * hash){
    for(int i = 0; i < hash->tam; i++){
        if(cb != NULL) percorreLista(hash->conteudo[i],cb,0);
        liberaLista(hash->conteudo[i]);
    }

    free(hash->conteudo);
    free(hash);
}

void imprimeHash(Hash *hash, void funcaoImprime(void *,void*)){
    //printf("tamanho da hash: %d\n", hash->tam);
    for(int i=0; i<hash->tam; i++){
        //printf("Pos %d da hash\n", i);
        percorreLista(hash->conteudo[i], (int (*)(void *, void *)) funcaoImprime, 0);
    }
}