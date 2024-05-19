#include <iostream>
#include <cstring>


using namespace std;

static int konferenciski_trud = 1;
static int spisanie_trud = 3;

class Exception {
private:
public:

    void message() {
        cout << "Ne moze da se vnese dadeniot trud" << endl;
    }
};


class Trud {
private:

    char vidTrud; //(еден знак и тоа C за конференциски труд, J за труд во списание)
    int godIzdavanje;

public:

    char getVidTrud() const {
        return vidTrud;
    }

    int getGodIzdavanje() const {
        return godIzdavanje;
    }

    Trud() {
        this->vidTrud = 'z';
        this->godIzdavanje = 0;
    }

    Trud(char vidTrud, int godIzdavanje) {
        this->vidTrud = vidTrud;
        this->godIzdavanje = godIzdavanje;
    }

    Trud(const Trud &t) {
        this->vidTrud = t.vidTrud;
        this->godIzdavanje = t.godIzdavanje;
    }

    Trud &operator=(const Trud &t) {
        this->vidTrud = t.vidTrud;
        this->godIzdavanje = t.godIzdavanje;

        return *this;
    }

    friend istream &operator>>(istream &is, Trud &trud) {

        is >> trud.vidTrud >> trud.godIzdavanje;

        return is;
    }

};

class Student {

private:

    char ime[30];
    int indeks;
    int godina_upis;
    int *ocenki_polozeni;
    int br_polozeni;

public:

    int getGodinaUpis() const {
        return godina_upis;
    }

    int getIndeks() const {
        return indeks;
    }

    Student() {
        strcpy(this->ime, "Nan");
        this->indeks = 0;
        this->godina_upis = 0;
        this->ocenki_polozeni = nullptr;
        this->br_polozeni = 0;

    };

    Student(char *ime, int indeks, int godina_upis, int *ocenki_polozeni, int br_polozeni) {

        strcpy(this->ime, ime);

        this->indeks = indeks;
        this->godina_upis = godina_upis;

        this->ocenki_polozeni = new int[br_polozeni];
        for (int i = 0; i < br_polozeni; i++) {
            this->ocenki_polozeni[i] = ocenki_polozeni[i];
        }

        this->br_polozeni = br_polozeni;
    };

    Student(const Student &s) {

        strcpy(this->ime, s.ime);

        this->indeks = s.indeks;
        this->godina_upis = s.godina_upis;

        this->ocenki_polozeni = new int[s.br_polozeni];
        for (int i = 0; i < s.br_polozeni; i++) {
            this->ocenki_polozeni[i] = s.ocenki_polozeni[i];
        }

        this->br_polozeni = s.br_polozeni;
    };

    Student &operator=(const Student &s) {

        strcpy(this->ime, s.ime);

        this->indeks = s.indeks;
        this->godina_upis = s.godina_upis;

        delete[]this->ocenki_polozeni;
        this->ocenki_polozeni = new int[s.br_polozeni];
        for (int i = 0; i < s.br_polozeni; i++) {
            this->ocenki_polozeni[i] = s.ocenki_polozeni[i];
        }

        this->br_polozeni = s.br_polozeni;

        return *this;
    };

    virtual float rang() {

        float prosek;

        for (int i = 0; i < this->br_polozeni; i++) {
            prosek = prosek + (float) this->ocenki_polozeni[i];
        }
        prosek = prosek / (float) this->br_polozeni;

        return prosek;
    }

    friend ostream &operator<<(ostream &os, Student &student) {

        os << student.indeks << " " << student.ime << " " << student.godina_upis << " " << student.rang() << endl;

        return os;
    }

};

class PhDStudent : public Student {

private:
    Trud *listaTrudovi;
    int br_trudovi;

public:

    PhDStudent() : Student() {
        this->listaTrudovi = nullptr;
        this->br_trudovi = 0;
    }

