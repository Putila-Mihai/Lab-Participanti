//
// Created by ultra on 17.03.2023.
//

#ifndef LAB2_4_ENTITIES_H
#define LAB2_4_ENTITIES_H

typedef struct {
    char *nume;
    char *prenume;
    int scor;
} Concurent;

/*
 * create an participant object
 * nume: first name of participant
 * prenume: second name o participant
 * score: participant's score
 * return: Participant
 */
Concurent *create_concurent(char *nume, char *prenume, int scor);

Concurent* copy_concurent(Concurent* c);

//void destroy_concurent(Concurent* p);

void destroy_c(Concurent *c);

void test_CreateDestroy();

/*
 * check if an concurent it 's valid
 */
int valideaza(Concurent p);

/*
 * dezaloca numele si prenumele unui concurent
 */
int getscor(Concurent *p);

void setscor(Concurent *p, int scor);

char *getprenume(Concurent *p);

char *getnume(Concurent *p);

void setnume(Concurent *p, char *nume);

void setprenume(Concurent *p, char *prenume);

void test_getset();

#endif //LAB2_4_ENTITIES_H
