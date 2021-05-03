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
    MapeiaPalavras(b);

    Grafo* grafo = inicializaGrafo(retornaNumPaginas(b));

    preencheGrafo(grafo,b);

    //imprimeBuscador(b);

    calculaPageRankPM(b,grafo);

    //imprimeBuscador(b);
    while(!feof(stdin))
        buscadordeTermos(b);

    liberaGrafo(grafo);
    LiberaBuscador(b);


    return 0;
}