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
        this->niza_broevi = new int[brojac];
        for (int i = 0; i < brojac; i++) {
            this->niza_broevi[i] = niza_broevi[i];
        }

        this->brojac=brojac;
    }
    //copy constructor
    List(const List& copyList){
        this->niza_broevi = new int[copyList.brojac];

        for (int i = 0; i < copyList.brojac; i++) {
            this->niza_broevi[i] = copyList.niza_broevi[i];
        }

        this->brojac=copyList.brojac;
    }


    //destructor
    ~List(){
        delete []niza_broevi;
    }
    //operator =

    List& operator=(const List& other)
    {
        if(this !=  &other) { // moze i bez ova, ama dobra praktika e da se proveri self assigment, ako vrednostite se isti na dvata objekta, nema potreba da se aktiviraat operaciite vo blokot naredbi
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

      //  cout<<""
        //[број на елементи во листата]: x1 x2 .. xn sum: [сума] average: [просек]
    }

//todo
    int sum() {

        int sum=0;

        for(int i =0;i<this->brojac;i++)
        {
            sum=sum+this->niza_broevi[i];
        }
        //vrakja suma na elementite vo listata
    return sum;
    }

//todo
    double average() {
        double average=0.0;

        average=sum()/this->brojac;
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
//copy constructor
//destruktor
//operator =

//todo
    void pecati() {
        //List number: [реден број на листата] List info: [испечатени информации за листата со методот List::pecati()] \n sum: [сума] average: [просек]
        //доколку контејнерот е празен се печати само порака The list is empty.
    }

//todo - metod sho dodava lista vo kontejnerot
    void addNewList(List l) {
//Напомена: една листа се додава во контејнерот ако и само ако има различна сума од сите листи што се веќе додадени во контејнерот
    }

    //todo
    int sum() {
        //sumata na site elementi vo site listi
    }

//todo
    double average() {
        /*   метод што го враќа просекот на сите елементи во      сите      листи       во контејнерот*/
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