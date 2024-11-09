Фирмата FINKI Cloud има потреба од решение за управување со image датотеките од различните оперативни системи кои ги користат при сетирање на нови сервери. За таа цел потребно е да се дефинираат следниве класи:

OperativenSistem
Во класата OperativenSistem треба да се чуваат следниве податоци:

име на оперативниот систем (динамички алоцирана низа од знаци)
верзија (float)
тип (енумерација со можни вредности LINUX, UNIX, WINDOWS)
големина (во GB) (float)
Дополнително, во рамките на класата потребно е да се дефинира:

конструктори со и без параметри
copy constructor
destructor
преоптоварување на операторот =
метод за печатење на информациите - void pecati() (видете го излезот од тест примерите за структурата)
метод за проверка на еднаквост помеѓу два оперативни системи (два оперативни системи се еднакви ако имаат исто име, верзија, тип и големина) - bool ednakviSe(const OperativenSistem &os)
метод за споредба на верзии помеѓу два оперативни система - int sporediVerzija(const OperativenSistem &os), кој ќе враќа 0 доколку верзиите се исти, -1 доколку верзијата на оперативниот систем од аргументот е поголема и 1 во преостанатиот случај.
метод за проверка дали два оперативни системи се од иста фамилија. Два оперативни системи се од иста фамилија доколку имаат исто име и се од ист тип. bool istaFamilija(const OperativenSistem &sporedba)
Repozitorium
Во класата Repozitorium треба да се чуваат следниве податоци:

име на репозиториумот (низа од 20 знака)
динамички алоцирана низа од OperativenSistem
број на оперативни системи кои моментално се наоѓаат во репозиториумот (int)
Дополнително, во рамките на класата потребно е да се дефинира:

конструктор Repozitorium(const char *ime)
деструктор
метод void pecatiOperativniSistemi() кој ќе ги печати сите оперативни системи кои се дел од репозиториумот
метод void izbrishi(const OperativenSistem &operativenSistem) кој ќе го избрише оперативниот систем проследен како аргумент, доколку тој се наоѓа во репозиториумот. Да се користи методот ednakviSe за споредба на два оперативни система.
метод за додавање на оперативен систем (void dodadi(const OperativenSistem &nov)) кој ќе го има следново однесување:
Доколку веќе постои оперативен систем од иста фамилија (да се користи методот за проверка на фамилија) кој е постар од проследениот оперативен систем, тогаш постоечкиот оперативен систем се заменува со новиот.
Во секој друг случај, проследениот оперативен систем се додава како дополнителен во репозиториумот.


#include <iostream>
#include <cstring>

using namespace std;

enum Tip {
    LINUX,
    UNIX,
    WINDOWS
};

class OperativenSistem {
private:
    char * name;
    float version;
    Tip type;
    float size;

    void copy(const OperativenSistem& other) {
        this->name = new char[strlen(other.name)+1];
        strcpy(this->name, other.name);

        this->version = other.version;
        this->type = other.type;
        this->size = other.size;
    }

public:
    OperativenSistem() {
    }

    OperativenSistem(char * name, float version, Tip type, float size) {
        this->name = new char[strlen(name)+1];
        strcpy(this->name, name);

        this->version = version;
        this->type = type;
        this->size = size;
    }

    OperativenSistem(const OperativenSistem& other) {
         copy(other);
    }

    ~OperativenSistem() {
        delete [] name;
    }

    OperativenSistem &operator =(const OperativenSistem& other) {
       if(this == &other) {
        return *this;
       }
       delete [] name;
       copy(other);
       return *this;
    }

    void pecati() {
        cout<<"Ime: "<<name<<" Verzija: "<<version<<" Tip: "<<type<<" Golemina:"<<size<<"GB"<<endl;
    }

    bool ednakviSe(const OperativenSistem &os) {
        return strcmp(this->name, os.name)==0 && version==os.version && type == os.type && size == os.size;
    }

    int sporediVerzija(const OperativenSistem&os) {
        if(version == os.version) {
            return 0;
        }
        else if(os.version > version) {
            return -1;
        }
        else {
            return 1;
        }
    }

    bool istaFamilija(const OperativenSistem &sporedba) {
        return strcmp(this->name, sporedba.name) == 0 && type == sporedba.type;
    }
};

class Repozitorium {

private:
    char name[20];
    OperativenSistem * systems;
    int count;
    
    void copy(const Repozitorium&other) {
        this->count = other.count;
        strcpy(this->name, other.name);
        systems = new OperativenSistem[count];
        
        for(int i=0; i<count; i++) {
            systems[i] = other.systems[i];
        }
    }

public:
    Repozitorium(char name[20] = "") {
        strcpy(this->name, name);
        count = 0;
        this->systems = new OperativenSistem [ count ];
    }
    
    Repozitorium(const Repozitorium&r) {
        copy(r);
    }
    

    ~Repozitorium() {
        delete [] systems;
    }

    void pecatiOperativniSistemi() {
        cout<<"Repozitorium: "<<name<<endl;
        for(int i=0; i<count; i++) {
            systems[i].pecati();
        }
    }

    void izbrishi(const OperativenSistem &operativenSistem) {
        int found = 0;

        for(int i=0; i<count; i++) {
            if(systems[i].ednakviSe(operativenSistem)) {
                found = 1;
                break;
            }
        }

        if(found) {
            OperativenSistem * tmp = new OperativenSistem[count-1];
            int j = 0;
            for(int i=0; i<count; i++) {
                if(!systems[i].ednakviSe(operativenSistem)) {
                    tmp[j++] = systems[i];
                }
            }
            count--;
            delete [] systems;
            systems = tmp;
        }
    }

    void dodadi(const OperativenSistem&nov) {
       for(int i=0; i<count; i++) {
            if(systems[i].istaFamilija(nov)) {
                if(systems[i].sporediVerzija(nov) == -1) {
                    systems[i] = nov;
                    return;
                }
            }
        }

        OperativenSistem * tmp = new OperativenSistem[count + 1];
        for(int i=0; i<count; i++) {
            tmp[i] = systems[i];
        }
        tmp[count++] = nov;
        delete [] systems;
        systems = tmp;
    }
};



int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
     cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}