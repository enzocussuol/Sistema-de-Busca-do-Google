//
// Created by bonella on 28/04/2021.
//

#include "Grafo.h"
#include "tabelaHash.h"
#include <math.h>

#define UNSIGNEDINTLEN sizeof(unsigned int)*8
#define SetBit(A,k)     ( A[(k)/UNSIGNEDINTLEN] |= (1 << ((k)%UNSIGNEDINTLEN)) )
#define TestBit(A,k)    ( A[(k)/UNSIGNEDINTLEN] & (1 << ((k)%UNSIGNEDINTLEN)) )


#define TAM_WORD 50

typedef struct Vertice{
    int numAdj;
    Pagina* pagina;
}Vertice;

struct grafo{
    unsigned int ** matrizAdj; //matriz que indica se matriz[i][j], tem conexao da pagina I para J
    int tam;
    Vertice* vertices;
};

Grafo* inicializaGrafo(int nVertices){
    Grafo* novoGrafo = (Grafo*) malloc(sizeof(Grafo));

    novoGrafo->matrizAdj = malloc(sizeof(int*)*nVertices);
    novoGrafo->vertices = malloc(sizeof(Vertice)*nVertices);
    for(int i = 0 ;i < nVertices;i++){
        novoGrafo->matrizAdj[i] = malloc(sizeof(int)*((nVertices/UNSIGNEDINTLEN)+1));
        for(int j = 0;j < (nVertices/UNSIGNEDINTLEN)+1 ; j++){ //inicializa todas as casa da matriz com 0
           novoGrafo->matrizAdj[i][j] = 0;
        }
    }

    novoGrafo->tam = nVertices;

    return novoGrafo;
}

void preencheGrafo(Grafo * g, Buscador * buscador){
    FILE* input = fopen("graph.txt","r");
    if(input == NULL){
        printf("Erro na abertura do arquivo grafo\n");
        exit(1);
    }

    char nomePagina[TAM_WORD];
    int numConexoes, indiceOrigem, indiceDestino;

    while(fscanf(input,"%s%d", nomePagina, &numConexoes) == 2){
        Pagina* aux = buscaDadoHash(retornaHashPaginas(buscador),
                            (int (*)(void *, int)) hashNomePagina,
                            (int (*)(void *, void *)) comparaNome,
                            nomePagina);
        indiceOrigem = getID(aux);
        g->vertices[indiceOrigem].pagina = aux;
        g->vertices[indiceOrigem].numAdj = numConexoes;
        for(int i = 0; i < numConexoes; i++){
            fscanf(input, "%s", nomePagina);
            aux = buscaDadoHash(retornaHashPaginas(buscador),
                                (int (*)(void *, int)) hashNomePagina,
                                (int (*)(void *, void *)) comparaNome,
                                nomePagina);
            indiceDestino = getID(aux);
            //g->matrizAdj[indiceOrigem][indiceDestino] = 1;
            SetBit(g->matrizAdj[indiceOrigem],indiceDestino);
        }
        fscanf(input, "\n");
    }
    fclose(input);
}

static double calculaEk(Grafo* g,double* ant){

    double e = 0;
    for(int i = 0 ; i < g->tam; i++){
        double diff = getRank(g->vertices[i].pagina) - ant[i];
        e += fabs(diff);
    }
    return e/g->tam;
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
//        if(grafo->matrizAdj[j][pos] == 1){
//            termo += ant[j]/ grafo->vertices[j].numAdj;
//        }
        if(TestBit(grafo->matrizAdj[j],pos)){
            termo += ant[j]/ grafo->vertices[j].numAdj;
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

    primeiroTermo = (1 - alfa)/ n;

    int j =0;
    do{
        j++;
        double  somapr = 0;
        for(int i = 0; i < grafo->tam;i++) ant[i] = getRank(grafo->vertices[i].pagina);

        for(int i = 0; i < grafo->tam; i++){
            ultimoTermo = calculaUltimoTermo(grafo, ant, i);
            PR = primeiroTermo + (alfa*ultimoTermo);

            if(grafo->vertices[i].numAdj == 0){
                termoEspecial = alfa * ant[i];
                PR += termoEspecial;
            }
            //printf("PR: %lf ",PR);
            setRank(grafo->vertices[i].pagina, PR);
            somapr += PR;
        }
        //printf("PRTOTAL: %f ek : %.12f\n",somapr,calculaEk(grafo,ant));
    }while(calculaEk(grafo,ant) > 0.000001);
    //printf("Iteracoes %d\n",j);
}

void imprimeGrafo(Grafo* grafo){
    for(int i = 0; i < grafo->tam; i++){
        for(int j = 0; j < grafo->tam; j++){
            printf("%d ", grafo->matrizAdj[i][j]);
        }
        printf("\n");
    }
}

void liberaGrafo(Grafo* grafo){
    for(int i = 0; i < grafo->tam; i++){
        free(grafo->matrizAdj[i]);
    }
    free(grafo->vertices);
    free(grafo->matrizAdj);
    free(grafo);
}