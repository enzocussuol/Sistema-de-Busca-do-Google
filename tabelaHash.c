//
// Created by bonella, enzo, danilo on 26/04/2021.
//

#include "tabelaHash.h"
#include "pagina.h"

struct tabelahash{
    Lista** conteudo;
    int tam;
    int qtdItens;
    int k;
};

//Calcula um tamanho primo para uma Hash a partir de um parametro K
//Formula: tam = 2^k - delta
static int calculaTamHash(int k){
    char deltaK[27] = {1, 3, 1, 5, 3, 3, 9, 3, 1, 3, 19, 15, 1, 5, 1, 3, 9, 3, 15, 3, 39, 5, 39, 57, 3, 35, 1};

    return pow(2, k) - deltaK[k - 5];
}

//Inicializa uma hash vazia
Hash * inicializaHash(int k){
    Hash * novaHash = (Hash*) malloc(sizeof(Hash));

    novaHash->k = k;
    novaHash->tam = calculaTamHash(novaHash->k);

    novaHash->conteudo = (Lista**) malloc(sizeof(Lista*) * novaHash->tam);
    novaHash->qtdItens = 0;

    for(int i = 0; i < novaHash->tam; i++){
        novaHash->conteudo[i] = criaLista();
    }

    return novaHash;
}

//Expande uma hash, criando uma nova hash e liberando a antiga
Hash* resizeHash(Hash* hashAntiga, int findHash(void*, int), int compare(void*, void*)){
    Hash* novaHash = inicializaHash(hashAntiga->k + 1);
    novaHash->qtdItens = hashAntiga->qtdItens;

    for(int i = 0; i < hashAntiga->tam; i++){
        if(hashAntiga->conteudo[i] != NULL){
            for(Lista* l = hashAntiga->conteudo[i]; l != NULL; l = retornaProx(l)){
                acessaHash(novaHash, findHash, compare, retornaItem(l));
            }
        }
    }

    liberaHash(hashAntiga, NULL);

    return novaHash;
}

//Calcula a densidade de uma tabela hash
int calculaDensidade(Hash* hash){
    return hash->qtdItens/hash->tam;
}

//Retorna a quantidade de itens dentro da hash
int retornaItensAtivosHash(Hash* h){
    return h->qtdItens;
}

//Retorna o parametro K, que calcula o tamanho da Hash
int retornaKHash(Hash* hash){
    return hash->k;
}

//Insere um novo dado na hash, e caso já exista indica sua existencia
int acessaHash(Hash * hash, int findHash(void*, int), int compare(void*, void*), void * dado){
    int pos = findHash(dado, hash->tam);

    int flag = percorreLista(hash->conteudo[pos],compare,dado);
    if(flag) return 1;

    hash->conteudo[pos] = insereLista(hash->conteudo[pos],dado);
    hash->qtdItens++;
    return 0;
}

//Verifica a existencia de um dado dentro da tabela Hash
int buscaHash(Hash * hash, int findHash(void*, int), int compare(void*, void*), void * dado){
    int pos = findHash(dado, hash->tam);

    int flag = percorreLista(hash->conteudo[pos],compare,dado);
    if(flag) return 1;

    return 0;
}

//Retorna o dado que esta se buscando
void* buscaDadoHash(Hash * hash, int findHash(void*, int), int compare(void*, void*), void * dado){
    int pos = findHash(dado, hash->tam);

    void* flag = percorreListaRetornaDado(hash->conteudo[pos],compare,dado);
    if(flag) return flag;

    return 0;
}

int retornaTam(Hash* hash){
    return hash->tam;
}

// Imprime as paginas de forma ordenada pelo PageRank
static void imprimeInterseccao(Pagina ** vetPaginas, int tam){
    qsort(vetPaginas, tam, sizeof(vetPaginas[0]), cmpPRPaginas);

    printf("pages:");
    for(int i = 0; i < tam; i++){
        printf("%s ", getNome(vetPaginas[i]));
    }
    printf("\n");
    printf("pr:");
    for(int i = 0; i < tam; i++){
        printf("%.8f ", getRank(vetPaginas[i]));
    }
    printf("\n");
}

//Acha a intersecçao entre hashs usando suas caracteristicas
void Interseccao(Lista* listadeHashs,Hash* menosItens){
    Lista* intersec = criaLista();
    int condicao, max , tam = 0;
    for(int i = 0 ; i < menosItens->tam ; i++){
        Pagina* a = NULL;
        if(menosItens->conteudo[i] != NULL){
            for(Lista * list = menosItens->conteudo[i]; list != NULL; list = retornaProx(list)){ //percorre toda a lista da posicao I da hash
                a = retornaItem(list); // a = pagina atual da lista
                condicao = 0; //Indica a quantidade de palavras que foi achadada na pagina
                max = 0; //Indica o total de palavras que foi buscada
                for(Lista* l = listadeHashs; l!=NULL; l= retornaProx(l)) {
                    if (retornaItem(l) != menosItens) {
                        condicao += buscaHash(retornaItem(l), (int (*)(void *, int)) hashPagina,
                                              (int (*)(void *, void *)) comparaPagina, a);
                        max++;
                    }
                }
                if(condicao == max){ // Insira caso a pagina contenha todas palavras buscadas
                    intersec = insereLista(intersec,a);
                    tam++;
                }
            }
        }
    }
    Pagina* vet[tam];
    int pos = 0;
    //converte lista em vetor
    for(Lista* l = intersec; l != NULL; l = retornaProx(l)){
        vet[pos] = retornaItem(l);
        pos++;
    }

    //caso exista interseccao imprime ordenado
    if(tam>0){
        imprimeInterseccao(vet,tam);
    }
    else{
        printf("pages:\n");
        printf("pr:\n");
    }
    liberaLista(intersec);
}

void liberaHash(Hash * hash,int (*cb)(void*,void*)){
    for(int i = 0; i < hash->tam; i++){
        if(cb != NULL){
            percorreLista(hash->conteudo[i],cb,NULL);
        }

        liberaLista(hash->conteudo[i]);
    }

    free(hash->conteudo);
    free(hash);
}
