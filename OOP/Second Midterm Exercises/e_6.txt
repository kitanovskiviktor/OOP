Потребно е да се имплементира класа за компјутерска игра (Game), што содржи информации за:

име на играта (низа од макс. 100 знаци)
цена на играта (децимален број)
дали е играта купена на распродажба (bool променлива).
Од класата Game да се изведе класа SubscriptionGame, што дополнително ќе чува:

месечен надоместок за играње (децимален број).
датум кога играта е купена (месец и година како позитивни цели броеви)
За класите Game и SubscriptionGame да се преоптоварат операторите за печатење (<<) и читање (>>). Да се дефинира и операторот == кој ќе споредува игри според нивното име.

Да се дефинира класа за корисник (User) во која се чуваат:

кориснично име на корисникот (низа од макс. 100 знаци)
колекција од игри кои се купени од корисникот (динамички алоцирана низа).
Да се преоптовари операторот += кој ќе овозможи додавање на нова игра во колекцијата на игри. Притоа ако корисникот ја има веќе купено играта, потребно е да се креира исклучок од типот ExistingGame. Класата за имплементација на исклучоци потребно е има соодветен конструктор и метода message за печатење на порака на екран.

Да се креира и метода total_spent() во класата User која ќе пресметува колку пари корисникот потрошил за својата колекција од игри. Доколку играта е купена на распродажба, цената на играта е 30% од стандарната цена. Доколку играта е од типот SubscriptionGame, потребно е да се вкалкулира и сумата потрошена за месечниот надоместок (број_на_изминати_месеци x цена_на_месечен_надоместок) без да се земе во предвид моменталниот месец (мај 2018).

Да се преоптовари и оператоторот за печатење на корисникот, која печати информации во сл. формат (види тест примери 7 до 12):

User: username
- Game: PUBG, regular price: $70, bought on sale
- Game: Half Life 2, regular price: $70 - Game: Warcraft 4, regular price: $40, monthly fee: $10, purchased: 1-2017

Листа на дел од методите со нивни прототипови кои се користат во main:

ЕxistingGame::message()
Game::operator==(Game&)
User::operator+=(Game&)
User::get_game(int)
User::total_spent(int)
User::get_name()
User::get_games_number()


#include <iostream>
#include <cstring>
using namespace std;


class ExistingGame {
public:
    void print() {
        cout<<"The game is already in the collection"<<endl;
    }
};


class Game {
protected:
    char name[100];
    float price;
    bool onSale;

    void copy(const Game&other) {
        strcpy(this->name, other.name);
        this->price = other.price;
        this->onSale = other.onSale;
    }

public:

    Game() {}

    Game(char * name, float price, bool onSale) {
        strcpy(this->name, name);
        this->price = price;
        this->onSale = onSale;
    }

    Game(const Game&other) {
        copy(other);
    }

    Game&operator=(const Game&other) {
        if(this==&other) {
            return *this;
        }
        copy(other);
        return *this;
    }

    virtual float totalPrice() {
        if(onSale) {
            return price * 0.7;
        }
        return price;
    }

    friend ostream&operator<<(ostream&out, Game&g) {
        out<<"Game: "<<g.name<<", regular price: $"<<g.price;
        if(g.onSale) {
            out<<", bought on sale";
        }
        out<<endl;
        return out;
    }


    friend istream&operator>>(istream &in, Game&g) {
        in.get();
        in.getline(g.name, 100);

        in >> g.price >> g.onSale;
        return in;
    }

    bool operator==(Game&g) {
        return (strcmp(name, g.name)==0);
    }
};

class SubscriptionGame : public Game {
protected:
    float nadomestok;
    int godina;
    int mesec;

    void copy(const SubscriptionGame&other) {
         this->nadomestok = other.nadomestok;
        this->godina = other.godina;
        this->mesec = other.mesec;
    }

public:

