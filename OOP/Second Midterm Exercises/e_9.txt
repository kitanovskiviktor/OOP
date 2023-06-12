Да се имплементира класа Trud во која се чуваат информации за: (5 поени)

вид на труд (еден знак и тоа C за конференциски труд, J за труд во списание)
година на издавање (цел број).
Да се имплементира класа Student во која се чува: (5 поени)

името на студентот (низа од најмногу 30 карактери)
индекс (цел број)
година на упис (цел број)
листа на оцени од положени предмети (низа од цели броеви)
број на положени предмети (цел број)
За оваа класа да се имплементираат следните методи:

функција rang() што пресметува просек од положените испити на студентот (5 поени)
оператор << за печатење на студентот во формат: (5 поени)

Индекс Име Година на упис ранг

Да се имплементира класа PhDStudent во која покрај основните информации за студентот дополнително се чува: (5 поени)

листа од објавени трудови (динамички резервирана низа од објекти од класата Trud)
бројот на трудови (цел број)
Во оваа класа да се препокрие соодветно функцијата rang() така што на просекот од положените испити ќе се додаде и збирот од поените од објавените трудови на PhD студентот. Во зависност од видот на трудот, секој универзитет има посебен начин на бодување на трудовите. Начинот на бодување е ист за сите PhD студенти. Иницијално да се смета дека конференциски труд се бодува со 1 поен, а труд во списание со 3 поени. Универзитетот има можност да ги менува вредностите на бодовите. (5 поени + 5 поени)

За оваа класа да се обезбеди:

оператор += за додавање нов објект од класата Trud во листата (5 поени). Ако се направи обид да се внесе труд што е издаден порано од годината на упис на студентот да се фрли исклучок (објект од класата Exception). Справувањето со исклучокот треба да се реализира во главната функција main каде што е потребно, но и во конструктор ако е потребно. Ако бил генериран исклучок треба да се отпечати соодветна порака за грешка "Ne moze da se vnese dadeniot trud", а новиот труд нема да се внесе во листата на трудови од студентот. (10 поени)
Напомена: Сите променливи на класите се чуваат како приватни.

Да се обезбедат сите потребни функции за правилно функционирање на програмата. (5 поени)


#include <iostream>
#include <cstring>

using namespace std;

class Exception
{
private:
    char *msg;
public:
    Exception (char *msg)
    {
        this->msg = new char[strlen(msg)+1];
        strcpy(this->msg,msg);
    }

    void message(){
        cout<<msg<<endl;
    }

    ~Exception()
    {
        delete []msg;
    }
};

class Trud {

protected:
    char TIP;
    int godina;

public:
    Trud(){}

    Trud(char tip, int godina) {
        this->godina = godina;
        this->TIP = tip;
    }

    Trud(const Trud&other) {
        this->godina = other.godina;
    }

    char getTIP() {
        return TIP;
    }

    friend istream&operator>>(istream&input, Trud&trud) {
        input >> trud.TIP >> trud.godina;
        return input;
    }

    int getGodina() { return godina; }
};



class Student {
protected:
    char name[30];
    int indeks;
    int godinaUpis;
    int * oceni;
    int count;

public:
    Student() {}

    Student(char * name, int indeks, int godinaUpis, int * oceni, int count) {
        strcpy(this->name, name);
        this->indeks = indeks;
        this->godinaUpis = godinaUpis;
        this->count = count;
        this->oceni = new int [count+1];
        for(int i=0; i<count; i++) {
            this->oceni[i] = oceni[i];
        }
    }

    virtual double rang() {
        double zbir = 0.0;
        for(int i=0; i<count; i++) {
            zbir+=oceni[i];
        }
        return zbir / (double)count;
    }

    int getIndex() {
        return indeks;
    }

    friend ostream&operator<<(ostream&os, Student &s) {
        os<<s.indeks<<" "<<s.name<<" "<<s.godinaUpis<<" "<<s.rang()<<endl;
        return os;
    }


};

class PhDStudent : public Student {
    Trud * trudovi;
    int brojTrudovi;
    static int bodoviJ;
    static int bodoviC;

public:

    PhDStudent() {}

