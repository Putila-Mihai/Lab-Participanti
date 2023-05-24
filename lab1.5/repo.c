//
// Created by ultra on 17.03.2023.
//
#include "repo.h"

#include <assert.h>
#include <string.h>
#include<stdlib.h>

/*
 * create an empty list
 */
repo* createEmpty() {
    repo* rez =malloc(sizeof(repo));
    rez->elements = (TElem *) malloc(30 * sizeof(TElem));
    rez->lengh = 0;
    return rez;
}

/*
 * destroy the list
 */
void destroy(repo *l,DestroyFunction destFct) {
    for(int i=0;i<size(l);i++)
    {
        destFct((l->elements[i]));
    }
    free(l->elements);
    l->lengh = 0;
}

int size(repo *l) {
    return l->lengh;
}

void add(repo *l, TElem el) {
    l->elements[l->lengh] = el;
    l->lengh++;
}

TElem get(repo *l, int poz) {
    return l->elements[poz];
}

repo* copylist(repo *l,CopyFct copy) {
    repo* rez = createEmpty();
    for (int i = 0; i < size(l); i++) {
        TElem c = get(l, i);
        add(rez, copy(c));
    }
    return rez;
}

void destroy_lista(repo* l){
    destroy(l,destroy_c);
}

TElem removelast(repo* l){
    TElem rez= l->elements[l->lengh -1 ];
    l->lengh -=1;
    return rez;
}

void testCopyList() {
    repo* l = createEmpty();
    add(l, create_concurent("a", "b", 20));
    add(l, create_concurent("c", "d", 30));
    repo* l2 = copylist(l,copy_concurent);
    assert(size(l2) == 2);
    Concurent* c = get(l2, 1);
    assert(c->scor == 30);
    destroy(l,destroy_c);
    free(l2->elements);
    free(l2);

}

void testCreateList() {
    repo* l = createEmpty();
    assert(size(l) == 0);
    destroy(l,destroy_c);
}
void test_lista_liste(){
    repo* concurenti =createEmpty();
    add(concurenti, create_concurent("Mihai","alex",22));
    add(concurenti, create_concurent("ema","ale",23));
    repo* concurenti2 = createEmpty();
    repo* undo_list = createEmpty();
    add(undo_list,concurenti);
    assert(size(undo_list)==1);
    add(undo_list,concurenti2);
    assert(size(undo_list)==2);
    destroy(undo_list,destroy_lista);

}
void testIterateList() {
    repo* l = createEmpty();
    add(l, create_concurent("a", "b", 20));
    add(l, create_concurent("c", "d", 30));
    assert(size(l) == 2);
    Concurent* c = l->elements[0];
    Concurent* b = removelast(l);
    assert(b->scor == 30);
    assert(strcmp(c->nume, "a") == 0);
    c = l->elements[1];
    assert(strcmp(c->prenume, "d") == 0);
    destroy(l,destroy_c);
    assert(size(l) == 0);

}