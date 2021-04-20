#ifndef LISTA_H
    #define LISTA_H

    #include "pagina.h"

    typedef struct celula Celula;
    typedef struct lista Lista;

    Lista* inicializaLista();
    void insereLista(Lista*, Pagina*);
    void imprimeLista(Lista*);
    void liberaLista(Lista*);
#endif