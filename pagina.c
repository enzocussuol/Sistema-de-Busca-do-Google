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
void imprimePagina(Pagina* p){

    printf("Pagina: %s, rank : %.2f\n",p->nome,p->rank);

}
void liberaPagina(Pagina* p){

    free(p->nome);
    free(p);

}