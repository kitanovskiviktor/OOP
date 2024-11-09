Да се креира класа Customer за опишување на купувачи на една книжара. За секој купувач се чуваат податоци за:

името (низа од 50 знаци),
електронска адреса (низа од 50 знаци),
вид на купувач (стандардни, лојални или вип),
основен попуст (цел број изразен во проценти),
дополнителен попуст (цел број изразен во проценти) и
број на купени производи. (5 поени)
Сите лојални купувачи со покажување на клуб картичка имаат право на основниот попуст при купување од книжарата. Основниот попуст е ист за сите лојални купувачи и изнесува 10%. Оваа вредност може да се смени со одлука на раководството на книжарата. Дополнителниот попуст е фиксен и може да го користат само вип купувачите и изнесува 20%. Стандардните купувачи немаат право на попуст (5 поени).

За оваа класа да се имплементира оператор << за печатење на купувач во формат:

[ime_na_kupuvac]
[email_na_kupuvac]
[broj_na_proizvodi]
[vid_na_kupuvac] [popust_sto_moze_da_go_koristi]
каде попустот е 0% ако купувачот е стандарден, вредноста на основниот попуст, ако е лојален или збир од основниот и дополнителниот попуст, ако купувачот е вип. (5 поени)

Да се креира класа за онлајн книжара FINKI-bookstore во која се чува низа од регистрирани купувачи (динамички алоцирана низа) и број на купувачи. (5 поени) За класата да се обезбедат:

operator+= (10 поени) за додавање купувач во листата од купувачи, но само ако веќе не е дел од неа (ако во листата нема купувач со иста електронска адреса). Ако во листата постои корисник со иста електронска адреса, треба да се генерира исклучок UserExistsException. Потребно е да се обезбеди справување со исклучокот во функцијата main на означеното место. Во ваква ситуација се печати порака "The user already exists in the list" (5 поени).
Функција update со која сите стандардни купувачи со купени повеќе од 5 производи стануваат лојални, а сите лојални купувачи со над 10 купени производи, стануваат вип (5 поени).
Оператор << за печатење на информациите за сите регистрирани купувачи (5 поени).
Да се обезбедат сите дополнителни методи потребни за правилно функционирање на програмата. (10 поени)

#include <iostream>
#include <cstring>

using namespace std;
#define MAX 100


class UserExistsException {
public:
    void message() {
        cout<<"The user already exists in the list!"<<endl;
    }
};

enum customerType {
    standard,
    loyal,
    vip
};

class Customer {

protected:
    char name[50];
    char email[50];
    customerType type;
    int baseDiscount;
    static int additionalDiscount;
    int numProducts;

public:

    void setType(customerType type) {
        this->type = type;
        if(type==loyal) baseDiscount=10;
    }

    int getProducts() {
        return numProducts;
    }

    customerType getType() {
        return type;
    }

    char * getEmail() {
        return email;
    }

    void setDiscount1(int d) {
        baseDiscount = d;
    }

    Customer() {}

    Customer(char * name, char * email, customerType type, int numProducts) {
             strcpy(this->name, name);
             strcpy(this->email, email);
             this->type = type;
             this->additionalDiscount = additionalDiscount;
             this->numProducts = numProducts;
             if(type == loyal || type == vip) {
                baseDiscount = 10;
             }
            else {
                baseDiscount = 0;
            }

    }

      friend ostream &operator<<(ostream &os, Customer &c){
            os<<c.name<<endl<<c.email<<endl<<c.numProducts<<endl;
            if(c.type==standard) os<<"standard "<<0<<endl;
            if(c.type==loyal) os<<"loyal "<<c.baseDiscount<<endl;
            if(c.type==vip) os<<"vip "<<c.baseDiscount+c.additionalDiscount<<endl;
            return os;
        }
};

int Customer::additionalDiscount = 20;

class FINKI_bookstore : public Customer {
private:
    Customer * customers;
    int count;


public:
    FINKI_bookstore() {}

    FINKI_bookstore(char * name, char * email, customerType type, int numProducts,
             Customer * customers, int count) : Customer(name, email, type, numProducts) {
                this->count = count;
                this->customers = new Customer[count];
                for(int i = 0; i<count; i++) {
                    this->customers[i]=customers[i];
                }
             }

    FINKI_bookstore(const FINKI_bookstore &other) {
        strcpy(name, other.name);
        strcpy(email, other.email);
        type = other.type;
        numProducts = other.numProducts;
        count = other.count;
        for(int i=0; i<count; i++) {
            customers[i] = other.customers[i];
        }
    }

   FINKI_bookstore&operator=(const FINKI_bookstore&other) {
        if(this==&other) {
            return *this;
        }
        delete [] customers;
        strcpy(name, other.name);
        strcpy(email, other.email);
        type = other.type;
        numProducts = other.numProducts;
        count = other.count;
        for(int i=0; i<count; i++) {
            customers[i] = other.customers[i];
        }
        return *this;
    }

    FINKI_bookstore&operator+=(Customer&other) {
        for(int i=0; i<count; i++) {
            if(strcmp(customers[i].getEmail(), other.getEmail())==0) {
                throw UserExistsException();
            }
        }

        Customer * temp = new Customer[count+1];
        for(int i=0; i<count; i++) {
            temp[i]=customers[i];
        }
        temp[count++]=other;
        delete [] customers;
        customers=temp;
        return *this;
    }

    void update() {
        for(int i=0; i<count; i++) {
            if(customers[i].getType()==standard && customers[i].getProducts() > 5) {
                customers[i].setType(loyal);
                continue;
            }
            if(customers[i].getType()==loyal && customers[i].getProducts() > 10) {
                customers[i].setType(vip);
                continue;
            }
        }
    }

    friend ostream&operator<<(ostream &os, FINKI_bookstore & f) {
        for(int i=0; i<f.count; i++) {
            os<<f.customers[i];
        }
        return os;
    }

    void setCustomers(Customer * c, int n) {
        if(count!=0) {
            delete [] customers;
        }
        count = n;
        customers = new Customer[n];
        for(int i=0; i<n; i++) {
            customers[i] = c[i];
        }
    }


};




int main(){
   int testCase;
  cin >> testCase;

  char name[MAX];
  char email[MAX];
  int tC;
  int discount;
  int numProducts;


  if (testCase == 1){
    cout << "===== Test Case - Customer Class ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (customerType) tC, numProducts);
    cout << c;

  }

  if (testCase == 2){
    cout << "===== Test Case - Static Members ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (customerType) tC, numProducts);
    cout << c;

    c.setDiscount1(5);

    cout << c;
  }

  if (testCase == 3){
    cout << "===== Test Case - FINKI-bookstore ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (customerType) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << fc <<endl;
  }

  if (testCase == 4){
    cout << "===== Test Case - operator+= ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (customerType) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    Customer c(name, email, (customerType) tC, numProducts);
    fc+=c;

    cout << fc;
  }

  if (testCase == 5){
    cout << "===== Test Case - operator+= (exception) ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    Customer temp;
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (customerType) tC, numProducts);
      customers[i] = c;
      temp = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    try{
        fc+=temp;
    }catch(UserExistsException e){
        e.message();
    }

    cout << fc;
  }

  if (testCase == 6){
    cout << "===== Test Case - update method  ======" << endl << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (customerType) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << "Update:" << endl;
    fc.update();
    cout << fc;
  }
  return 0;

}
