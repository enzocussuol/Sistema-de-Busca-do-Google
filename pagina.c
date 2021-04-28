#include "pagina.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pagina{
    char* nome;
    double rank;
};

Pagina* inicializaPagina(char* nome){

    Pagina* new = malloc(sizeof(*new));

    new->nome = strdup(nome);
    new->rank = 0;

    return new;

}

char* getNome(Pagina* p){

    return p->nome;

}

double getRank(Pagina* p){

    return p->rank;

}

void setRank(Pagina* p, double rank){

    p->rank = rank;

}

int comparaPagina(Pagina* a,Pagina* b){
    return strcmp(a->nome,b->nome);
}

int hashPagina(Pagina* pagina, int tamHash){
    int cont = 0;

    for(int i = 0; i < strlen(pagina->nome); i++){
        cont += pagina->nome[i];
    }

    return cont%tamHash;
}

void imprimePagina(Pagina* p){

    printf("Pagina: %s ",p->nome);

}
void liberaPagina(Pagina* p){

    free(p->nome);
    free(p);

}