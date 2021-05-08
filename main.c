#include <stdio.h>
#include "Lista.h"
#include "Grafo.h"
#include "Buscador.h"

#define TAM_WORD 100

int main(int argc, char* argv[]){

    Buscador* b = initBuscador();

    LePaginas(b);

    //calcula o page rank das paginas lidas
    Grafo* grafo = inicializaGrafo(retornaNumPaginas(b));
    preencheGrafo(grafo,b);
    calculaPageRankPM(b,grafo);
    liberaGrafo(grafo);

    MapeiaPalavras(b);
    //imprimeBuscador(b);
    //imprimeBuscador(b);
    unsigned long buffersize = 100;
    char *buffer = malloc(sizeof(char)*buffersize);
    while(getline(&buffer,&buffersize,stdin)){
        if(feof(stdin)) break;
        buscadordeTermos(b,buffer);
    }
    free(buffer);
    LiberaBuscador(b);

    return 0;
}