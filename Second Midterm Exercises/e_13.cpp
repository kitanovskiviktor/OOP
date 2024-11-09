Да се креира класа која претставува слика (Image) во рамките на еден компјутер. За секоја датотека се чуваат (5 поени):

име на сликата (дин. алоцирана низа од знаци). Предефинирано поставено на untitled.
име на корисникот кој е сопственик на датотеката (низа од макс. 50 знаци). Предефинирано поставено на unknown.
димензии на сликата (2 цели броеви кои претставуваат ширина и висина во пиксели). Предефинирано поставени на 800.
Од класата Imageда се изведе класата TransparentImage, која претставува слика која содржи поддржува транспарентност. За транспарентна слика дополнително се чува :

дали поддржува нивоа на транспарентност (bool променлива, предефинирано не поддржува транспарентност).
За класите Image и TransparentImage да биде достапна метода (fileSize)за пресметка на големината на сликата (во бајти). Големината се пресметува на сл. начин (5 поени):

за објектите од класата Image, големината на датотеката е еднаква на:висината * ширината * 3.
за TransparentImage, доколку поддржува нивоа на транспарентност, големината на датотеката е еднаква на ширина * висина * 4. Доколку не поддржува транспарентност, големината на сликата се пресметува како ширина * висина + бр._на_пиксели_присутни_во_сликата / 8.
За класите Image и TransparentImage да се преоптоварат следниве оператори (5 поени):

оператор << кој ги печати податоците од датотеката во сл. формат:

ime_fajl avtor golemina_na_fajlot_vo_bajti

оператор > кој ги споредува сликите според нивната големина.

Да се дефинира класа Folder, што репрезентира директориум во кој може да се поставуваат слики. За секој фолдер се чува (5 поени):

име на фолдерот (низа од макс 255 знаци)
име на корисникот кој е сопственик на фолдерот (низа од макс. 50 знаци). Предефинирано поставено на unknown.
низа од покажувачи кон Image објекти (макс. 100 во рамките на еден фолдер).
Да се имплементираат следниве методи (5 поени):

метода за пресметка на големината на фолдерот (folderSize). Големината на фолдерот е сума од големините од сите слики во рамките на фолдерот.

метода за пронаоѓање на наголемата слика во рамките на фолдерот (getMaxFile). Методата враќа покажувач кон најголемата слика во фолдерот (сметано во бајти).

За класата Folder да се имплементира и оператор += кој додава објекти од типот Image/TransparentImage во рамките на фолдерот (5 поени).

Да се креираат следниве функционалности за класите (5 поени):

operator << - со кој се печатат податоците за фолдерот во формат (5 поени):

ime_folder sopstvenik --

imeslika avtor goleminanafajlotvo_bajti
imeslika avtor goleminanafajlotvobajti -- goleminanafoldervo_bajti
operator [] - кој враќа покажувач кон соодветната слика во фолдерот. Доколку не постои слика на тој индекс, треба да се врати NULL (5 поени).

Да се креира и глобална функција max_folder_size која го прима низа од објекти од типот Folder и го враќа фолдерот кој има зафаќа најмногу простор (во бајти). (5 поени)

Да се овозможи правилно функционирање на класите (потребни set или get методи/оператори/конструктори/деструктори) според изворниот код кој е веќе зададен. Сите податочни членови на класите се protected. (5 поени)


#include <cstring>
#include <iostream>

using namespace std;



class Image {
protected:
    char * ime;
    char owner[50];
    int sirina;
    int visina;

public:
    Image(char * ime = "untitled", char * owner = "unknown", int sirina = 800, int visina = 800) {
        this->ime = new char[strlen(ime)+1];
        strcpy(this->ime, ime);
        strcpy(this->owner, owner);
        this->sirina = sirina;
        this->visina = visina;
    }

    Image(const Image&other) {
         this->ime = new char[strlen(other.ime)+1];
        strcpy(this->ime, other.ime);
        strcpy(this->owner, other.owner);
        this->sirina = other.sirina;
        this->visina = other.visina;
    }

    Image&operator=(const Image&other) {
        if(this==&other) {
            return *this;
        }
        delete [] ime;
        this->ime = new char[strlen(other.ime)+1];
        strcpy(this->ime, other.ime);
        strcpy(this->owner, other.owner);
        this->sirina = other.sirina;
        this->visina = other.visina;
        return *this;
    }

    virtual int fileSize() {
        return visina * sirina * 3;
    }

    friend ostream&operator<<(ostream&out, Image&i) {
        out<<i.ime<<" "<<i.owner<<" "<<i.fileSize()<<endl;
        return out;
    }

    bool operator>(Image &i) {
        return this->fileSize() > i.fileSize();
    }


};

class TransparentImage : public Image {
protected:
    bool nivo;

public:
    TransparentImage(char * ime = "untitled", char * owner = "unknown", int sirina = 800, int visina = 800, bool nivo = true) : Image(ime,owner,sirina,visina) {
        this->nivo = nivo;
    }

    TransparentImage(const TransparentImage&other) : Image(other) {
        this->nivo = other.nivo;
    }

    TransparentImage&operator=(const TransparentImage&other) {
         if(this==&other) {
            return *this;
         }
         delete [] ime;
          this->ime = new char[strlen(other.ime)+1];
        strcpy(this->ime, other.ime);
        strcpy(this->owner, other.owner);
        this->sirina = other.sirina;
        this->visina = other.visina;
        this->nivo = other.nivo;
        return *this;

    }

