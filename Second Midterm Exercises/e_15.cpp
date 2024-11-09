Дадена е дел од дефиниција на класата StudentKurs. За секој студент кој слуша некој курс се чуваат информации за неговото име (низа од знаци), оценка од писмен дел (цел број) и дали студентот сака да биде испрашуван и усно (булова променлива).

Оцената за писмениот дел е вредност од 1 до МАX. MAX има почетна вредност 10 која е иста е за сите и може да се промени со соодветна функција setMAX(). (5 поени)

Кај оние студенти кои сакаат да бидат испрашувани усно и добиваат и описна оценка. Имплементирај соодветна класа StudentKursUsno во која се чуваат дополнителни информации за описна оценка на усното испрашување (динамичко алоцирана низа од знаци). Описни оценки може да бидат: odlicen, dobro, losho.... Ако описната оценка е odlicen тогаш оцената ќе биде најмногу за оценки 2 повисока од оценката од писмениот дел, ако е dobro оценката ќе биде најмногу за 1 повисока, а ако е losho за 1 пониска. Ако студентот добие некоја друга описна оценка, неговата оценка ќе остане иста со оценката од писмениот дел.

Во класите StudentKurs и StudentKursUsno треба да се имплементираат потребните конструктори, функции за поставување и преземање и деструктор. (5 поени)

За сите објекти од класите треба да се обезбедат следните функции:

преоптоварен оператор << во кој се печатат информации за студентот на курсот во формат: Ime --- ocenka (5 поени)
оcenka() – ја враќа оценката на студентот на курсот (5 поени)
Во класата StudentKursUsno дефинирај ја функцијата:

преоптоварен оператор += за поставување на описна оценка на студентот(5 поени)
Ако се направи обид да се внесе описна оценка во која покрај букви има и други знаци треба да се фрли исклучок (објект од класата BadInputException). Фатете го исклучокот во главната функција каде што е потребно. Откако ќе го фатите отпечатете соодветна порака за грешка (Greshna opisna ocenka) и справете се со исклучокот така што тие знаци ќе отстранат од стрингот со описната оценка (ако описната оценка била dо1ba0r ќе се промени во dоbar). (10 поени)

Дадена е дел од дефиницијата на класата KursFakultet во која се чуваат информаци за името на курсот (низа од 30 знаци) и за студентите запишани на курсот (низа од 20 покажувачи кон класата StudentKurs) како и бројот на студенти запишани на курсот.

Еден студент кој запишал некој курс ќе го положи курсот ако има барем MINOCENKA. Вредноста MINOCENKA е членка на класата StudentKurs и има фиксна вредност 6 која не може да се промени. (5 поени)

Во класата KursFakultet имплементирај ги функциите:

функција pecatiStudenti() во која се печатат сите студенти кои го положиле курсот, секој во посебен ред. Претходно во првиот ред се печати: Kursot XXXXX go polozile: (5 поени).

функција postaviOpisnaOcenka(char * ime, char* opisnaOcenka) во која на студентот на курсот со даденото име му се поствува описна оценка. Ако тоа не е можно функцијата не прави ништо (15 поени).

Комплетна функционалност (5 поени)


#include<iostream>
#include<string.h>
using namespace std;

class BadInputException
{
private:
    char *msg;
public:
    BadInputException(char *msg)
    {
        this->msg = new char[strlen(msg)+1];
        strcpy(this->msg, msg);
    }
    void message()
    {
        cout<<msg<<endl;
    }
    ~BadInputException()
    {
        delete []msg;
    }
};


class StudentKurs{
   protected:
       char ime[30];
       int ocenka;
       bool daliUsno;
        static int MAX;
        const static int MINOCENKA;

   public:
       StudentKurs() {}
    StudentKurs(char* ime,int finalenIspit){
       strcpy(this->ime,ime);
       this->ocenka=finalenIspit;
       this->daliUsno=false;
     }
     //дополни ја класата

     static int setMAX(int p) {
        MAX = p;
     }

     friend ostream&operator<<(ostream&out, StudentKurs &s) {
        out<<s.ime<<" --- "<<s.ocena()<<endl;
        return out;
     }

     bool getDaliUsno() {
        return daliUsno;
     }

     virtual int ocena() { return ocenka; }

     char *getIme() {
        return ime;
     }

     const static int getMINOCENKA() {
        return MINOCENKA;
     }

     virtual ~StudentKurs() {}

};

int StudentKurs::MAX = 10;
const int StudentKurs::MINOCENKA = 6;


//вметни го кодот за StudentKursUsno

