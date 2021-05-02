//
// Created by bonella on 26/04/2021.
//

#ifndef TRABALHO_3_DE_ED2_TABELAHASH_H
#define TRABALHO_3_DE_ED2_TABELAHASH_H

typedef struct tabelahash Hash;

#include "stdlib.h"
#include "Lista.h"

Hash * inicializaHash();
int acessaHash(Hash * hash, int findHash(void*, int), int compare(void*, void*), void * dado);
int buscaHash(Hash * hash, int findHash(void*, int), int compare(void*, void*), void * dado);
void* buscaDadoHash(Hash * hash, int findHash(void*, int), int compare(void*, void*), void * dado);
void liberaHash(Hash* h,int (*cb)(void*,void*));
void imprimeHash(Hash * h, void func(void*,void*));
#endif //TRABALHO_3_DE_ED2_TABELAHASH_H
