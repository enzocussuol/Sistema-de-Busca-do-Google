//
// Created by bonella on 01/05/2021.
//

#include "Buscador.h"

#define TAM_WORD 50
#define TAMHASH 109

struct buscador{
    Lista* listaPaginas;
    Hash* hashPaginas;
    int numPaginas;
    Hash* hashSW;
    RBT* mapaPalavra;
};

Buscador* initBuscador(){

    Buscador* novo = malloc(sizeof(*novo));

    novo->listaPaginas = criaLista();
    //novo->hashPaginas = inicializaHash(TAMHASH);
    novo->hashSW = inicializaHash(TAMHASH);
    novo->mapaPalavra = inicializaRBT();
    novo->numPaginas = 0;

    return novo;

}

static void initHashPaginas(Buscador* b,int tam){
    b->hashPaginas = inicializaHash(tam);
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
        buscador->numPaginas++;
        i++;
    }
    initHashPaginas(buscador,i*1.3);
    for(Lista* l = buscador->listaPaginas;l!= NULL ; l = retornaProx(l)){
        acessaHash(buscador->hashPaginas,
                   (int (*)(void *, int)) hashPagina,
                   (int (*)(void *, void *)) comparaPagina,
                   retornaItem(l));
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
        Hash* aux = NULL;
        stringLower(str);
        aux = buscaRBTHash(b->mapaPalavra,str);

        if(aux == NULL){
            printf("Termo %s nao esta mapeado\n",str);
            flag = 0;
            break;
        }

        if(j==0) menorHash = aux;
        if(retornaItensAtivosHash(aux) < retornaItensAtivosHash(menorHash)) menorHash = aux;

        listaHash = insereLista(listaHash,aux);

        j++;
        str = strtok(NULL, " "); // le o proximo string
    }


    if(flag) Interseccao(listaHash,menorHash);
    liberaLista(listaHash);
}


void LiberaBuscador(Buscador *b){
    percorreLista(b->listaPaginas, (int (*)(void *, void *)) liberaPagina, NULL);
    liberaLista(b->listaPaginas);
    liberaHash(b->hashPaginas,NULL);
    liberaRBT(b->mapaPalavra);
    free(b);
}