#include "lista.h"

struct celula{
    Pagina* pagina;
    Celula* proxCel;
};

struct lista{
    Celula* primCel;
    Celula* ultCel;
    int tam;
};