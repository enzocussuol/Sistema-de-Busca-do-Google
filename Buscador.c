//
// Created by bonella on 01/05/2021.
//
#include <ctype.h>
#include <string.h>
#include "Buscador.h"
#include "Lista.h"
#include "tabelaHash.h"
#include "RedBlackTree.h"
#include "stopword.h"


#define TAM_WORD 50
#define TAMHASH 49

struct buscador{
    Lista* listaPaginas;
    Hash* hashPaginas;
    int numPaginas;
    Hash* hashSW;
    RBT* mapaPalavraPaginas;
};

Buscador* initBuscador(){

    Buscador* novo = malloc(sizeof(*novo));

    novo->listaPaginas = criaLista();
    novo->hashPaginas = inicializaHash(TAMHASH);
    novo->hashSW = inicializaHash(TAMHASH);
    novo->mapaPalavraPaginas = inicializaRBT();
    novo->numPaginas = 0;

    return novo;

}

void LePaginas(Buscador* buscador){
    FILE* index = fopen("../index.txt", "r");

    char nomePagina[TAM_WORD];

    while(fscanf(index, "%s\n", nomePagina) == 1){
        Pagina* pagina = inicializaPagina(nomePagina);
        acessaHash(buscador->hashPaginas,
                   (int (*)(void *, int)) hashPagina,
                   (int (*)(void *, void *)) comparaPagina,
                   pagina);
        buscador->listaPaginas = insereLista(buscador->listaPaginas,pagina);
        buscador->numPaginas++;
    }

    fclose(index);
}


static void stringLower(char* palavra){
    for(int i = 0; i < strlen(palavra); i++) palavra[i] = (char) tolower(palavra[i]);
}

static void leStopWords(Buscador* buscador){
    FILE* filesw = fopen("../stopwords.txt", "r");

    char palavra[30];
    while(fscanf(filesw, "%s\n", palavra) == 1){
        StopWord * sw = inicializaStopWord(palavra);
        acessaHash(buscador->hashSW, (int (*)(void *, int)) hashStopWord, (int (*)(void *, void *)) comparaStopWord, sw);
    }
    fclose(filesw);
}

void MapeiaPalavras(Buscador * buscador){

    leStopWords(buscador);

    for(Lista * l = buscador->listaPaginas; l != NULL; l= retornaProx(l) ) {
        Pagina* p = retornaItem(l);

        char filename[50] = "";
        strcpy(filename, "pages/");
        strcat(filename, getNome(p));

        FILE* file = fopen(filename, "r");
        if(file == NULL){
            printf("Erro na abertura de arquivo\n");
            exit(1);
        }

        char palavra[TAM_WORD];
        while(fscanf(file,"%s ", palavra) == 1) {
            stringLower(palavra);
            StopWord *PossivelSW = inicializaStopWord(palavra);
            if (!buscaHash(buscador->hashSW, (int (*)(void *, int)) hashStopWord, (int (*)(void *, void *)) comparaStopWord,PossivelSW)) {
                buscador->mapaPalavraPaginas = insereRBT(buscador->mapaPalavraPaginas, p, palavra);
            }
            liberaStopWord(PossivelSW);
        }
    }

    //neste momento Hash de StopWords pode ser liberada
    liberaHash(buscador->hashSW,liberaStopWord);
}

void imprimeBuscador(Buscador* buscador){

    printf("O buscador possui %d paginas\n\n",buscador->numPaginas);

    printf("Lista de paginas\n\n");
    percorreLista(buscador->listaPaginas,imprimePagina,0);

    printf("\n\nHash de paginas\n\n");
    imprimeHash(buscador->hashPaginas,imprimePagina);

    printf("\n\nHash de Stopwords\n\n");
    imprimeHash(buscador->hashSW,imprimeStopWord);

    printf("\n\nMapa de Palavras\n\n");
    imprimeRBT(buscador->mapaPalavraPaginas);

}

void LiberaBuscador(Buscador *b){
    percorreLista(b->listaPaginas,liberaPagina,0);
    liberaLista(b->listaPaginas);
    liberaHash(b->hashPaginas,NULL);
    liberaRBT(b->mapaPalavraPaginas);
    free(b);
}