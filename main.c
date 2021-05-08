#include <stdio.h>
#include "Lista.h"
#include "Grafo.h"
#include "Buscador.h"

#define TAM_WORD 100

int main(int argc, char* argv[]){
    // Inicializa o buscador de palavras
    Buscador* b = initBuscador();

    // Preenche as paginas a partir do arquivo index.txt
    LePaginas(b, argv[1]);

    // Inicializa o grafo para realizar o calculo do Page Rank das paginas
    Grafo* grafo = inicializaGrafo(retornaNumPaginas(b));

    // Preenche o grafo (utiliza-se uma matriz de adjacencias)
    preencheGrafo(grafo,b,argv[1]);

    // Realiza o calculo do Page Rank para cada pagina
    calculaPageRankPM(b,grafo);

    // Libera o grafo pois este nao ira mais ser util
    liberaGrafo(grafo);

    // Preenche a Red Black Tree mapeando palavras com suas respectivas paginas
    MapeiaPalavras(b,argv[1]);

    // Realiza leitura do usuario (stdin)
    unsigned long buffersize = 100;
    char *buffer = malloc(sizeof(char)*buffersize);
    while(getline(&buffer,&buffersize,stdin)){
        if(feof(stdin)) break;
        buscadordeTermos(b,buffer);
    }
    free(buffer);

    // Libera o espaco de memoria utilizado pelo buscador de paginas
    LiberaBuscador(b);

    return 0;
}