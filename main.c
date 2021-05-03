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

    imprimeBuscador(b);

    liberaGrafo(grafo);
    LiberaBuscador(b);

    //
//    printf("Digite o texto que deseja buscar:\n");
//
//    Lista * listaPalavras = criaLista();
//    char palavra[TAM_WORD];
//    char separador = ' ';
//
//    for(int j = 0; separador != '\n'; j++){
//        scanf("%s%c", palavra, &separador);
//        listaPalavras = insereLista(listaPalavras, strdup(palavra));
//    }
//
    return 0;
}