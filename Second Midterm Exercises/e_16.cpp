Туристичка агенција нуди различни понуди за транспорт на патници. За секоја понуда се чуваат податоци за дестинацијата (низа од знаци), основна цена (цел број) и податок за растојанието до дестинацијата изразено во km (цел број).

Од класата Transport да се изведат класите AvtomobilTransport и KombeTransport за моделирање на понудите за транспорт кои нудат транспорт со автомобил или комбе, соодветно. За секоја понуда за транспорт со автомобил се чува податок за тоа дали во понудата има платен шофер (булова променлива), а за транспорт со комбе бројот на луѓе кои може да се превезат во комбето (цел број). (5 поени)

За секој објект од двете изведени класи треба да бидат на располагање следниве методи:

конструктор со аргументи што одговараат на податочните членови и set и get методи за податочните членови (5 поени)
метод cenaTransport, за пресметување на цената на понудата на следниот начин:
За транспорт со автомобил - основната цена се зголемува за 20% ако има платен шофер
За транспорт со комбе - основната цена ќе се намали зависно од бројот на патници во комбето. За секој патник во комбето цената се намалува за 200 (10 поени)
преоптоварен оператор < за споредба на две понуди за транспорт на патник според растојанието до дестинацијата. (5 поени)
Да се имплементира функција pecatiPoloshiPonudi што на влез прима низа од понуди за транспорт на патник, бројот на елементите од низата и една понуда T. Функцијата ја печати дестинацијата, растојанието до дестинацијата и цената за понудите од низата кои се поскапи од понудата T сортирани во растечки редослед по растојанието до дестинацијата (погледни го повикот на функцијата) (10 поени)

Комплетна функционалност на кодот (5 поени)

#include <iostream>
#include <cstring>

using namespace std;





class Transport {
protected:
    char destinacija[100];
    int osnovnaCena;
    int kilometri;

public:

    char * getDestinacija() {
        return destinacija;
    }

    int getKilometri() {
        return kilometri;
    }

    Transport() {}

    Transport(char * d, int o, int k) {
        strcpy(this->destinacija, d);
        this->osnovnaCena = o;
        this->kilometri = k;
    }

    virtual int cenaTransport() = 0;

    bool operator<(Transport &t) {
        return this->kilometri < t.kilometri;
    }
    
    bool operator>(Transport &t) {
        return cenaTransport() > t.cenaTransport();
    }
};

class AvtomobilTransport : public Transport {
private:
    bool platenSofer;

public:
    AvtomobilTransport(char * d, int o, int k, bool p) : Transport(d,o,k) {
        this->platenSofer = p;
    }

    int cenaTransport() {
        if(platenSofer) {
            return osnovnaCena * 1.2;
        }
        return osnovnaCena;
    }


};

class KombeTransport : public Transport {
private:
    int brojLugje;

public:
    KombeTransport(char * d, int o, int k, int b) : Transport(d,o,k) {
        this->brojLugje = b;
    }

    int cenaTransport() {
        return osnovnaCena - (brojLugje * 200);
    }


};

void pecatiPoloshiPonudi(Transport **ponudi, int count, AvtomobilTransport &t ) {

    Transport **temp;
    temp = new Transport*[count];
    int tempCount = 0;
    for(int i=0; i<count; i++) {
        if(ponudi[i]->cenaTransport() > t.cenaTransport()) {
            temp[tempCount++] = ponudi[i];
        }
    }

    for(int i=0; i<tempCount-1; i++) {
        for(int j=0; j<tempCount-i-1; j++) {
            if(*temp[j]>*temp[j+1]) {
                Transport *tmp = temp[j];
                temp[j] = temp[j+1];
                temp[j+1]=tmp;
            }
        }
    }

    for(int i=0; i<tempCount; i++) {
        cout<<temp[i]->getDestinacija()<<" "<<temp[i]->getKilometri()<<" "<<temp[i]->cenaTransport()<<endl;
    }

}




int main(){

char destinacija[20];
int tip,cena,rastojanie,lugje;
bool shofer;
int n;
cin>>n;
Transport  **ponudi;
ponudi=new Transport *[n];

for (int i=0;i<n;i++){

    cin>>tip>>destinacija>>cena>>rastojanie;
    if (tip==1) {
        cin>>shofer;
        ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

    }
    else {
        cin>>lugje;
        ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
    }


}

AvtomobilTransport nov("Ohrid",2000,600,false);
pecatiPoloshiPonudi(ponudi,n,nov);

for (int i=0;i<n;i++) delete ponudi[i];
delete [] ponudi;
return 0;
}