    SubscriptionGame(){}
    SubscriptionGame(char * name, float price, bool onSale, float nadomestok, int mesec, int godina)
    : Game(name,price,onSale) {
        this->nadomestok = nadomestok;
        this->godina = godina;
        this->mesec = mesec;
    }

    SubscriptionGame(const SubscriptionGame&other): Game(other) {
        copy(other);
    }

    SubscriptionGame&operator=(const SubscriptionGame&other) {
        if(this==&other) {
            return *this;
        }
        Game::operator=(other);
        copy(other);
        return *this;
    }

    float totalPrice() {
        float tGame = Game::totalPrice();
        float temp;
        if(godina<2018) {
            temp = (12 -  mesec) + (2017-godina) * 12 + 5;
        }
        else {
            temp = 5 - mesec;
        }
        tGame += temp * nadomestok;
        return tGame;
    }

       friend ostream&operator<<(ostream&out, SubscriptionGame&g) {
       out<<"Game: "<<g.name<<", regular price: $"<<g.price;
       if(g.onSale) {
            out<<", bought on sale";
       }
        out<<", monthly fee: $"<<g.nadomestok<<", purchased: "<<g.mesec<<"-"<<g.godina<<endl;
        return out;
    }

    friend istream&operator>>(istream&in, SubscriptionGame&g) {
         in.get();
        in.getline(g.name, 100);
        in >> g.price >> g.onSale >> g.nadomestok >> g.mesec >> g.godina;
        return in;
    }

};


class User {
protected:
    char nameUser[100];
    Game **games;
    int count;

    void copy(const User&other) {
     strcpy(this->nameUser, other.nameUser);
        this->count = other.count;
        this->games = new Game*[count];
        for(int i=0; i<count; i++){
            this->games[i] = other.games[i];
        }
    }

public:

    User(const User&other) {
       copy(other);
    }

    User(char *nameUser) {
        strcpy(this->nameUser, nameUser);
        this->count=0;
        games = new Game*[0];
    }

    User&operator=(const User&other) {
        if(this==&other) {
            return *this;
        }
        delete [] games;
        copy(other);
        return *this;
    }

    User&operator+=(Game &g) {
        for(int i=0; i<count; i++) {
            if(*games[i]==g) {
                throw ExistingGame();
            }
        }

        Game ** temp = new Game*[count+1];
        for(int i=0; i<count; i++) {
            temp[i]=games[i];
        }
        temp[count++]=&g;
        delete [] games;
        games=temp;
        return *this;
    }

    float total_spent() {
        float totalka = 0;
        for(int i=0; i<count; i++) {
            totalka +=games[i]->totalPrice();
        }
        return totalka;
    }

    friend ostream&operator<<(ostream&out, User&u) {
        out<<"\nUser: "<<u.nameUser<<endl;
        for(int i=0; i<u.count; i++) {
            out<<"- ";
            SubscriptionGame * temp=dynamic_cast<SubscriptionGame*>(u.games[i]);
            if(temp) {
                out<<*temp;
            }
            else {
                out<<*u.games[i];
            }
        }
        out<<endl;
        return out;
    }


};



