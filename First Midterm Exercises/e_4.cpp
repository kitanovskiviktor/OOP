Да се креира структура Воз во која се чуваат податоци за релацијата по која се движи возот (низа од најмногу 50 знаци), предвиден бројот на километри што треба да се поминат (реален број), како и бројот на патници во возот (цел број).

Потоа да се креирa структура ZeleznickaStanica во која се чуваат податоци за градот во кој се наоѓа (низа од 20 знаци), низа од возови што поаѓаат од станицата (најмногу 30) и бројот на возови (цел број).

Треба да се направи функција со потпис

void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad)
во која се печати релацијата и бројот на километри на возот што поминува најкратка релација (најмалку километри), а поаѓа од железничката станица од градот што се проследува како влезен аргумент. Ако има повеќе возови со ист најмал број на километри, да се испечати релацијата на последниот таков.


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


typedef struct Voz {

    char relacija[50];
    float kilometri;
    int br_patnici;

} Voz;


typedef struct ZeleznickaStanica{

    char grad[30];
    Voz vozovi[30];
    int br_vozovi;
} ZeleznickaStanica;


void najkratkaRelacija(ZeleznickaStanica * stanici, int n, char * grad) {

    for(int i=0; i<n; i++) {
       
       if(!strcmp(stanici[i].grad, grad)) {
           int index = 0;
           float minKMs = stanici[i].vozovi[0].kilometri;
           for(int j=0; j<stanici[i].br_vozovi; j++) {
               if(stanici[i].vozovi[j].kilometri<=minKMs) {
                   minKMs = stanici[i].vozovi[j].kilometri;
                   index = j;
               }
           }
           
           printf("Najkratka relacija: %s (%g km)", stanici[i].vozovi[index].relacija, 
           stanici[i].vozovi[index].kilometri);
       }
    }
}

int main() {


    int n;
    scanf("%d", &n);

    ZeleznickaStanica zStanica[100];

    for(int i=0; i<n; i++) {

        scanf("%s %d", zStanica[i].grad, &zStanica[i].br_vozovi);

        for(int j=0; j<zStanica[i].br_vozovi; j++) {
            scanf("%s %f %d", zStanica[i].vozovi[j].relacija,
                  &zStanica[i].vozovi[j].kilometri,
                  &zStanica[i].vozovi[j].br_patnici);
        }

    }

    char grad[30];
    scanf("%s", grad);

    najkratkaRelacija(zStanica, n, grad);

    return 0;
}
