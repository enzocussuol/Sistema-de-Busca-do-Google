#include <stdio.h>
#include "pagina.h"
#include "Lista.h"
#include "tabelaHash.h"
#include "stopword.h"
#include "RedBlackTree.h"

//Le a lista de paginas presentes em index.txt
Lista* leIndex(Lista* paginas){
    FILE* index = fopen("../index.txt", "r");

    char nomePagina[30];

    while(fscanf(index, "%s\n", nomePagina) == 1){
        Pagina* pagina = inicializaPagina(nomePagina);
        paginas = insereLista(paginas, pagina);
    }

    fclose(index);
    return paginas;
}

void leStopWords(Hash* h){
    FILE* filesw = fopen("../stopwords.txt", "r");

    char palavra[30];

    while(fscanf(filesw, "%s\n", palavra) == 1){
        StopWord * sw = inicializaStopWord(palavra);
        acessaHash(h, (int (*)(void *, int)) hashStopWord, (int (*)(void *, void *)) comparaStopWord, sw);
    }

    fclose(filesw);
}

void leGrafo(){

}

int main(int argc, char* argv[]){
    Lista* paginas = criaLista();
    paginas = leIndex(paginas);

    Hash* hashSW = inicializaHash(7);
    leStopWords(hashSW);
    imprimeHash(hashSW, (void (*)(void *, void *)) imprimeStopWord);

    RBT* mapaPalavraPaginas = inicializaRBT();

    liberaLista(paginas);
    return 0;
}