    PhDStudent(char * name, int indeks, int godinaUpis, int * oceni, int count, Trud * trudovi, int bt) : Student(name, indeks, godinaUpis, oceni, count) {
        this->trudovi = new Trud [bt+1];
        this->brojTrudovi = bt;
        for(int i = 0; i<brojTrudovi; i++) {
            this->trudovi[i] = trudovi[i];
        }
    }

    PhDStudent(const PhDStudent&other) : Student(other){
         this->trudovi = new Trud [other.brojTrudovi+1];
        this->brojTrudovi = other.brojTrudovi;
        for(int i = 0; i<other.brojTrudovi; i++) {
            this->trudovi[i] = other.trudovi[i];
        }
    }

    PhDStudent&operator=(const PhDStudent&other){
         if(this==&other) {
            return *this;
         }
     //    delete [] trudovi;
      //   delete [] oceni;
          strcpy(this->name, other.name);
        this->indeks = other.indeks;
        this->godinaUpis = other.godinaUpis;
        this->oceni = new int [other.count+1];
        for(int i=0; i<other.count; i++) {
            this->oceni[i] = other.oceni[i];
        }
         this->trudovi = new Trud [other.brojTrudovi+1];
         this->brojTrudovi = other.brojTrudovi;
         for(int i = 0; i<other.brojTrudovi; i++) {
            this->trudovi[i] = other.trudovi[i];
        }
        return *this;
    }

    double rang() {
        int bodovi = 0;
        float osnoven = Student::rang();
        for(int i=0; i<brojTrudovi; i++) {
                if(trudovi[i].getTIP()=='J' || trudovi[i].getTIP()=='j') {
                    bodovi+=bodoviJ;
                }
                else if(trudovi[i].getTIP()=='C' || trudovi[i].getTIP()=='c') {
                    bodovi+=bodoviC;
                }

        }
        return osnoven + bodovi;
    }

    static void setBodoviJ(int j) {
        bodoviJ = j;
    }

    static void setBodoviC(int c) {
        bodoviC = c;
    }

    PhDStudent&operator+=(Trud &t) {

        if(t.getGodina() < godinaUpis) {
            throw Exception("Ne moze da se vnese dadeniot trud");
        }

        Trud * temp = new Trud[brojTrudovi+1];
        for(int i=0; i<brojTrudovi; i++) {
            temp[i] = trudovi[i];
        }
        temp[brojTrudovi++] = t;
        delete [] trudovi;
        trudovi = temp;
        return *this;

    }


};

int PhDStudent::bodoviC = 1;
int PhDStudent::bodoviJ = 3;



int main(){
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;
        bool najde=false;
        for(int i=0;i<m;i++)
        {
            if(niza[i]->getIndex()==indeks)
            {

                PhDStudent *p = dynamic_cast<PhDStudent*> (niza[i]);
                if(p!=0)
                {
                    najde=true;
                    try
                    {
                        *p+=t;
                    }
                    catch(Exception &e)
                    {
                        e.message();
                    }
                }
            }
        }
        if(najde==false)
        {
          cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;
        }

            // pecatenje na site studenti
            cout << "\nLista na site studenti:\n";
            for (int i = 0; i < m; i++)
                cout << *niza[i];
    }
    if (testCase == 3){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks

        Trud t;
        cin >> indeks;
        cin >> t;
        for(int i=0;i<m;i++)
        {
            if(niza[i]->getIndex()==indeks)
            {
                PhDStudent *p = dynamic_cast<PhDStudent*> (niza[i]);
                if(p!=0)
                {
                    try
                    {
                        *p+=t;
                    }
                    catch(Exception &e)
                    {
                        e.message();
                    }
                }
            }
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            try
            {
                if(god_tr<god)
                    throw Exception ("Ne moze da se vnese dadeniot trud");
                Trud t(tip, god_tr);
                trud[j] = t;
            }
            catch(Exception &e)
            {
                e.message();
            }

        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 5){
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;



        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot

        for(int i=0;i<m;i++)
        {
            if(niza[i]->getIndex()==indeks)
            {
                PhDStudent *p = dynamic_cast<PhDStudent*> (niza[i]);
                if(p!=0)
                {
                    try
                    {
                        *p+=t;
                    }
                    catch(Exception &e)
                    {
                        e.message();
                    }
                }
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6){
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        PhDStudent::setBodoviJ(journal);
        PhDStudent::setBodoviC(conf);

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;

}
