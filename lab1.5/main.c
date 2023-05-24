#include <stdio.h>
#include <stdlib.h>
#include "entities.h"
#include "repo.h"
#include "service.h"

void testall() {
    test_CreateDestroy();
    testCreateList();
    testIterateList();
    testCopyList();
    testaddC();
    testreverse();
    test_getset();
    test_lista_liste();
    test_undo();
    test_sort();
}

/*
 * read and add and participant repo
 * l: the list of participants
 */
void readconcurent(Concurs *l) {
    printf("Numele:");
    char *nume = (char *) malloc(30 * sizeof(char));
    scanf("%s", nume);
    printf("Prenumele:");
    char *prenume = (char *) malloc(30 * sizeof(char));
    scanf("%s", prenume);
    int scor;
    printf("Scorul este");
    scanf("%d", &scor);

    int error = addC(l, nume, prenume, scor);
    if (error != 0) {
        printf("Concurent invalid\n");
    } else {
        printf("Concurent adaugat\n");
    }
    free(nume);
    free(prenume);
}

/*
 * print all participants
 * l: the list of participants
 *
 */
void printall(repo *l) {
    printf("Concurenti: \n");
    for (int i = 0; i < size(l); i++) {
        Concurent *c = get(l, i);
        printf("Nume:%s, Prenume:%s, Scor:%d \n", c->nume, c->prenume, c->scor);
    }
}

/*
 * update a participant from the list
 * l: the list of participants
 */
void update(Concurs *l) {
    printf("Introduceti: Numele: ");
    char *nume = (char *) malloc(30 * sizeof(char));
    char *prenume = (char *) malloc(30 * sizeof(char));
    int scor;
    scanf("%s", nume);
    printf("Prenume: ");
    scanf("%s", prenume);
    printf("Scor: ");
    scanf("%d", &scor);
    if (updateS(l, nume, prenume, scor) == 1) {
        printf("\nConcurent modificat cu succes\n");
    } else {
        printf("\nConcurent inexistent\n");
    }
    free(nume);
    free(prenume);
}

/*
 * delete a participant from the list
 * l: the list of participants
 */
void delete(Concurs *l) {
    printf("Introduceti: Numele: ");
    char *nume = (char *) malloc(30 * sizeof(char));
    char *prenume = (char *) malloc(30 * sizeof(char));
    scanf("%s", nume);
    printf("Prenume: ");
    scanf("%s", prenume);
    if (deleteS(l, nume, prenume) == 1) {
        printf("\nConcurent sters cu succes\n");
    } else {
        printf("\nConcurent inexistent\n");
    }
    free(nume);
    free(prenume);
}

/*
 * afiseaza concurentii care au obtinut un scor mai mare decat un numar  dat
 * l: lista de concurenti
 */
void filter(repo *l) {
    int scor;
    printf("Scorul minim:  ");
    scanf("%d", &scor);
    repo *filtered = filters(l, scor);
    printall(filtered);
    destroy(filtered, destroy_c);
}

/*
 * sorteaza lista de concurenti in ordine crescatoare a scorului
 */
void sort(Concurs *l) {
    repo *sorted = sorts(l);
    printall(sorted);
    destroy(sorted, destroy_c);
}

void sort_g(Concurs *l,FunctieComparare cmp){
    repo* sorted = sort_given(l,cmp);
    printall(sorted);
    destroy(sorted, destroy_c);
}
void sort_name(Concurs *l){
    repo* sorted = sort_name_service(l);
    printall(sorted);
    destroy(sorted,destroy_c);
}

void run() {
    Concurs repository = create_concurs();
    int ok = 1;
    while (ok) {
        printf("[0]Exit | [1]Adauga concurent | [2]Afisare concurenti | [3]Actualizare concurent |[4]Elimina concurent [5]Filtru [6]Sort [8]undo [9]Filtrare_nume\n");
        printf("Comanda este:  ");
        int cmd;
        scanf("%d", &cmd);
        switch (cmd) {
            case 1:
                readconcurent(&repository);
                break;
            case 2:
                printall(repository.all);
                break;
            case 3:
                update(&repository);
                break;
            case 4:
                delete(&repository);
                break;
            case 5:
                filter(&repository);
                break;
            case 6:
                sort(&repository);
                break;
            case 7:
                sort_g(&repository, &reverse);
                break;
            case 8:
                if (undo(&repository) != 0) {
                    printf("No more undo!\n");
                }
                break;
            case 9:
                sort_name(&repository);
                break;
            case 0:
                destroy(&repository, destroy_c);
                ok = 0;
                break;
            default:
                printf("Comanda invalida!\n");
        }

    }
}

int main() {
    testall();
    run();
    return 0;
}
