Да се дефинира класата Pesna во која се чуваат информации за (5 поени):

име на песна (динамички алоцирано поле од знаци)
времетраење на песната во минути
тип на песна кој може да биде: поп, рап или рок (енумерација tip)
Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата. (10 поени)

Дополнително за оваа класа да се дефинира методот:

pecati() - функција во која ќе се печатат одделени со цртичка(-): името на песната во наводници и времетраењето на песната со постфикс min. (5 поени)
Да се креира класата CD во која се чуваат информации за (5 поени):

низа од песни снимени на CD-то (Поле од најмногу 10 објекти од класата Pesna )
број на песни снимени на CD-то
максимално времетраење на песните на CD-то (во минути)
Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата. (5 поени)

Дополнително за оваа класа да се дефинираат методите:

dodadiPesna (Pesna p) - со кој се додава песната p на CDто, но само ако има доволно преостанато место (земајќи го предвид максималното времетраење на песните на CDто и времетраењата на песните на CD-то) и ако има помалку од 10 песни на CD-то. (10 поени)
pecatiPesniPoTip(tip t) – со кој се печатат информациите за сите песни од тип t (поп, рап или рок). (10 поени)
Комплетна функционалност (5 поени).



#include <iostream>
#include <string.h>
using namespace std;


enum tip {
        pop,
        rap,
        rock
    };

class Pesna {

private:
    char * ime;
    int vremetraenje;
    tip tipP;

public:

    Pesna() {}

    Pesna(char * ime, int vremetraenje, tip tipP){
        this->ime = new char[strlen(ime)+1];
        strcpy(this->ime, ime);
        this->vremetraenje = vremetraenje;
        this->tipP = tipP;
    }

 //   ~Pesna() {
 //       delete [] ime;
 //   }

    void setIme(char * ime) {
        strcpy(this->ime, ime);
    }

    char * getIme() {
        return ime;
    }

    void setVremetranje(int vremetraenje) {
        this->vremetraenje=vremetraenje;
    }

    int getVremetranje() {
        return vremetraenje;
    }


    void setTip(tip t) {
        tipP = t;
    }

    tip getTip() {
        return this->tipP;
    }


    void pecati() {
        cout<<"\""<<this->ime<<"\""<<"-"<<this->vremetraenje<<"min"<<endl;
    }
};


class CD {

private:
    Pesna pesni[10];
    int brojPesni;
    int maxVremetraenje;

public:

    CD() {
    }

    CD(Pesna pesni[10], int brojPesni, int maxVremetraenje) {
        for(int i=0; i<brojPesni; i++) {
            this->pesni[i]=pesni[i];
        }
        this->brojPesni=brojPesni;
        this->maxVremetraenje=maxVremetraenje;
    }
    
    CD(int maxVremetraenje) {
        this->brojPesni = 0;
        this->maxVremetraenje = maxVremetraenje;
    }

    ~CD() {}

    void setPesni(Pesna pesni[], int brojPesni) {
        for(int i=0; i<brojPesni; i++) {
            this->pesni[i] = pesni[i];
        }
        this->brojPesni = brojPesni;
    }

    Pesna getPesna(int i) {
        return this->pesni[i];
    }

    void setBrojPesni(int brojPesni) {
        this->brojPesni = brojPesni;
    }

    int getBrojPesni() {
        return this->brojPesni;
    }

    void setMaxVremetranje(int maxVremetraenje) {
        this->maxVremetraenje = maxVremetraenje;
    }

    int getMaxVremetraenje() {
        return maxVremetraenje;
    }

    void dodadiPesna(Pesna p) {
        if(brojPesni>=10) {
            return;
        }
        int total = 0;
        for(int i=0; i<brojPesni; i++) {
            total +=pesni[i].getVremetranje();
        }

        if(total + p.getVremetranje() > maxVremetraenje) {
            return;
        }

        pesni[brojPesni++] = p;

    }

    void pecatiPesniPoTip(tip t) {
        for(int i=0; i<brojPesni; i++) {
            if(pesni[i].getTip() == t) {
                this->pesni[i].pecati();
            }
        }
    }
};


int main() {
	// se testira zadacata modularno
    int testCase;
    cin >> testCase;
	
	int n, minuti, kojtip;
	char ime[50];
	
	if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
		p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<n; i++)
				(omileno.getPesna(i)).pecati();
	}
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<omileno.getBrojPesni(); i++)
				(omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);
        	
    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);
        	
    }
    
return 0;
}