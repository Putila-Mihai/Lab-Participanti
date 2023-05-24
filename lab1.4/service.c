//
// Created by ultra on 17.03.2023.
//
#include "service.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>


int addC(repo *l, char *nume, char *prenume, int scor) {
    Concurent* c = create_concurent(nume, prenume, scor);
    int succ = valideaza(*c);
    if (succ != 0) {
        free(c->nume);
        free(c->prenume);
        free(c);
        return succ;

    }
    add(l, c);
    return 0;
}

repo* getAllC(repo *l) {
    return copylist(l,copy_concurent);
}

int updateS(repo *l, char *nume, char *prenume, int scor) {
    repo* cp = getAllC(l);
    int ok = 0;
    for (int i = 0; i < size(cp); i++) {
        Concurent* x = get(cp, i);
        if (strcmp(x->nume, nume) == 0 && strcmp(x->prenume, prenume) == 0) {
            setscor(l->elements[i], scor);
            ok = 1;
        }
    }
    free(cp->elements);
    free(cp);
    return ok;

}

int deleteS(repo *l, char *nume, char *prenume) {
    repo* cp = getAllC(l);
    int ok = 0;
    for (int i = 0; i < size(cp); i++) {
        Concurent* x = get(cp, i);
        if (strcmp(x->nume, nume) == 0 && strcmp(x->prenume, prenume) == 0) {
            destroy_c(l->elements[i]);
            for (int k = i; k < size(cp) - 1; k++) {
                l->elements[k] = l->elements[k + 1];

            }
            ok = 1;
            l->lengh--;
        }

    }
    free(cp->elements);
    free(cp);
    return ok;
}

repo* filters(repo *l, int scor) {
    repo* lista = createEmpty();
    for (int k = 0; k < size(l); k++) {
        Concurent* c = get(l, k);
        if (c->scor >= scor) {
            addC(lista, c->nume, c->prenume, c->scor);
        }
    }
    return lista;
}

repo* sorts(repo *l) {
    repo* sorted = createEmpty();
    for (int k = 0; k < size(l); k++)
        addC(sorted, getnume(l->elements[k]), getprenume(l->elements[k]), getscor(l->elements[k]));
    for (int k = 0; k < size(l) - 1; k++)
        for (int j = k; j < size(l); j++) {
            if (getscor(sorted->elements[k]) > getscor(sorted->elements[j])) {
                Concurent* aux = sorted->elements[k];
                sorted->elements[k] = sorted->elements[j];
                sorted->elements[j] = aux;
            }
        }
    return sorted;
}

void sort_given(repo *l, FunctieComparare cmp) {
    for (int i = 0; i < size(l) - 1; i++)
        for (int j = i + 1; j < size(l); j++) {
            Concurent* c1 = get(l, i);
            Concurent* c2 = get(l, j);
            if (cmp(c1, c2) == 1) {
                l->elements[i] = c2;
                l->elements[j] = c1;
            }

        }

}

int reverse(Concurent *c1, Concurent *c2) {
    if (c1->scor < c2->scor) return 1;
    else return 0;
}

void testreverse() {
    Concurent* c1;
    Concurent* c2;
    c1 = create_concurent("Mihai", "alx", 31);
    c2 = create_concurent("Mihai", "alex", 30);
    assert(reverse(c1, c2) == 0);
    destroy_c(c1);
    destroy_c(c2);
}

void testaddC() {
    repo* l = createEmpty();
    //invalid
    int error = addC(l, "", "b", 10);
    assert(error != 0);
    assert(size(l) == 0);

    error = addC(l, "a", "", 10);
    assert(error != 0);
    assert(size(l) == 0);
//
    error = addC(l, "a", "b", 1001);
    assert(error != 0);
    assert(size(l) == 0);
    //valid
    addC(l, "a", "b", 20);
    addC(l, "a2", "b2", 40);
    repo* l2 = getAllC(l);
    assert(size(l2) == 2);
    assert(getscor(l->elements[0]) == 20);
    //test update
    assert(updateS(l, "a", "b", 30) == 1);
    assert(getscor(get(l, 0)) == 30);
    //test delete
    assert(deleteS(l, "a", "b") == 1);
    assert(size(l) == 1);
    addC(l, "a2", "b23", 80);
    addC(l, "a2", "b24", 48);
    addC(l, "a2", "b25", 23);
    repo* t = filters(l, 70);
    assert(getscor(t->elements[0]) == 80);
    repo* sort = sorts(l);
    assert(getscor(sort->elements[3]) == 80);
    sort_given(sort, reverse);
    assert(getscor(sort->elements[0]) == 80);
    destroy(l,destroy_c);
    free(l2->elements);
    destroy(sort,destroy_c);
    destroy(t,destroy_c);
}