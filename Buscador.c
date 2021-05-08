//
// Created by bonella,enzo,danilo on 01/05/2021.
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

//le o arquivo index.txt e adiciona as paginas lidas no hash e lista de paginas
void LePaginas(Buscador* buscador,char* diretorio){
    char path[200];
    strcpy(path, diretorio);
    strcat(path,"index.txt");
    FILE* index = fopen(path, "r");
    if(index == NULL){
        perror("Erro ao abrir arquivo index\n");
        exit(1);
    }

    char nomePagina[TAM_WORD];
    int i = 0;
    while(fscanf(index, "%s\n", nomePagina) == 1){
        Pagina* pagina = inicializaPagina(nomePagina,i);

        //adiciona a pagina em uma lista
        buscador->listaPaginas = insereLista(buscador->listaPaginas,pagina);

        //adiciona pagina em uma hash
        acessaHash(buscador->hashPaginas,
                   (int (*)(void *, int)) hashPagina,
                   (int (*)(void *, void *)) comparaPagina,
                   pagina);
        buscador->numPaginas++;
        i++;

        //caso a densidade seja maior que a tolerada é preciso fazer rehash
        if(calculaDensidade(buscador->hashPaginas) > MAX_DENSIDADE)buscador->hashPaginas = resizeHash(buscador->hashPaginas,
                                                            (int (*)(void *, int)) hashPagina,
                                                            (int (*)(void *, void *)) comparaPagina);
    }

    fclose(index);
}

//converte um char* parar lower case
static void stringLower(char* palavra){
    for(int i = 0; i < strlen(palavra); i++) palavra[i] = (char) tolower(palavra[i]);
}

//funcao que le o arquivo stopwords.txt e adiciona em uma hash table
static void leStopWords(Buscador* buscador, char * diretorio){
    char path[200];
    strcpy(path, diretorio);
    strcat(path, "stopwords.txt");
    FILE* filesw = fopen(path, "r");

    char palavra[30];
    while(fscanf(filesw, "%s\n", palavra) == 1){
        StopWord * sw = inicializaStopWord(palavra);
        //caso a palavra seja repetida ela nao e adicionada
        if(acessaHash(buscador->hashSW, (int (*)(void *, int)) hashStopWord, (int (*)(void *, void *)) comparaStopWord, sw)){
            liberaStopWord(sw);
        }

        //caso a densidade seja maior que a tolerada é preciso fazer rehash
        if(calculaDensidade(buscador->hashSW) > MAX_DENSIDADE) buscador->hashSW = resizeHash(buscador->hashSW,
                                                            (int (*)(void *, int)) hashPagina,
                                                            (int (*)(void *, void *)) comparaPagina);
    }
    fclose(filesw);
}

//Mapeia as palavras para que cada palavra esteja associada a uma lista de paginas
void MapeiaPalavras(Buscador * buscador, char* diretorio){

    //le as stopwords para nao adiciona-las ao mapa
    leStopWords(buscador,diretorio);

    //abre cada pagina a ser lida e percorre
    for(Lista * l = buscador->listaPaginas; l != NULL; l= retornaProx(l) ) {
        Pagina* p = retornaItem(l);

        char filename[200];
        strcpy(filename, diretorio);
        strcat(filename, "pages/");
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
            //caso a palavra nao seja stopword adiciona ela ao mapa
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

    int flag = 1; //flag caso uma palavra nao esteja mapeada
    Lista* listaHash = criaLista();
    Hash* menorHash;

    buffer[strlen(buffer)-1] = '\0'; //retirna o \n lido pelo getline

    char* str = strtok(buffer, " "); //separa as strings pelo espaço
    int j = 0;
    //strtok para separar as strings
    while(str != NULL){
        Lista* aux2 = NULL; //lista aux para obter a lista de paginas da palavra
        Hash* aux = inicializaHash(retornaKHash(b->hashPaginas)); //hash aux usada para fazer fast intersection
        stringLower(str);
        aux2 = buscaRBTLista(b->mapaPalavra,str); //busca na RBT as pagina onde existe a palavra buscada

        //caso nao tenha lista de paginas
        if(aux2 == NULL){
            //printf("Termo %s nao esta mapeado\n",str);
            flag = 0;
            break;
        }

        for(Lista* l = aux2;l != NULL;l= retornaProx(l)){ //percorre a lista adicionando na hash
            acessaHash(aux, (int (*)(void *, int)) hashPagina, (int (*)(void *, void *)) comparaPagina, retornaItem(l));
        }

        //definir qual a menor hash , ou seja, que tem menos itens
        if(j==0) menorHash = aux;
        if(retornaItensAtivosHash(aux) < retornaItensAtivosHash(menorHash)) menorHash = aux;

        listaHash = insereLista(listaHash,aux); //insere a hash aux na lista de hashs para achar intersecao
        j++;
        str = strtok(NULL, " "); // le o proximo string
    }


    if(flag) Interseccao(listaHash,menorHash); //caso todas palavras estejam mapeadas procura intersecao

    //libera as estruturas usadas na funcao
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