    PhDStudent(char *ime, int indeks, int godina_upis, int *ocenki_polozeni, int br_polozeni, Trud *listaTrudovi,
               int br_trudovi) : Student(ime, indeks, godina_upis, ocenki_polozeni, br_polozeni) {


        for (int i = 0; i < br_trudovi; i++) {
            if (listaTrudovi[i].getGodIzdavanje() < this->getGodinaUpis()) {
                Exception().message();
                continue;
            };
        }

        this->listaTrudovi = new Trud[br_trudovi];
        for (int i = 0; i < br_trudovi; i++) {
            this->listaTrudovi[i] = listaTrudovi[i];
        }

        this->br_trudovi = br_trudovi;
    }

    PhDStudent(const PhDStudent &p) : Student(p) {

        this->listaTrudovi = new Trud[p.br_trudovi];
        for (int i = 0; i < p.br_trudovi; i++) {
            this->listaTrudovi[i] = p.listaTrudovi[i];
        }

        this->br_trudovi = p.br_trudovi;
    }

    PhDStudent &operator=(const PhDStudent &p) {

        Student::operator=(p);

        delete[]this->listaTrudovi;

        this->listaTrudovi = new Trud[p.br_trudovi];
        for (int i = 0; i < p.br_trudovi; i++) {
            this->listaTrudovi[i] = p.listaTrudovi[i];
        }

        this->br_trudovi = p.br_trudovi;

        return *this;
    }


    float rang() {

        float total = 0, poeni_od_trudovi = 0;

        for (int i = 0; i < this->br_trudovi; i++) {
            if (this->listaTrudovi[i].getVidTrud() == 'c'||this->listaTrudovi[i].getVidTrud() == 'C') {
                poeni_od_trudovi = poeni_od_trudovi + konferenciski_trud;
            } else if (this->listaTrudovi[i].getVidTrud() == 'j'||this->listaTrudovi[i].getVidTrud() == 'J') {
                poeni_od_trudovi = poeni_od_trudovi + spisanie_trud;
            };
        }

        total = Student::rang() + poeni_od_trudovi;

        return total;
    }

    PhDStudent &operator+=(const Trud &t) {

        if (t.getGodIzdavanje() < this->getGodinaUpis()) {
            throw Exception();
        }

        Trud *tmp = new Trud[this->br_trudovi + 1];

        for (int i = 0; i < this->br_trudovi; i++) {
            tmp[i] = this->listaTrudovi[i];
        }

        tmp[this->br_trudovi] = t;
        this->br_trudovi++;

        delete[] this->listaTrudovi;
        this->listaTrudovi = tmp;

        return *this;
    }

};

int main() {
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1) {
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
        for (int j = 0; j < n_tr; j++) {
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
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

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
        for (int i = 0; i < m; i++) {
            if (niza[i]->getIndeks() == indeks && dynamic_cast<PhDStudent *>(niza[i]) != nullptr) {
                dynamic_cast<PhDStudent *>(niza[i])->operator+=(t);
            }else if(niza[i]->getIndeks() == indeks && dynamic_cast<PhDStudent *>(niza[i]) == nullptr)
                cout<<"\nNe postoi PhD student so indeks "<<indeks;

        }


        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
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

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2
        for (int i = 0; i < m; i++) {
            if (niza[i]->getIndeks() == indeks && dynamic_cast<PhDStudent *>(niza[i]) != nullptr) {
                dynamic_cast<PhDStudent *>(niza[i])->operator+=(t);
            }

        }


        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;

            for (int j = 0; j < n_tr; j++) {
                cin >> tip;
                cin >> god_tr;
                Trud t(tip, god_tr);
                trud[j] = t;
            }
            PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
            cout << phd;

    }
    if (testCase == 5) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
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
        try {
            for (int i = 0; i < m; i++) {
                if (niza[i]->getIndeks() == indeks && dynamic_cast<PhDStudent *>(niza[i]) != nullptr) {
                    dynamic_cast<PhDStudent *>(niza[i])->operator+=(t);
                }
            }
        } catch (Exception &e) {
            e.message();
        }


        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6) {
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
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

        //postavete gi soodvetnite vrednosti za statickite promenlivi

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}