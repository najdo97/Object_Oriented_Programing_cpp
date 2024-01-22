#include <iostream>

using namespace std;

class List {
private:
    int *niza_broevi;
    int brojac;
public:
    //constructor
    //copy constructor
    //destructor
    //operator =

//todo
    void pecati() {
        //[број на елементи во листата]: x1 x2 .. xn sum: [сума] average: [просек]
    }

//todo
    int sum() {
        //vrakja suma na elementite vo listata
    }

//todo
    double average() {
        //prosekot na broevite vo listata
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