#include <stdio.h>
#include <string.h>
#include "pagina.h"
#include "lista.h"

void leIndex(Lista* paginas){
    FILE* index = fopen("index.txt", "r");

    char nomePagina[30];

    while(fscanf(index, "%s\n", nomePagina) == 1){
        Pagina* pagina = inicializaPagina(nomePagina);
        insereLista(paginas, pagina);

        imprimePagina(pagina);
    }

    fclose(index);
}

void leStopWords(){

}

void leGrafo(){

}

int main(int argc, char* argv[]){
    Lista* paginas = inicializaLista();
    leIndex(paginas);

    return 0;
}