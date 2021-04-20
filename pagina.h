#ifndef PAGINA_H
    #define PAGINA_H

    typedef struct pagina Pagina;
    
    Pagina* inicializaPagina(char*);
    char* getNome(Pagina*);
    double getRank(Pagina*);
    void setRank(Pagina*, double);
    void imprimePagina(Pagina*);
    void liberaPagina(Pagina*);
#endif