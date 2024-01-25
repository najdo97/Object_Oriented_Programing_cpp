#include <iostream>

using namespace std;

class List {
private:
    int *niza_broevi;
    int brojac;
public:
    //constructor
    List() {};

    List(int *niza_broevi, int brojac) {

        cout<<"constructor na List"<<endl;
        this->niza_broevi = new int[brojac];
        for (int i = 0; i < brojac; i++) {
            this->niza_broevi[i] = niza_broevi[i];
        }

        this->brojac = brojac;
    }

    //copy constructor
    List(const List &copyList) {
        this->niza_broevi = new int[copyList.brojac];

        for (int i = 0; i < copyList.brojac; i++) {
            this->niza_broevi[i] = copyList.niza_broevi[i];
        }

        this->brojac = copyList.brojac;
    }


    //destructor
    ~List() {
        delete[]niza_broevi;
    }
    //operator =

    List &operator=(const List &other) {
        if (this !=
            &other) { // moze i bez ova, ama dobra praktika e da se proveri self assigment, ako vrednostite se isti na dvata objekta, nema potreba da se aktiviraat operaciite vo blokot naredbi
            this->niza_broevi = new int[other.brojac];
            for (int i = 0; i < other.brojac; i++) {
                this->niza_broevi[i] = other.niza_broevi[i];
            }
            this->brojac = other.brojac;
        }
        return *this;
    }

//todo
    void pecati() {

        cout << this->brojac <<": ";
        for (int i = 0; i < this->brojac; i++) {
            cout << this->niza_broevi[i]<<" ";
        }
        cout << sum() << " " << average();

        //[број на елементи во листата]: x1 x2 .. xn sum: [сума] average: [просек]
    }

//todo
    int sum() {

        int sum = 0;

        for (int i = 0; i < this->brojac; i++) {
            sum = sum + this->niza_broevi[i];
        }
        //vrakja suma na elementite vo listata
        return sum;
    }

//todo
    double average() {
        double average = 0.0;

        average = sum() / this->brojac;
        //prosekot na broevite vo listata
        return average;
    }
};

class ListContainer {

private:
    List *niza_listi;
    int broj_na_listi;
    int obidi;  //se inicijalizira na 0 vo konstruktorot

public:

    //default construcotr - obidi se inicijalizira na 0
    ListContainer() {

        // todo - how do i iterate and initilize the default values of a dynamic array ? - sakam site clenovi da se inicijalizirani na 0

        this->broj_na_listi=0;
        this->obidi = 0;

        }

    //parametarized constructor
    ListContainer(List *niza_listi, int broj_na_listi, int obidi) {

        this->niza_listi = new List[broj_na_listi];   // inicijaliziranje i rezerviranje mem lokacija

        for (int i = 0; i < broj_na_listi; i++) {
            this->niza_listi[i] = niza_listi[i];      // dodeluvanje na vrednost an site clenovi
        }

        this->broj_na_listi = broj_na_listi;
        this->obidi = obidi;
    }

    //copy constructor

    ListContainer(const ListContainer &copyListContainer) {

        this->niza_listi = new List[copyListContainer.broj_na_listi];   // inicijaliziranje i rezerviranje mem lokacija

        for (int i = 0; i < copyListContainer.broj_na_listi; i++) {
            this->niza_listi[i] = copyListContainer.niza_listi[i];      // dodeluvanje na vrednost an site clenovi
        }

        this->broj_na_listi = copyListContainer.broj_na_listi;
        this->obidi = copyListContainer.obidi;
    }

    //destruktor
    ~ListContainer() {
        delete[]niza_listi;
    }


    //operator =
    ListContainer &operator=(const ListContainer &other) {

        if (this != &other) {

            this->niza_listi = new List[other.broj_na_listi];
            for (int i = 0; i < other.broj_na_listi; i++) {
                this->niza_listi[i] = other.niza_listi[i];
            }
            this->broj_na_listi = other.broj_na_listi;
            this->obidi = other.obidi;

        }
        return *this; // vrakja pokazuvac kon samiot ovoj objekt
    }


/*todo
    метод што ќе ги печати информациите за контејнерот во форматот:
    List number: [реден број на листата]
    List info: [испечатени информации за листата со методот List::pecati()] \n sum: [сума] average: [просек]
    доколку контејнерот е празен се печати само порака The list is empty.
*/
    void print() {
        if (this->broj_na_listi==0){
            cout<<"The list is empty"<<endl;
        }
        else {

            for (int i = 0; i < this->broj_na_listi; i++) {
                cout<<"List number: " << this->broj_na_listi ;
            }

            for (int i = 0; i < this->broj_na_listi; i++) {
                cout<<"List info: " ;
                this->niza_listi[i].pecati();
            }

        }
    }

//todo - void addNewList(List l) метод со којшто се додава листа во контејнерот
//Напомена: една листа се додава во контејнерот ако и само ако има различна сума од сите листи што се веќе додадени во контејнерот

    void addNewList(List l) {
        cout<<" vleze vo addNewList"<<endl;
        this->obidi++;
        bool check = false;

        for (int i = 0; i < this->broj_na_listi; i++) {
            cout<<" vleze vo for Loop"<<endl;

            if (this->niza_listi[i].sum() == l.sum()) {
                check = true;
                break;
            }
        }
        if (check == false) //if sucsessfull, zanci ima vekje ima lista so ista suma
        {
            cout<<" vleze vo if uslov, zanci ke probame da ja dodademe novata lista"<<endl;
            cout<<this->broj_na_listi<<endl;
            cout<<&broj_na_listi<<endl;

            /*
             Za da mozeme da dodademe nov clen na nizata, morame starata niza da ja kopirame privremeno vo druga niza koja ke
             ima novoalocirana memorija za +1 clen. Otposle treba site vrednosti da gi prefrlime vo novata niza, i na kraj
             da go dodademe noviot clen.

             */
            //todo - alociraj memorija na nova lista taka shto ke ima +1 clen novata lista
            //todo - kopiraj gi clenovite od nova stara lista vo nova lista
            //todo - dodaj go noviot clen na listata so = operator, toj sho go prepokri pogore !


            // this->broj_na_listi++;                      // ne sum siguren deka ova e dovolno, bidejki ovdeka nikade ne go inicijalizirame ovoj nov clen
            // this-> niza_listi=new List[this->broj_na_listi];    // ova e vozmozno bidejki go overloadnavme = operatorot
            // this->niza_listi[this->broj_na_listi]=l;    // ova e vozmozno bidejki go overloadnavme = operatorot
        }

    }

    int sum() {

        int suma=0;
        for (int i = 0; i < this->broj_na_listi; i++) {
            suma = suma + this->niza_listi[i].sum();
        }
        return suma;
    }


    double average() {
        double prosek=0;
        for (int i = 0; i < this->broj_na_listi; i++) {
            prosek = prosek + this->niza_listi[i].average();
        }
        return prosek;
    }
};


int main() {

    ListContainer lc;
    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        int n;
        int niza[100];

        cin >> n;

        for (int j = 0; j < n; j++) {
            cin >> niza[j];

        }

        List l = List(niza, n);

        lc.addNewList(l);
    }


    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "Test case for operator =" << endl;
        ListContainer lc1;
        lc1.print();
        cout << lc1.sum() << " " << lc.sum() << endl;
        lc1 = lc;
        lc1.print();
        cout << lc1.sum() << " " << lc.sum() << endl;
        lc1.sum();
        lc1.average();

    } else {
        lc.print();
    }
}