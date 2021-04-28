//
// Created by bonella on 28/04/2021.
//

#include "Grafo.h"

typedef struct vertice{
    Pagina* pagina;
    int numAdj;
}Vertice;

typedef struct aresta{
    Vertice origem,destino;
    double peso;
}Aresta;


struct grafo{

    Lista* listaAdj;
    Lista* vertices;

};

Grafo* inicializaGrafo(){

    Grafo* novo = malloc(sizeof(*novo));
    novo->listaAdj = criaLista();
    novo->vertices = criaLista();
    return novo;

}

void setVertices(Grafo*g,Lista* lista){
    g->vertices=lista;
}
