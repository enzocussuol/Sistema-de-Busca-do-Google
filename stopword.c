//
// Created by bonella on 26/04/2021.
//

#include <stdlib.h>
#include <string.h>
#include "stopword.h"

struct stopWord{
    char* palavra;
    int tam;
};

StopWord* inicializaStopWord(char* palavra){
    StopWord* novaStopWord = (StopWord*) malloc(sizeof(StopWord));

    novaStopWord->palavra = strdup(palavra);
    novaStopWord->tam = strlen(novaStopWord->palavra);

    return novaStopWord;
}

// Realiza o hash de uma stopword utilizando o metodo de Horner
int hashStopWord(StopWord* stopWord, int tamHash){
    int cont = 0;

    for(int i = 0; i < stopWord->tam; i++){
        cont = (31*cont + stopWord->palavra[i]) % tamHash;
    }

    return cont;
}

int comparaStopWord(StopWord* sw1, StopWord* sw2){
    return strcmp(sw1->palavra, sw2->palavra);
}

void liberaStopWord(StopWord* stopWord){
    free(stopWord->palavra);
    free(stopWord);
}