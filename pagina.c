#include "pagina.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pagina{
    char* nome;
    double rank;
    int id;
};

Pagina* inicializaPagina(char* nome,int id){

    Pagina* new = malloc(sizeof(*new));

    new->nome = strdup(nome);
    new->rank = 0;
    new->id = id;

    return new;

}

char* getNome(Pagina* p){

    return p->nome;

}

double getRank(Pagina* p){

    return p->rank;

}

int getID(Pagina* p){

    return p->id;

}

void setRank(Pagina* p, double rank){
    p->rank = rank;
}

int comparaPagina(Pagina* a,Pagina* b){
    return strcmp(a->nome,b->nome);
}
int comparaNome(Pagina*a, char * nome){
    return strcmp(a->nome, nome);
}

int hashNomePagina(char * nomepagina, int tamHash){
    int cont = 0;

    for(int i = 0; i < strlen(nomepagina); i++){
        cont = (31*cont + nomepagina[i]) %tamHash;
    }

    return cont;
}
int hashPagina(Pagina* pagina, int tamHash){
    return hashNomePagina(pagina->nome, tamHash);
}

int cmpPRPaginas(const void* p, const void* q){
    const Pagina* const* p1 = (const Pagina* const*) p;
    const Pagina* const* p2 = (const Pagina* const*) q;

    double diferenca = (double) (*p1)->rank - (*p2)->rank;

    if(diferenca > 0) return -1;
    else if(diferenca < 0) return 1;
    else{
        return comparaPagina((Pagina *) p1, (Pagina *) p2);
    }
}

void imprimePagina(Pagina * p){
    printf("%s "/*, Id %d, Rank %.8lf */, p->nome/*, p->id, p->rank*/);
}

void liberaPagina(Pagina* p){

    free(p->nome);
    free(p);

}