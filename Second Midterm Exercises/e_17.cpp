Да се имплементира апстрактна класа FudblaskaEkipa во која се чува: (5 поени)

име на тренерот на екипата (максимум 100 знаци)
бројот на постигнати голови на последните 10 натпревари, последниот натпревар е на позиција 9, предпоследниот на позиција 8, итн (поле од 10 цели броеви)
Од класата FudblaskaEkipa да се изведат класите Klub и Reprezentacija. За секој клуб дополнително се чува податок за името и бројот на титули што ги има освоено, а за репрезентацијата се чуваат податоци за името на државата и вкупен број на меѓународни настапи. За овие класи да се имплементираат следните методи:

соодветен конструктор (5 поени)
оператор << за печатење на стандарден излез во формат [IME_NA_KLUB/DRZHAVA]\n[TRENER]\n[USPEH]\n (5 поени)
преоптоварен оператор+= за додавање на голови од последниот натпревар (внимавајте секогаш се чуваат головите само од последните 10 натпревари) (10 поени)
метод uspeh, за пресметување на успехот на тимот на следниот начин:
За Klub се пресметува како збир од збирот на головите од последните 10 натпревари помножен со 3 и бројот на титули помножен со 1000 (на пр. голови = {2, 0, 1, 3, 2, 0, 1, 4, 2, 3} и број на титули = 3, достигнување = 18 * 3 + 3 * 1000 = 3054)
За Reprezentacija како збир од збирот на головите од последните 10 натпревари помножен со 3 и бројот на меѓународни настапи помножен со 50 (на пр. голови = {2, 0, 1, 3, 2, 0, 1, 4, 2, 3} и број на меѓународни настапи=150, достигнување = 18 * 3 + 150 * 50 = 7554) (10 поени)
преоптоварен оператор > за споредба на две фудбласки екипи од каков било вид (клубови или репрезентации) според успехот (5 поени)
Да се имплементира функција najdobarTrener што на влез прима низа од покажувачи кон FudblaskaEkipa и големина на низата и го печати тимот со најголем успех (10 поени).

#include <iostream>
#include <cstring>

using namespace std;




class FudbalskaEkipa {
protected:
    char ime[100];
    int brojGolovi[10];

public:
    FudbalskaEkipa(char * ime, int * bg) {
        strcpy(this->ime, ime);
        for(int i=0; i<10; i++) {
            this->brojGolovi[i] = bg[i];
        }
    }
    FudbalskaEkipa&operator+=(int p) {
      brojGolovi[0]=p;
      return *this;
    }

        virtual int uspeh() = 0;

    bool operator>(FudbalskaEkipa&f) {
        return this->uspeh() > f.uspeh();
    }


    virtual char * getKlub() = 0;

    friend ostream&operator<<(ostream &out, FudbalskaEkipa&f) {
        out<<f.getKlub()<<endl;
        out<<f.getTrener()<<endl;
        out<<f.uspeh()<<endl;
        return out;
    }

    char *getTrener() {
        return ime;
    }



};


class Klub : public FudbalskaEkipa {
private:
    char imeKlub[100];
    int brojTituli;

public:
    Klub(char *ime, int * golovi, char * x, int b): FudbalskaEkipa(ime, golovi) {
        strcpy(this->imeKlub, x);
        this->brojTituli = b;
    }

    int uspeh() {
           int zbirGolovi =0;
       int vkupnoGolovi = 0;
       for(int i=0; i<10; i++) {
            zbirGolovi += brojGolovi[i];
       }
       vkupnoGolovi = zbirGolovi * 3;
       int vTituli = 0;
       vTituli = brojTituli * 1000;
       return vkupnoGolovi + vTituli;
    }

      char * getKlub() {
        return imeKlub;
    }


};

class Reprezentacija : public FudbalskaEkipa {
protected:
    char drzava[100];
    int vkupnoNastapi;

public:

    Reprezentacija(char *ime, int * golovi, char * x, int b) : FudbalskaEkipa(ime, golovi) {
        strcpy(this->drzava, x);
        this->vkupnoNastapi = b;
    }

    int uspeh() {
       int zbirGolovi =0;
       int vkupnoGolovi = 0;
       for(int i=0; i<10; i++) {
            zbirGolovi += brojGolovi[i];
       }
       vkupnoGolovi = zbirGolovi * 3;
       int vNastapni = 0;
       vNastapni = vkupnoNastapi * 50;
       return vkupnoGolovi + vNastapni;
    }

     char * getKlub() {
        return drzava;
    }


};

void najdobarTrener(FudbalskaEkipa **ekipi, int n) {
    int maxUspeh = 0;
    int index = 0;

    for(int i=0; i<n; i++) {
        if(ekipi[i]->uspeh() > maxUspeh) {
            maxUspeh = ekipi[i]->uspeh();
            index = i;
        }
    }
    cout<<ekipi[index]->getKlub()<<endl;
    cout<<ekipi[index]->getTrener()<<endl;
    cout<<ekipi[index]->uspeh()<<endl;

}


int main(){

  int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
return 0;
}

