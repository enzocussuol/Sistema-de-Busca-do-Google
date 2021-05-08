//
// Created by bonella on 01/05/2021.
//

#include "Buscador.h"

#define TAM_WORD 50
#define HASHK 7
#define MAX_DENSIDADE 8

struct buscador{
    Lista* listaPaginas;
    Hash* hashPaginas;
    int numPaginas;
    Hash* hashSW;
    RBT* mapaPalavra;
};

Buscador* initBuscador(){

    Buscador* novo = malloc(sizeof(*novo));

    novo->hashPaginas = inicializaHash(HASHK);
    novo->hashSW = inicializaHash(HASHK);
    novo->listaPaginas = criaLista();
    novo->mapaPalavra = inicializaRBT();
    novo->numPaginas = 0;

    return novo;

}

Lista* retornaListaPaginas(Buscador* b){
    return b->listaPaginas;
}

Hash* retornaHashPaginas(Buscador* b){
    return b->hashPaginas;
}

int retornaNumPaginas(Buscador* b){
    return b->numPaginas;
}

RBT* retornaRBT(Buscador* b){
    return b->mapaPalavra;
}

void LePaginas(Buscador* buscador){
    FILE* index = fopen("index.txt", "r");

    char nomePagina[TAM_WORD];
    int i = 0;
    while(fscanf(index, "%s\n", nomePagina) == 1){
        Pagina* pagina = inicializaPagina(nomePagina,i);
        buscador->listaPaginas = insereLista(buscador->listaPaginas,pagina);
        acessaHash(buscador->hashPaginas,
                   (int (*)(void *, int)) hashPagina,
                   (int (*)(void *, void *)) comparaPagina,
                   pagina);
        buscador->numPaginas++;
        i++;

        if(calculaDensidade(buscador->hashPaginas) > MAX_DENSIDADE) buscador->hashPaginas = resizeHash(buscador->hashPaginas,
                                                            (int (*)(void *, int)) hashPagina,
                                                            (int (*)(void *, void *)) comparaPagina);
    }

    fclose(index);
}


static void stringLower(char* palavra){
    for(int i = 0; i < strlen(palavra); i++) palavra[i] = (char) tolower(palavra[i]);
}

static void leStopWords(Buscador* buscador){
    FILE* filesw = fopen("stopwords.txt", "r");

    char palavra[30];
    while(fscanf(filesw, "%s\n", palavra) == 1){
        StopWord * sw = inicializaStopWord(palavra);
        if(acessaHash(buscador->hashSW, (int (*)(void *, int)) hashStopWord, (int (*)(void *, void *)) comparaStopWord, sw)){
            liberaStopWord(sw);
        }

        if(calculaDensidade(buscador->hashSW) > MAX_DENSIDADE) buscador->hashSW = resizeHash(buscador->hashSW,
                                                            (int (*)(void *, int)) hashPagina,
                                                            (int (*)(void *, void *)) comparaPagina);
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
                buscador->mapaPalavra = insereRBT(buscador->mapaPalavra, p, palavra);
            }
            liberaStopWord(PossivelSW);
        }
        fclose(file);
    }

    //neste momento Hash de StopWords pode ser liberada
    liberaHash(buscador->hashSW, (int (*)(void *, void *)) liberaStopWord);

}

void imprimeBuscador(Buscador* buscador){

    printf("O buscador possui %d paginas\n\n",buscador->numPaginas);

//    printf("Lista de paginas\n\n");
//    percorreLista(buscador->listaPaginas, (int (*)(void *, void *)) imprimePagina, NULL);

//    printf("\n\nHash de paginas\n\n");
//    imprimeHash(buscador->hashPaginas, (void (*)(void *, void *)) imprimePagina);
//
//    printf("\n\nHash de Stopwords\n\n");
//    imprimeHash(buscador->hashSW, (void (*)(void *, void *)) imprimeStopWord);

    printf("\n\nMapa de Palavras\n\n");
    imprimeRBT(buscador->mapaPalavra);

}

void buscadordeTermos(Buscador*b,char* buffer){

    Lista * listaPalavras = criaLista();

    char palavra[TAM_WORD];
    char separador = ' ';
    int flag = 1;
    Lista* listaHash = criaLista();
    Hash* menorHash;

    buffer[strlen(buffer)-1] = '\0'; //retirna o \n lido pelo getline

    char* str = strtok(buffer, " "); //separa as strings pelo espaço

    int j = 0;
    while(str != NULL){
        Lista* aux2 = NULL;
        Hash* aux = inicializaHash(retornaKHash(b->hashPaginas));
        stringLower(str);
        aux2 = buscaRBTLista(b->mapaPalavra,str);

        if(aux2 == NULL){
            printf("Termo %s nao esta mapeado\n",str);
            flag = 0;
            break;
        }

        for(Lista* l = aux2;l != NULL;l= retornaProx(l)){
            acessaHash(aux, (int (*)(void *, int)) hashPagina, (int (*)(void *, void *)) comparaPagina, retornaItem(l));
        }

        if(j==0) menorHash = aux;
        if(retornaItensAtivosHash(aux) < retornaItensAtivosHash(menorHash)) menorHash = aux;

        listaHash = insereLista(listaHash,aux);

        j++;
        str = strtok(NULL, " "); // le o proximo string
    }


    if(flag) Interseccao(listaHash,menorHash);
    percorreLista(listaHash, (int (*)(void *, void *)) liberaHash, NULL);
    liberaLista(listaHash);
}


void LiberaBuscador(Buscador *b){
    percorreLista(b->listaPaginas, (int (*)(void *, void *)) liberaPagina, NULL);
    liberaLista(b->listaPaginas);
    liberaHash(b->hashPaginas,NULL);
    liberaRBT(b->mapaPalavra);
    free(b);
}