class StudentKursUsno : public StudentKurs {
private:
    char * opisna;

public:
    StudentKursUsno() :StudentKurs() {
        this->opisna = new char[0];
        daliUsno = true;
    }
    
    StudentKursUsno(char * ime, int finalenIspit) : StudentKurs(ime, finalenIspit) {
        this->opisna = new char[0];
        daliUsno = true;
    }

      StudentKursUsno(const StudentKursUsno &sku) : StudentKurs(sku)
    {
        this->opisna = new char [strlen(sku.opisna)+1];
        strcpy(this->opisna,sku.opisna);
    }

      StudentKursUsno& operator=(const StudentKursUsno &sku)
    {
        if(this!=&sku)
        {
            delete []opisna;
            strcpy(this->ime,sku.ime);
            this->daliUsno = sku.daliUsno;
            this->ocenka = sku.ocenka;
            this->opisna = new char [strlen(sku.opisna)+1];
            strcpy(this->opisna,sku.opisna);
        }
        return *this;
    }

     int ocena()
    {
        int osnovna = StudentKurs::ocena();
        if(strcmp(opisna,"odlicen")==0)
        {
            if(osnovna + 2<=MAX)
                return osnovna + 2;
            else if(osnovna + 1<=MAX)
                return osnovna + 1;
        }
        if(strcmp(opisna,"dobro")==0)
        {
            if(osnovna + 1<=MAX)
                return osnovna + 1;
        }
        if(strcmp(opisna,"losho")==0)
        {
            if(osnovna>1)
                return osnovna-1;
        }
        return osnovna;
    }


       StudentKursUsno& operator+=(char *nova)
    {
        for(int i=0;i<strlen(nova);i++)
        {
            if(!isalpha(nova[i]))
            {
                throw BadInputException("Greshna opisna ocenka");
            }
        }
        delete[]opisna;
        this->opisna = new char[strlen(nova)+1];
        strcpy(this->opisna,nova);
        return *this;
    }
    ~StudentKursUsno()
    {
        delete []opisna;
    }

};



class KursFakultet{
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;

public:
    KursFakultet(char *naziv, StudentKurs** studenti,int broj ){
      strcpy(this->naziv,naziv);
      for (int i=0;i<broj;i++){
        //ako studentot ima usno isprashuvanje
        if (studenti[i]->getDaliUsno()){
            this->studenti[i]=new StudentKursUsno(*dynamic_cast<StudentKursUsno*>(studenti[i]));
        }
        else this->studenti[i]=new StudentKurs(*studenti[i]);
      }
      this->broj=broj;
    }

    ~KursFakultet(){
    for (int i=0;i<broj;i++) delete studenti[i];
    }

    //дополни ја класата

    void pecatiStudenti() {
        cout<<"Kursot "<<naziv<<" go polozile:"<<endl;
        for(int i=0; i<broj; i++) {
            if(studenti[i]->ocena() >= StudentKurs::getMINOCENKA()) {
                cout<<*studenti[i];
            }
        }
    }

    void postaviOpisnaOcenka(char * ime, char * opisnaocenka) {
        for(int i=0; i<broj; i++) {
            if(strcmp(studenti[i]->getIme(), ime)==0) {
                if(studenti[i]->getDaliUsno()) {
                  StudentKursUsno * sku = dynamic_cast<StudentKursUsno*>(studenti[i]);
                    if(sku!=0)
                    {
                        *sku+=opisnaocenka;
                         break;
                    }
                }
            }
        }
    }

};

int main(){

 StudentKurs **niza;
    int n,m,ocenka;
    char ime[30],opisna[10];
    bool daliUsno;
    cin>>n;
    niza=new StudentKurs*[n];
    for (int i=0; i<n; i++)
    {
        cin>>ime;
        cin>>ocenka;
        cin>>daliUsno;
        if (!daliUsno)
            niza[i]=new StudentKurs(ime,ocenka);
        else
            niza[i]=new StudentKursUsno(ime,ocenka);
    }

    KursFakultet programiranje("OOP",niza,n);
    for (int i=0; i<n; i++) delete niza[i];
    delete [] niza;
    cin>>m;

    for (int i=0; i<m; i++)
    {
        cin>>ime>>opisna;
        try
        {
            programiranje.postaviOpisnaOcenka(ime,opisna);
        }
        catch(BadInputException &b)
        {
            b.message();
            char nova[30];
            int j=0;
            for(int i=0;i<strlen(opisna);i++)
            {
                if(isalpha(opisna[i]))
                {
                    nova[j] = opisna[i];
                    j++;
                }
            }
            programiranje.postaviOpisnaOcenka(ime,nova);
        }

    }

    StudentKurs::setMAX(9);

    programiranje.pecatiStudenti();

}
