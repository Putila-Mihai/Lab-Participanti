//
// Created by ultra on 17.03.2023.
//
#include "service.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>


int addC(Concurs *l, char *nume, char *prenume, int scor) {
    Concurent *c = create_concurent(nume, prenume, scor);
    int succ = valideaza(*c);
    if (succ != 0) {
        free(c->nume);
        free(c->prenume);
        free(c);
        return succ;

    }
    repo *toUNDO = copylist(l->all, (CopyFct) copy_concurent);
    add(l->all, c);
    //add to undo list
    add(l->undo, toUNDO);
    return 0;
}

int undo(Concurs *l) {
    if (size(l->undo) == 0) {
        return 1; // no undo left
    }
    repo *list = removelast(l->undo);
    destroy_lista(l->all);
    l->all = list;
}

repo *getAllC(repo *l) {
    return copylist(l, copy_concurent);
}

int updateS(Concurs *l, char *nume, char *prenume, int scor) {
    repo *cp = getAllC(l->all);
    int ok = 0;
    for (int i = 0; i < size(cp); i++) {
        Concurent *x = get(cp, i);
        if (strcmp(x->nume, nume) == 0 && strcmp(x->prenume, prenume) == 0) {
            repo *toUndo = copylist(l->all, copy_concurent);
            add(l->undo, toUndo);
            setscor(l->all->elements[i], scor);
            ok = 1;
        }
    }
    destroy(cp, (DestroyFunction) destroy_c);
    return ok;

}

int deleteS(Concurs *l, char *nume, char *prenume) {
    repo *cp = getAllC(l->all);
    int ok = 0;
    for (int i = 0; i < size(cp); i++) {
        Concurent *x = get(cp, i);
        if (strcmp(x->nume, nume) == 0 && strcmp(x->prenume, prenume) == 0) {
            repo *toUNDO = copylist(l->all, copy_concurent);
            add(l->undo, toUNDO);
            destroy_c(l->all->elements[i]);
            for (int k = i; k < size(cp) - 1; k++) {
                l->all->elements[k] = l->all->elements[k + 1];

            }
            ok = 1;
            l->all->lengh--;
        }

    }
    free(cp->elements);
    free(cp);
    return ok;
}

repo *filters(Concurs *l, int scor) {
    repo *lista = createEmpty();
    for (int k = 0; k < size(l->all); k++) {
        Concurent *c = get(l->all, k);
        if (c->scor >= scor) {
            add(lista, create_concurent(c->nume, c->prenume, c->scor));
        }
    }
    return lista;
}

repo *sorts(Concurs *l) {
    repo *sorted = createEmpty();
    for (int k = 0; k < size(l->all); k++)
        add(sorted, create_concurent(getnume(l->all->elements[k]), getprenume(l->all->elements[k]),
                                     getscor(l->all->elements[k])));
    for (int k = 0; k < size(l->all) - 1; k++)
        for (int j = k; j < size(l->all); j++) {
            if (getscor(sorted->elements[k]) > getscor(sorted->elements[j])) {
                Concurent *aux = sorted->elements[k];
                sorted->elements[k] = sorted->elements[j];
                sorted->elements[j] = aux;
            }
        }
    return sorted;
}

repo *sort_given(Concurs *l, FunctieComparare cmp) {

    repo *sorted = createEmpty();
    sorted = copylist(l->all, copy_concurent);
    for (int i = 0; i < size(sorted) - 1; i++)
        for (int j = i + 1; j < size(sorted); j++) {
            Concurent *c1 = get(sorted, i);
            Concurent *c2 = get(sorted, j);
            if (cmp(c1, c2) == 1) {
                sorted->elements[i] = c2;
                sorted->elements[j] = c1;
            }

        }
    return sorted;

}

int reverse(Concurent *c1, Concurent *c2) {
    if (c1->scor < c2->scor) return 1;
    else return 0;
}

Concurs create_concurs() {
    Concurs rez;
    rez.all = createEmpty(destroy_c);
    rez.undo = createEmpty(destroy_lista);
    return rez;
}
repo* sort_name_service(Concurs* l){
    repo *sorted = createEmpty();
    sorted = copylist(l->all, copy_concurent);
    for (int i = 0; i < size(sorted) - 1; i++)
        for (int j = i + 1; j < size(sorted); j++) {
            Concurent *c1 = get(sorted, i);
            Concurent *c2 = get(sorted, j);
            if (strcmp(getnume(c1), getnume(c2)) > 0) {
                sorted->elements[i] = c2;
                sorted->elements[j] = c1;
            }

        }
    return sorted;
}

void test_undo() {
    Concurs l = create_concurs();
    addC(&l, "mihai", "alex", 12);
    addC(&l, "mi", "lex", 32);
    undo(&l);
    assert(size(l.all) == 1);
    undo(&l);
    assert(size(l.all) == 0);
    assert(undo(&l) != 0);
    destroyConcurs(&l);
}

void destroyConcurs(Concurs *c) {
    destroy_lista(c->all);
    destroy(c->undo, destroy_lista);
}

void testreverse() {
    Concurent *c1;
    Concurent *c2;
    c1 = create_concurent("Mihai", "alx", 31);
    c2 = create_concurent("Mihai", "alex", 30);
    assert(reverse(c1, c2) == 0);
    destroy_c(c1);
    destroy_c(c2);
}

void testaddC() {
    Concurs l = create_concurs();
    //invalid
    int error = addC(&l, "", "b", 10);
    assert(error != 0);
    assert(size(l.all) == 0);

    error = addC(&l, "a", "", 10);
    assert(error != 0);
    assert(size(l.all) == 0);
//
    error = addC(&l, "a", "b", 1001);
    assert(error != 0);
    assert(size(l.all) == 0);
    //valid

    addC(&l, "a", "b", 20);
    addC(&l, "a2", "b2", 40);
    repo *l2 = getAllC(l.all);
    assert(size(l2) == 2);
    assert(getscor(l2->elements[0]) == 20);
    //test update

    assert(updateS(&l, "a", "b", 30) == 1);
    assert(getscor(get(l.all, 0)) == 30);
    //test delete

    assert(deleteS(&l, "a", "b") == 1);
    assert(size(l.all) == 1);
    addC(&l, "a2", "b23", 80);
    addC(&l, "a2", "b24", 48);
    addC(&l, "a2", "b25", 23);
    //test filtru

    repo *t = filters(&l, 70);
    assert(getscor(t->elements[0]) == 80);
    //test sort

    repo *sort = sorts(&l);
    assert(getscor(sort->elements[3]) == 80);
    repo *sort2 = sort_given(&l, reverse);
    assert(getscor(sort2->elements[0]) == 80);
    destroy(sort, destroy_c);
    destroy(t, destroy_c);
    destroy(l2, destroy_c);
    destroy(sort2, destroy_c);
    destroyConcurs(&l);
}
void test_sort(){
    Concurs l = create_concurs();
    addC(&l, "mihai", "alex", 12);
    addC(&l, "mi", "lex", 32);
    repo* sorted = sort_name_service(&l);
    assert(getscor(sorted->elements[1])==12);
    destroy(sorted, (DestroyFunction) destroy_c);
    destroyConcurs(&l);
}