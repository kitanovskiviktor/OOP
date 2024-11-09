Во програмскиот јазик C да се креира структура Laptop за опишување на спецификациите на даден преносен компјутер. Структурата треба да содржи: (5 поени)

Фирма која го произведува ( низа од 100 знаци)
Големина на монитор во инчи (реален број)
Дали е со touch или не (булова променлива)
Цена (цел број)
Да се креира структура ITStore, што содржи: (5 поени)

Име на продавницата (низа од 100 знаци)
Локација (низа од 100 знаци)
Низа од достапни лаптопи (низа од максимум 100 елементи од структурата Laptop)
Број на елементи во низата (цел број)
Да се креира функција print за печатење на информациите за сите лаптопи во една продавница во формат: (10 поени)

[Ime na prodavnicata] [Lokacija]
[Marka1] [dim_monitor1] [Cena1]
[Marka2] [dim_monitor2] [Cena2]
[Marka3] [dim_monitor3] [Cena3]
...
Да се креира функција najeftina_ponuda, што прима низа од променливи од типот ITStore и го печати името и локацијата на онаа продавница која нуди најевтин преносен компјутер и неговата цена. Најефтин преносен компјутер е оној што има најниска цена и плус опција за touch. Ако има повеќе такви продавници, се печати прво најдената.* (15 поени)*

Да се дополни функцијата main (10 поени).

Од тастатура се внесува бројот на продавници, па потоа за секоја продавница се внесуваат името и локацијата, а потоа бројот на компјутери, па за секој од компјутерите фирма која го произведува, големина на монитор, дали има touch и цена. Потоа се печатат сите внесени продавници и најевтината понуда.


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct Laptop {

    char firma[100];
    float monitor;
    int touchScreen;
    int cena;

} Laptop;

typedef struct ITStore {

    char imeStore[100];
    char lokacija[100];
    Laptop laptops[100];
    int br_elementi;

} ITStore;

void print(ITStore * stores, int n) {

    for(int i=0; i<n; i++) {
        printf("%s %s\n", stores[i].imeStore, stores[i].lokacija);
        for(int j=0; j<stores[i].br_elementi; j++) {
            printf("%s %g %d\n", stores[i].laptops[j].firma,
                   stores[i].laptops[j].monitor,
                   stores[i].laptops[j].cena);
        }
    }
}

void najeftinaPonuda(ITStore * stores, int n) {

    int minPrice;
    int index = 0;
    int flag = 1;
    for(int i=0; i<n; i++) {
        for(int j=0; j<stores[i].br_elementi; j++) {
            if(stores[i].laptops[j].touchScreen) {
                if(flag) {
                    minPrice = stores[i].laptops[j].cena;
                    flag = 0;
                }
                if(stores[i].laptops[j].cena < minPrice) {
                    minPrice = stores[i].laptops[j].cena;
                    index = i;
                }
            }
        }
    }
    printf("Najeftina ponuda ima prodavnicata:\n%s %s\n", stores[index].imeStore, stores[index].lokacija);
    printf("Najniskata cena iznesuva: %d", minPrice);
}

int main() {


    int n;
    scanf("%d", &n);

    ITStore stores[100];

     for(int i=0; i<n; i++) {
        scanf("%s%s%d", stores[i].imeStore, stores[i].lokacija, &stores[i].br_elementi);
        for(int j=0; j<stores[i].br_elementi; j++) {
            scanf("%s %f %d %d", stores[i].laptops[j].firma, &stores[i].laptops[j].monitor, &stores[i].laptops[j].touchScreen, &stores[i].laptops[j].cena);
        }
    }
    print(stores, n);
    najeftinaPonuda(stores, n);
    return 0;
}
