//
// Created by ultra on 17.03.2023.
//
#include "entities.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

Concurent* create_concurent(char *nume, char *prenume, int scor) {
    Concurent *rez = malloc(sizeof(Concurent));
    int nr = strlen(nume);
    rez->nume = malloc(nr * sizeof(char));
    strcpy(rez->nume, nume);
    nr = strlen(prenume);
    rez->prenume = malloc(nr * sizeof(char));
    strcpy(rez->prenume, prenume);
    rez->scor = scor;
    return rez;
}


void test_CreateDestroy() {
    Concurent* c = create_concurent("Mihai", "alex", 30);
    assert(strcmp(c->nume, "Mihai") == 0);
    assert(strcmp(c->prenume, "alex") == 0);
    assert(c->scor == 30);
    destroy_c(c);
}

int valideaza(Concurent p) {
    if (strlen(p.nume) == 0) {
        return 1;
    }
    if (strlen(p.prenume) == 0) {
        return 2;
    }
    if (p.scor > 100 || p.scor < 0) {
        return 3;
    }
    return 0;
}

void destroy_c(Concurent *c) {
    free(c->nume);
    free(c->prenume);
    free(c);
}
int getscor(Concurent *p) {
    return p->scor;
}

char* getnume(Concurent *p) {
    return p->nume;
}

char* getprenume(Concurent *p) {
    return p->prenume;
}

void setscor(Concurent *p, int scor) {
    p->scor = scor;
}
void setnume(Concurent* p,char* nume){
    strcpy(getnume(p),nume);
}

void setprenume(Concurent* p,char* prenume){
    strcpy(p->prenume, prenume);
}
void test_getset(){
    Concurent *c = create_concurent("Mihai", "alex", 30);
    assert(strcmp(getnume(c),"Mihai")==0);
    assert(strcmp(getprenume(c),"alex")==0);
    assert(getscor(c)==30);
    setnume(c,"ale");
    setprenume(c,"ema");
    setscor(c,50);
    assert(strcmp(getnume(c),"ale")==0);
    assert(strcmp(getprenume(c),"ema")==0);
    assert(getscor(c)==50);
    destroy_c(c);
}
Concurent* copy_concurent(Concurent* c){
    return create_concurent(c->nume,c->prenume,c->scor);
}