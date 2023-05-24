//
// Created by ultra on 17.03.2023.
//

#ifndef LAB2_4_REPO_H
#define LAB2_4_REPO_H

#include "entities.h"

typedef void* TElem;
typedef void (*DestroyFunction)(TElem);
typedef TElem (*CopyFct) (TElem);
typedef struct {
    TElem *elements;
    int lengh;
} repo;

/*
 * Create an empty list
 */
repo* createEmpty();

/*
 * Destroy list
 */
void destroy(repo *l,DestroyFunction destFct);

/*
 * return the number of elements in the list
 */
int size(repo *l);

/*
 * add an elem to the repo
 * l: list of participants
 */
void add(repo *l, TElem el);

/*
 * get the elemnet on poz from the list
 */
TElem get(repo *l, int poz);

/*
 *make a copy of the exact same elements of the list
 */
repo* copylist(repo *l,CopyFct copy);

TElem removelast(repo* l);

void destroy_lista(repo* l);

void testCreateList();

void testIterateList();

void testCopyList();

void test_lista_liste();

#endif //LAB2_4_REPO_H
