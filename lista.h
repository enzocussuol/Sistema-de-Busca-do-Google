#ifndef LISTA_H
    #define LISTA_H

    #include "pagina.h"

    typedef struct celula Celula;
    typedef struct lista Lista;

    Lista* inicializaLista();
    int listaVazia(Lista*);
    void insereLista(Lista*, Pagina*);
    void imprimeLista(Lista*);
    void liberaLista(Lista*);
#endif