int main() {
    int test_case_num;
 cin>>test_case_num;

  // for Game
  char game_name[100];
  float game_price;
  bool game_on_sale;

  // for SubscritionGame
  float sub_game_monthly_fee;
  int sub_game_month, sub_game_year;

  // for User
  char username[100];
  int num_user_games;

  if (test_case_num == 1){
    cout<<"Testing class Game and operator<< for Game"<<std::endl;
    cin.get();
    cin.getline(game_name,100);
    //cin.get();
    cin>>game_price>>game_on_sale;

    Game g(game_name, game_price, game_on_sale);

    cout<<g;
  }
  else if (test_case_num == 2){
    cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<std::endl;
    cin.get();
    cin.getline(game_name, 100);

    cin>>game_price>>game_on_sale;

    cin>>sub_game_monthly_fee;
    cin>>sub_game_month>>sub_game_year;

    SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
    cout<<sg;
  }
  else if (test_case_num == 3){
    cout<<"Testing operator>> for Game"<<std::endl;
    Game g;

    cin>>g;

    cout<<g;
  }
  else if (test_case_num == 4){
    cout<<"Testing operator>> for SubscriptionGame"<<std::endl;
    SubscriptionGame sg;

    cin>>sg;

    cout<<sg;
  }
  else if (test_case_num == 5){
    cout<<"Testing class User and operator+= for User"<<std::endl;
    cin.get();
    cin.getline(username,100);
    User u(username);

    int num_user_games;
    int game_type;
    cin >>num_user_games;

    try {

      for (int i=0; i<num_user_games; ++i){

        cin >> game_type;

        Game *g;
        // 1 - Game, 2 - SubscriptionGame
        if (game_type == 1){
          cin.get();
          cin.getline(game_name, 100);

          cin>>game_price>>game_on_sale;
          g = new Game(game_name, game_price, game_on_sale);
        }
        else if (game_type == 2){
          cin.get();
          cin.getline(game_name, 100);

          cin>>game_price>>game_on_sale;

          cin>>sub_game_monthly_fee;
          cin>>sub_game_month>>sub_game_year;
          g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        }

        //cout<<(*g);


        u+=(*g);
      }
    }catch(ExistingGame &ex){
      ex.print();
    }

    cout<<u;

//    cout<<"\nUser: "<<u.get_username()<<"\n";

//    for (int i=0; i < u.get_games_number(); ++i){
//        Game * g;
//        SubscriptionGame * sg;
//        g = &(u.get_game(i));

//        sg = dynamic_cast<SubscriptionGame *> (g);

//        if (sg){
//          cout<<"- "<<(*sg);
//        }
//        else {
//          cout<<"- "<<(*g);
//        }
//        cout<<"\n";
//    }

  }
  else if (test_case_num == 6){
      cout<<"Testing exception ExistingGame for User"<<std::endl;
      cin.get();
      cin.getline(username,100);
      User u(username);

      int num_user_games;
      int game_type;
      cin >>num_user_games;

      for (int i=0; i<num_user_games; ++i){

          cin >> game_type;

          Game *g;
          // 1 - Game, 2 - SubscriptionGame
          if (game_type == 1){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;
            g = new Game(game_name, game_price, game_on_sale);
          }
          else if (game_type == 2){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;

            cin>>sub_game_monthly_fee;
            cin>>sub_game_month>>sub_game_year;
            g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
          }

          //cout<<(*g);

          try {
            u+=(*g);
          }
          catch(ExistingGame &ex){
            ex.print();
          }
        }

      cout<<u;

//      for (int i=0; i < u.get_games_number(); ++i){
//          Game * g;
//          SubscriptionGame * sg;
//          g = &(u.get_game(i));

//          sg = dynamic_cast<SubscriptionGame *> (g);

//          if (sg){
//            cout<<"- "<<(*sg);
//          }
//          else {
//            cout<<"- "<<(*g);
//          }
//          cout<<"\n";
//      }
  }
  else if (test_case_num == 7){
      cout<<"Testing total_spent method() for User"<<std::endl;
      cin.get();
      cin.getline(username,100);
      User u(username);

      int num_user_games;
      int game_type;
      cin >>num_user_games;

      for (int i=0; i<num_user_games; ++i){

          cin >> game_type;

          Game *g;
          // 1 - Game, 2 - SubscriptionGame
          if (game_type == 1){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;
            g = new Game(game_name, game_price, game_on_sale);
          }
          else if (game_type == 2){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;

            cin>>sub_game_monthly_fee;
            cin>>sub_game_month>>sub_game_year;
            g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
          }

          //cout<<(*g);


          u+=(*g);
        }

      cout<<u;

      cout<<"Total money spent: $"<<u.total_spent()<<endl;
  }

    return 0;
}


