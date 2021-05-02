//
// Created by bonella on 28/04/2021.
//

#include "Grafo.h"
#include "tabelaHash.h"
#include <math.h>


#define TAM_WORD 50

typedef struct Vertice{
    int numAdj;
    Pagina* pagina;
}Vertice;

struct grafo{
    //danilo suggestion
    int ** matrizAdj; //matriz que indica se matriz[i][j], tem conexao da pagina I para J
    Pagina** vetPagina; // indica qual pagina se trata na posicao da matriz
};

Grafo* inicializaGrafo(int nVertices){
    Grafo* novoGrafo = (Grafo*) malloc(sizeof(Grafo));

    novoGrafo->matrizAdj = malloc(sizeof(int*)*nVertices);
    novoGrafo->vertices = malloc(sizeof(Vertice)*nVertices);
    for(int i = 0 ;i < nVertices;i++){
        novoGrafo->matrizAdj[i] = malloc(sizeof(int)*nVertices);
        for(int j = 0;j < nVertices ; j++){ //inicializa todas as casa da matriz com 0
           novoGrafo->matrizAdj[i][j] = 0;
        }
    }

    return novoGrafo;

}

void preencheGrafo(Grafo * g, Buscador * buscador){
    FILE* input = fopen("../graph.txt","r");
    char nomepagina[TAM_WORD];
    int numconexoes;
    while(fscanf(input,"%s %d", nomepagina, &numconexoes) == 1){


        char conect[TAM_WORD];
        for(int i = 0; i < numconexoes; i++){
            fscanf(input, "%s", conect);

        }
        fscanf(input, "\n");
    }
}

static double calculaEk(Grafo* g,double* ant){

    double e = 0;
    for(int i = 0 ; i< g->tam; i++){
        double diff = getRank(g->vertices[i].pagina) - ant[i];
        e += diff*diff;

    }

    return sqrt(e);
}

void inicializaPM(Buscador * b){
    Lista* listaPaginas = retornaListaPaginas(b);
    int n = retornaNumPaginas(b);
    for(listaPaginas ; listaPaginas!=NULL ; listaPaginas = retornaProx(listaPaginas)){
       setRank(retornaItem(listaPaginas), 1.0/n);
    }
}

static double calculaUltimoTermo(Grafo* grafo, double* ant, int pos){
    double termo = 0;

    for(int j = 0; j < grafo->tam; j++){
        if(grafo->matrizAdj[j][pos] == 1){
            termo += ant[j]/grafo->vertices[j].numAdj;
        }
    }

    return termo;
}

void calculaPageRankPM(Buscador*b, Grafo* grafo){
    int n = retornaNumPaginas(b);
    double PR=0;
    double alfa = 0.85;
    double primeiroTermo, ultimoTermo, termoEspecial;
    double ant[grafo->tam];

    inicializaPM(b);

    for(int i = 0;i< grafo->tam;i++){
        ant[i] = getRank(grafo->vertices[i].pagina);
    }
    imprimeBuscador(b);
    primeiroTermo = (1 - alfa)/n;
    int j =0;
    do{
        //printf("Iteracao %d: ", ++j);
        double  somapr = 0;
        for(int i = 0; i < grafo->tam; i++){
            ultimoTermo = calculaUltimoTermo(grafo, ant, i);
            PR = primeiroTermo + ultimoTermo;

            ant[i] = getRank(grafo->vertices[i].pagina);
            if(grafo->vertices[i].numAdj == 0){
                termoEspecial = alfa * ant[i];
                PR += termoEspecial;
            }
            //printf("PR: %lf ",PR);
            setRank(grafo->vertices[i].pagina, PR);
            somapr += PR;
        }
        //printf("PRTOTAL: %f ek : %f\n",somapr,calculaEk(grafo,ant));
    }while(calculaEk(grafo,ant) > 0.000001);
}

void imprimeGrafo(Grafo* grafo){

}

void liberaGrafo(Grafo* grafo){
//    liberaLista(grafo->listaAdj);
//    liberaLista(grafo->vertices);
//    free(grafo);
}