Да се креира структура SkiLift во која се чуваат податоци за името на ски лифтот (низа од 15 знаци), максимален број на корисници што може да опслужи на едно возење, дали е пуштен во функција.

Потоа да се креирa структура SkiCenter во која се чуваат податоци за името на скијачкиот центар, држава во која се наоѓа (низи од 20 знаци), низа од ски лифтови (макс 20) што ги има и број на ски лифтови.

Треба да се направи функција со потпис

void najgolemKapacitet(SkiCenter *sc, int n)
која што ќе го отпечати ски центарот што има најголем капацитет за опслужување скијачи (вкупниот број на скијачи кои може да се опслужуваат во еден момент вкупно на сите ски лифтови во центарот). Доколку два ски центри имаат ист капацитет, тогаш се печати оној кој има поголем број на ски лифтови. Притоа треба да се испечатат во посебен ред името, државата и капацитетот на ски центарот. Кога се пресметува капацитет на еден ски центар во предвид се земаат само ски лифтовите кои се поставени дека се во функција.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>




typedef struct SkiLift {

    char skifLiftName[15];
    int korisnici;
    int funkcija;
} SkiLift;


typedef struct SkiCenter {
    char skiCenterName[20];
    char drzava[20];
    SkiLift skiLifts[20];
    int broj_skiliftovi;
} SkiCenter;


int kapacitetCentar(SkiCenter sc) {

    int zbir = 0;
    for(int i=0; i<sc.broj_skiliftovi; i++) {
        if(sc.skiLifts[i].funkcija) {
            zbir+=sc.skiLifts[i].korisnici;
        }
    }
    return zbir;
}


void najgolemKapacitet(SkiCenter * sc, int n) {

    int index = 0;
    int max = 0;
    int temp;
    for(int i=0; i<n; i++) {
        temp = kapacitetCentar(sc[i]);
        if(temp>max || temp==max && sc[i].broj_skiliftovi > sc[index].broj_skiliftovi) {
            max = temp;
            index = i;
        }
    }
    
    printf("%s\n%s\n%d",sc[index].skiCenterName, sc[index].drzava, max);

}


int main() {


    int n;
    scanf("%d", &n);
    
    SkiCenter SkiCenters[n];
    
    for(int i=0; i<n; i++) {
        
        scanf("%s%s%d", SkiCenters[i].skiCenterName,
              SkiCenters[i].drzava,
              &SkiCenters[i].broj_skiliftovi);
        for(int j=0; j<SkiCenters[i].broj_skiliftovi; j++) {
            scanf("%s%d%d", SkiCenters[i].skiLifts[j].skifLiftName, 
                  &SkiCenters[i].skiLifts[j].korisnici,
                  &SkiCenters[i].skiLifts[j].funkcija);
        }
        
    }
    najgolemKapacitet(SkiCenters, n);
    return 0;
}
