#include <iostream>

using namespace std;

class List {
private:
    int *niza_broevi;
    int brojac;


public:

    int getBrojac() {
        return brojac;
    }

    //constructor
    List() {
        niza_broevi = nullptr;
        brojac = 0;
    };

    List(int *niza_broevi, int brojac) {

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

    List &operator=(const List& other) {
        if (this != &other) {
            delete[] this->niza_broevi;     //todo - tuka javuva bug

            this->niza_broevi = new int[other.brojac];

            for (int i = 0; i < other.brojac; i++) {
                this->niza_broevi[i] = other.niza_broevi[i];
            }
            this->brojac = other.brojac;
        }
        return *this;
    }

    void pecati() {

        cout << this->brojac << ": ";
        for (int i = 0; i < this->brojac; i++) {
            cout << this->niza_broevi[i] << " ";
        }
        cout <<"sum: " <<sum() << " " <<"average: " << average()<< endl;
    }

   int sum() {

        int sum = 0;

        for (int i = 0; i < this->brojac; i++) {
            sum = sum + this->niza_broevi[i];
        }
        return sum;
    }

    double average() {
        double average = 0.0;
        average = (double)sum() / this->brojac;

        return average;
    }
};

class ListContainer {

private:
    List *niza_listi;
    int broj_na_listi;
    int obidi;


public:

    //default construcotr - obidi se inicijalizira na 0
    ListContainer() {


        this->niza_listi = new List[25];
        this->broj_na_listi = 0;
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
            delete[]niza_listi;         //todo - tuka ke javuva bug
            this->niza_listi = new List[25];

            for (int i = 0; i < other.broj_na_listi; i++) {
                this->niza_listi[i] = other.niza_listi[i];
            }
            this->broj_na_listi = other.broj_na_listi;
            this->obidi = other.obidi;
        }
        return *this; // vrakja pokazuvac kon samiot ovoj objekt
    }

    void print() {
        if (this->broj_na_listi <= 0) {
            cout << "The list is empty" << endl;
        } else {

            for (int i = 0; i < this->broj_na_listi; i++) {
                cout << "List number: " << i+1 << " List info: ";
                this->niza_listi[i].pecati();
            }
            cout << "Sum: " << sum() << " Average: " << average() << "\n";
            cout << "Successful attempts: " << this->broj_na_listi << " Failed attempts: " << (obidi - broj_na_listi) << "\n";

        }
    }



    void addNewList(List l) {

        obidi++;
        bool check = false;

        for (int i = 0; i < this->broj_na_listi; i++) {

            if (this->niza_listi[i].sum() == l.sum()) {
                check = true;
                break;
            }
        }
        if (check == false) //if sucsessfull, zanci ima vekje ima lista so ista suma
        {
           this->niza_listi[this->broj_na_listi++] = l;
        }

    }


    int sum() {

        int suma = 0;
        for (int i = 0; i < this->broj_na_listi; i++) {
            suma = suma + this->niza_listi[i].sum();
        }
        return suma;
    }


    double average() {
        double prosek = 0;
        for (int i = 0; i < this->broj_na_listi; i++) {
            prosek = prosek + this->niza_listi[i].getBrojac();
        }

        return (double)sum()/prosek;
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