    int fileSize() {
        if(nivo){
            return sirina * visina * 4;
        }
        return sirina * visina + (sirina*visina)/8;
    }

    friend ostream&operator<<(ostream&out, TransparentImage&i) {
        out<<i.ime<<" "<<i.owner<<" "<<i.fileSize()<<endl;
        return out;
    }

    bool operator>(TransparentImage&t) {
        return this->fileSize() > t.fileSize();
    }
};

class Folder {
private:
    char imeFolder[255];
    char ownerFolder[50];
    Image ** images;
    int n;

public:

    Folder(char * imeFolder ="", char * ownerFolder = "unknown", Image ** images = 0, int n = 0) {
        strcpy(this->imeFolder, imeFolder);
        strcpy(this->ownerFolder, ownerFolder);
        this->images = new Image*[n];
        this->n = n;
       // for(int i=0; i<n; i++) {
      //      this->images[i] = images[i];
       // }
    }

    Folder(const Folder&other) {
        strcpy(this->imeFolder, other.imeFolder);
        strcpy(this->ownerFolder, other.ownerFolder);
        this->n = other.n;
        for(int i = 0; i<n; i++) {
            this->images[i] = other.images[i];
        }
    }

    int folderSize() {
        int sumicka = 0;
        for(int i=0; i<n; i++) {
            sumicka+=images[i]->fileSize();
        }
        return sumicka;
    }

  //  Image * getMaxFile() {
  //      Image * maxFile = images[0];
   //     for(int i=0; i<n; i++) {
  //          if(images[i]->fileSize() > maxFile->fileSize()) {
   //             maxFile = images[i];
   //         }
   //     }
   //     return maxFile;
  //  }

    Image * getMaxFile() {
        Image * maxFile = images[0];
         for(int i=0; i<n; i++) {
            if(*images[i] > *maxFile) {
                *maxFile = *images[i];
            }
        }
        return maxFile;
    }

    Folder&operator+=(Image &i) {
        this->images[n++]=&i;
        return *this;
    }

    Folder&operator+=(TransparentImage&t) {
        this->images[n++]=&t;
            return *this;
    }

    friend ostream&operator<<(ostream&out, Folder&f) {
        out<<f.imeFolder<<" "<<f.ownerFolder<<endl;
        out<<"--"<<endl;
        for(int i=0; i<f.n; i++) {
            out<<*(f.images[i]);
        }
        out<<"--"<<endl;
        out<<"Folder size: "<<f.folderSize()<<endl;
        return out;
    }

    Image *operator[](int a) {
        if(a < 0 || a > n) {
            return 0;
        }
        return images[a];

    }
};

Folder &max_folder_size(Folder *niza, int n) {
    int maxFolder = niza[0].folderSize();
    int f = 0;
    for(int i=0; i<n; i++) {
        if(niza[i].folderSize()>maxFolder) {
            maxFolder = niza[i].folderSize();
            f = i;
        }
    }
    return niza[f];
}


int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
      // Testing constructor(s) & operator << for class File

      cin >> name;
      cin >> user_name;
      cin >> w;
      cin >> h;


      Image f1;

      cout<< f1;

      Image f2(name);
      cout<< f2;

      Image f3(name, user_name);
      cout<< f3;

      Image f4(name, user_name, w, h);
      cout<< f4;
    }
    else if (tc==2){
      // Testing constructor(s) & operator << for class TextFile
      cin >> name;
      cin >> user_name;
      cin >> w >> h;
      cin >> tl;

      TransparentImage tf1;
      cout<< tf1;

      TransparentImage tf4(name, user_name, w, h, tl);
      cout<< tf4;
    }
    else if (tc==3){
      // Testing constructor(s) & operator << for class Folder
      cin >> name;
      cin >> user_name;

      Folder f3(name, user_name);
      cout<< f3;
    }
    else if (tc==4){
      // Adding files to folder
      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image * f;
      TransparentImage *tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
        }
      }
      cout<<dir;
    }
    else if(tc==5){
      // Testing getMaxFile for folder

      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image* f;
      TransparentImage* tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
        }
      }
      cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
      // Testing operator [] for folder

      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image* f;
      TransparentImage* tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
        }
      }

      cin >> sub; // Reading index of specific file
      cout<< *dir[sub];
    }
    else if(tc==7){
      // Testing function max_folder_size
      int folders_num;

      Folder dir_list[10];

      Folder dir;
      cin >> folders_num;

      for (int i=0; i<folders_num; ++i){
        cin >> name;
        cin >> user_name;
        dir = Folder(name, user_name);


        Image* f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
          cin >> sub; // Should we add subfiles to this folder
          if (!sub) break;

          cin >>fileType;
          if (fileType == 1){ // Reading File
            cin >> name;
            cin >> user_name;
            cin >> w >> h;
            f = new Image(name,user_name, w, h);
              dir += *f;
          }
          else if (fileType == 2){
            cin >> name;
            cin >> user_name;
            cin >> w >> h;
            cin >> tl;
            tf = new TransparentImage(name,user_name, w, h, tl);
              dir += *tf;
          }
        }
        dir_list[i] = dir;
      }

      cout<<max_folder_size(dir_list, folders_num);
    }
  return 0;
}

