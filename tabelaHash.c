//
// Created by bonella on 26/04/2021.
//

#include "tabelaHash.h"
#include "pagina.h"

struct tabelahash{
    Lista** conteudo;
    int tam;
    int qtdItens;
};

Hash * inicializaHash(int tam){
    Hash * novaHash = (Hash*) malloc(sizeof(Hash));
    novaHash->conteudo = (Lista**) malloc(sizeof(Lista*) * tam);
    novaHash->qtdItens = 0;
    for(int i = 0; i < tam; i++){
        novaHash->conteudo[i] = criaLista();
    }
    novaHash->tam = tam;

    return novaHash;
}

int retornaItensAtivosHash(Hash* h){
    return h->qtdItens;
}

int acessaHash(Hash * hash, int findHash(void*, int), int compare(void*, void*), void * dado){
    int pos = findHash(dado, hash->tam);

    int flag = percorreLista(hash->conteudo[pos],compare,dado);
    if(flag) return 1;

    hash->conteudo[pos] = insereLista(hash->conteudo[pos],dado);
    hash->qtdItens++;
    return 0;
}

int buscaHash(Hash * hash, int findHash(void*, int), int compare(void*, void*), void * dado){
    int pos = findHash(dado, hash->tam);

    int flag = percorreLista(hash->conteudo[pos],compare,dado);
    if(flag) return 1;

    return 0;
}

void* buscaDadoHash(Hash * hash, int findHash(void*, int), int compare(void*, void*), void * dado){
    int pos = findHash(dado, hash->tam);

    void* flag = percorreListaRetornaDado(hash->conteudo[pos],compare,dado);
    if(flag) return flag;

    return 0;
}

int retornaTam(Hash* hash){
    return hash->tam;
}

static void imprimeInterseccao(Pagina ** vetPaginas, int tam){
    qsort(vetPaginas, tam, sizeof(vetPaginas[0]), cmpPRPaginas);

    for(int i = 0; i < tam; i++){
        printf("%s ", getNome(vetPaginas[i]));
    }
    printf("\n");
    for(int i = 0; i < tam; i++){
        printf("%.8f ", getRank(vetPaginas[i]));
    }
    printf("\n");
}

void Interseccao(Lista* listadeHashs,Hash* menosItens){
    Lista* intersec = criaLista();
    int condicao, max , tam = 0;
    for(int i = 0 ; i < menosItens->tam ; i++){
        Pagina* a = NULL;
        if(menosItens->conteudo[i] != NULL){
            for(Lista * list = menosItens->conteudo[i]; list != NULL; list = retornaProx(list)){ //percorre toda a lista da posicao I da hash
                a = retornaItem(list); // a = pagina atual da lista
                condicao = 0;
                max = 0;
                for(Lista* l = listadeHashs; l!=NULL; l= retornaProx(l)){
                    if(retornaItem(l) != menosItens){
                        condicao += buscaHash(retornaItem(l), (int (*)(void *, int)) hashPagina,
                                              (int (*)(void *, void *)) comparaPagina, a);
                        max++;
                    }
                }
                //printf("cond = %d, menosItensQtd %d", condicao, menosItens->qtdItens);
                if(condicao == max){
                    intersec = insereLista(intersec,a);
                    tam++;
                }
            }
        }
    }
    Pagina* vet[tam];
    int pos = 0;
    for(Lista* l = intersec; l != NULL; l = retornaProx(l)){
        //imprimePagina(retornaItem(l));
        vet[pos] = retornaItem(l);
        pos++;
    }
    //printf("\n");
    if(tam>0){
        imprimeInterseccao(vet,tam);
    }
    liberaLista(intersec);
}

void liberaHash(Hash * hash,int (*cb)(void*,void*)){
    for(int i = 0; i < hash->tam; i++){
        if(cb != NULL){
            percorreLista(hash->conteudo[i],cb,0);
        }

        liberaLista(hash->conteudo[i]);
    }

    free(hash->conteudo);
    free(hash);
}

void imprimeHash(Hash *hash, void funcaoImprime(void *,void*)){
    //printf("tamanho da hash: %d\n", hash->tam);
    for(int i=0; i<hash->tam; i++){
        //printf("Pos %d da hash\n", i);
        percorreLista(hash->conteudo[i], (int (*)(void *, void *)) funcaoImprime, NULL);
    }
}