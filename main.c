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

void stringLower(char* palavra){
    for(int i = 0; i < strlen(palavra); i++) palavra[i] = (char) tolower(palavra[i]);
}

// Preenche a rbt com as paginas de cada palavra
RBT* Mapeia(Lista * paginas,Hash* h, RBT * rbt){
    Lista* l;
    for(l = paginas; l!= NULL; l = retornaProx(l)) {
        Pagina *p = retornaItem(l);

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
            if (!buscaHash(h, (int (*)(void *, int)) hashStopWord, (int (*)(void *, void *)) comparaStopWord,PossivelSW)) {
                rbt = insereRBT(rbt, p, palavra);
            }
            liberaStopWord(PossivelSW);
        }
    }

    return rbt;
}

int main(int argc, char* argv[]){
    Lista* paginas = criaLista();
    paginas = leIndex(paginas);

    Hash* hashSW = inicializaHash(7);
    leStopWords(hashSW);
    imprimeHash(hashSW, (void (*)(void *, void *)) imprimeStopWord);

    RBT* mapaPalavraPaginas = inicializaRBT();
    mapaPalavraPaginas = Mapeia(paginas, hashSW, mapaPalavraPaginas);

    printf("Digite o texto que deseja buscar:\n");

    Lista * listaPalavras = criaLista();
    char palavra[TAM_WORD];
    char separador = ' ';

    for(int j = 0; separador != '\n'; j++){
        scanf("%s%c", palavra, &separador);
        listaPalavras = insereLista(listaPalavras, strdup(palavra));
    }

    liberaLista(paginas);
    liberaHash(hashSW);
    liberaRBT(mapaPalavraPaginas);

    return 0;
}