//
// Created by bonella on 26/04/2021.
//

#ifndef TRABALHO_3_DE_ED2_STOPWORD_H
#define TRABALHO_3_DE_ED2_STOPWORD_H

typedef struct stopWord StopWord;

StopWord* inicializaStopWord(char*);
int hashStopWord(StopWord*, int);
int comparaStopWord(StopWord*, StopWord*);
void liberaStopWord(StopWord*);

#endif //TRABALHO_3_DE_ED2_STOPWORD_H
