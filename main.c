#include <stdio.h>
#include <string.h>
#include "pagina.h"
#include "Lista.h"
#include "tabelaHash.h"
#include "stopword.h"
#include "RedBlackTree.h"
#include "Grafo.h"
#include "Buscador.h"

#define TAM_WORD 50
#define TAMHASH 49
#define MAX_PALAVRAS 10

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