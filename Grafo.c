//
// Created by bonella on 28/04/2021.
//

#include "Grafo.h"
#include "tabelaHash.h"
#define TAM_WORD 10

struct grafo{
    //danilo suggestion
    int ** matrizAdj; //matriz que indica se matriz[i][j], tem conexao da pagina I para J
    Pagina** vetPagina; // indica qual pagina se trata na posicao da matriz
};

Grafo* inicializaGrafo(int nVertices){
    Grafo* novoGrafo = (Grafo*) malloc(sizeof(Grafo));

    novoGrafo->matrizAdj = malloc(sizeof(int*)*nVertices);

    for(int i = 0 ;i < nVertices;i++){
        novoGrafo->matrizAdj[i] = malloc(sizeof(int)*nVertices);
    }

    return novoGrafo;

}

Grafo* preencheGrafo(Grafo * g, Hash* h,int qtdPag){

    FILE* input = fopen("../graph.txt","r");
    char nomepagina[TAM_WORD];
    int numconexoes;
    while(fscanf(input,"%s %d", nomepagina, &numconexoes) == 1){


        char conect[TAM_WORD];
        for(int i = 0; i < numconexoes; i++){
            fscanf(input, "%s", conect);

        }
    }
}

void setVertices(Grafo*g,Lista* lista){
    //g->vertices=lista;
}
