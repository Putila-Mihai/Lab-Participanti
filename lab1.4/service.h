//
// Created by ultra on 17.03.2023.
//

#ifndef LAB2_4_SERVICE_H
#define LAB2_4_SERVICE_H

#include "repo.h"

/*
 * add a elem to the list
 * l: the list of participants
 * nume: first name of participant
 * prenume: second name of participant
 * scor: the score obtained
 */
int addC(repo *l, char *nume, char *prenume, int scor);

/*
 * return all elements
 * l: the list of participants
 */
repo* getAllC(repo *l);

/*
 * update a participant's score
 * l: the list of participants
 * nume: first name of participant
 * prenume: second name o participant
 * return: 1(Participant updated) or 0(participant don t exist)
 */
int updateS(repo *l, char *nume, char *prenume, int scor);

/*
 * delete a participant from the list
 * l: the list of participants
 * nume: first name of participant
 * prenume: second name o participant
 * return: 1(Participant updated) or 0(participant don t exist)
 */
int deleteS(repo *l, char *nume, char *prenume);

/*
 * functia filtreaza oncurentii ce au peste un anumit scor
 * returneaza lista de concurenti
 */
repo* filters(repo *l, int scor);

/*
 * functia sorteazeaza crescator lista de concurenti dupa scor
 * returnee lista de concurenti sortata
 */
repo* sorts(repo *l);

/*
 * functia sorteaza dupa o functie de comparare data
 */
typedef int(*FunctieComparare)(Concurent *c1, Concurent *c2);

/*
 * functia sorteaza lista dupa o proprietate(functie data ca si paramentru)
 * FunctieComparare este funtia data
 */
void sort_given(repo *l, FunctieComparare cmp);

/*
 * functia verifica daca c1 este mai mare decat c2
 * return : 1 daca e mai mic si 0 daca e mai mare
 */
int reverse(Concurent *c1, Concurent *c2);

void testreverse();

void testaddC();

#endif //LAB2_4_SERVICE_H
