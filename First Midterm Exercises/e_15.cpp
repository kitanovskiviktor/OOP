Да се креира структура Tanc во која се чуваат податоци за името на танцот и земја на потекло (низи од 15 знаци) .

Потоа да се креирa структура Tancer во која се чуваат податоци за име и презиме (низи од максимум 20 знаци), низа од 5 танци (структура Tanc) кои дадениот танчер може да ги игра. Дополнително, за оваа структура да се обезбеди функција со потпис :

void tancuvanje(Tancer *t, int n, char *zemja)

што ќе ги испечати во посебен ред името и презимето на танчерите што знаат да играат барем по еден танц од земјата која е проследена како аргумент на функцијата, како и името на танцот во формат: Име Презиме, Име на танц
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>



typedef struct Tanc {

    char ime[15];
    char zemja[15];
    
} Tanc;

typedef struct Tancer {
    
    char ime[20];
    char prezime[20];
    Tanc tanci[5];
    
} Tancer;

void tancuvanje(Tancer *t, int n, char * zemja) {

     for(int i=0; i<n; i++) {
        int brojac = 0;
        for(int j=0; j<3; j++) {
            if(strcmp(t[i].tanci[j].zemja, zemja)==0) {
                brojac++;
                if(brojac==1) {
                      printf("%s %s, %s\n",
                       t[i].ime,
                       t[i].prezime,
                       t[i].tanci[j].ime);
                }
              
            }
        }
    }

}
int main() {

    int n;
    scanf("%d", &n);
    
    Tancer tanceri[n];
    
    for(int i=0; i<n; i++) {
        scanf("%s%s", tanceri[i].ime, tanceri[i].prezime);
        
        for(int j=0; j<3; j++) {
            scanf("%s%s", tanceri[i].tanci[j].ime,
                  tanceri[i].tanci[j].zemja);
        }
    }
    
    char zemja[20];
    scanf("%s", zemja);
    
    tancuvanje(tanceri, n, zemja);
    
    return 0;
}
