#ifndef PAGINA_H
    #define PAGINA_H

    typedef struct pagina Pagina;
    
    Pagina* inicializaPagina(char*,int);
    char* getNome(Pagina*);
    double getRank(Pagina*);
    int getID(Pagina* p);
    void setRank(Pagina*, double);
    int hashNomePagina(char*, int);
    int hashPagina(Pagina*, int);
    int comparaPagina(Pagina*, Pagina*);
    int comparaNome(Pagina*, char*);
    int cmpPRPaginas(const void*, const void*);
    void imprimePagina(Pagina*);
    void liberaPagina(Pagina*);
#endif