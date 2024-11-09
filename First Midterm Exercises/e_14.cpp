Во програмскиот јазик C да се креира структура Pacient и истата треба да содржи: (5 поени)

Име и презиме на пациентот ( низа од макс. 100 знаци)
Дали е здраствено осигуран (1-да, 0-не)
Број на прегледи во текот на последниот месец (цел број)
Да се креира структура MaticenDoktor, која во себе содржи: (5 поени)

Име на докторот (низа од 100 знаци)
Број на пациенти (цел број)
Листа од пациенти (низа од максимум 200 елементи од структурата Pacient)
Цена на преглед (децимален број)
Да се креираат метода najuspesen_doktor, која прима низа од променливи од типот MaticenDoktor и нивниот број; и го печати името, заработената сума и бројот на прегледи на оној доктор кој заработил најголема сума од пациенти кои ги прегледувал приватно (не се здраствено осигурани) (10 поени). Доколку два или повеќе доктори имаат иста сума, тогаш се печати оној доктор кој има направено најголем број на прегледи вкупно во текот на последниот месец. (20 поени)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>



typedef struct Pacient {

    char ime_prezime[100];
    int osiguran;
    int br_pregledi;

} Pacient;

typedef struct MaticenDoktor {

    char ime[100];
    int br_pacienti;
    Pacient pacienti[200];
    float cena;

} MaticenDoktor;


void najuspesen_doktor(MaticenDoktor * doktor, int n) {


    int index = 0;
    float maxZarabotka = 0;
    int maxBrPregledi = 0;
    int flag = 1;
    for(int i=0; i<n; i++) {
        int momentalnaZarabotka = 0;
        int momentalniBrPregledi = 0;
        int zbir = 0;
        for(int j=0; j<doktor[i].br_pacienti; j++) {
            if(doktor[i].pacienti[j].osiguran == 0) {
                zbir += doktor[i].pacienti[j].br_pregledi;
            }
            momentalniBrPregledi = momentalniBrPregledi + doktor[i].pacienti[j].br_pregledi;
        }

        momentalnaZarabotka += doktor[i].cena * zbir;

        if(momentalnaZarabotka > maxZarabotka) {
            maxZarabotka = momentalnaZarabotka;
            index = i;
            maxBrPregledi = momentalniBrPregledi;
        }
        else if(momentalnaZarabotka == maxZarabotka) {
            if(momentalniBrPregledi > maxBrPregledi) {
                maxZarabotka = momentalnaZarabotka;
                index = i;
                maxBrPregledi = momentalniBrPregledi;
            }
        }
    }

    printf("%s %.2f %d", doktor[index].ime, maxZarabotka, maxBrPregledi);
}

int main() {

    int n;
    scanf("%d", &n);

    MaticenDoktor doktor[n];

    for(int i=0; i<n; i++) {

        scanf("%s%d%f", doktor[i].ime, &doktor[i].br_pacienti, &doktor[i].cena);

        for(int j=0; j<doktor[i].br_pacienti; j++) {
            scanf("%s%d%d", doktor[i].pacienti[j].ime_prezime,
                  &doktor[i].pacienti[j].osiguran, &doktor[i].pacienti[j].br_pregledi);
        }
    }
    
    najuspesen_doktor(doktor, n);
    return 0;
}
