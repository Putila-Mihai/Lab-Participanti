//
// Created by ultra on 17.03.2023.
//

#ifndef LAB2_4_SERVICE_H
#define LAB2_4_SERVICE_H

#include "repo.h"

typedef struct {
    repo* all;
    repo* undo;//list of list of pets
} Concurs;
/*
 * add a elem to the list
 * l: the list of participants
 * nume: first name of participant
 * prenume: second name of participant
 * scor: the score obtained
 */
int addC(Concurs* l, char *nume, char *prenume, int scor);

int undo(Concurs* l);


Concurs create_concurs();
void destroyConcurs(Concurs* c);
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
int updateS(Concurs *l, char *nume, char *prenume, int scor);

/*
 * delete a participant from the list
 * l: the list of participants
 * nume: first name of participant
 * prenume: second name o participant
 * return: 1(Participant updated) or 0(participant don t exist)
 */
int deleteS(Concurs *l, char *nume, char *prenume);

/*
 * functia filtreaza oncurentii ce au peste un anumit scor
 * returneaza lista de concurenti
 */
repo* filters(Concurs *l, int scor);

/*
 * functia sorteazeaza crescator lista de concurenti dupa scor
 * returnee lista de concurenti sortata
 */
repo* sorts(Concurs *l);

/*
 * functia sorteaza dupa o functie de comparare data
 */
typedef int(*FunctieComparare)(Concurent *c1, Concurent *c2);

/*
 * functia sorteaza lista dupa o proprietate(functie data ca si paramentru)
 * FunctieComparare este funtia data
 */
repo* sort_given(Concurs *l, FunctieComparare cmp);

/*
 * functia verifica daca c1 este mai mare decat c2
 * return : 1 daca e mai mic si 0 daca e mai mare
 */
int reverse(Concurent *c1, Concurent *c2);

void testreverse();

void testaddC();

void test_undo();
void test_sort();
repo* sort_name_service(Concurs* l);
#endif //LAB2_4_SERVICE_H
