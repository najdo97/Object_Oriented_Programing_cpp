#include<iostream>
#include<string.h>

using namespace std;


//todo
//  StudentKursUsno mora da bide ima true vrednost vo daliUsno za sekoj objekt
//  operator+= treba da se prereshi celosno


class BadInputException {
private:
public:
    void message() {
        cout << "Greshna opisna ocenka" << endl;
    }
};

class StudentKurs {
protected:
    char ime[30];
    int ocenka;
    bool daliUsno;

    static int MAX;
    static int MINOCENKA;

public:

    const char *getIme() const {
        return ime;
    }

    static int getMinocenka() {
        return MINOCENKA;
    }

    static void setMAX(int m) {
        MAX = m;
    }


    bool getDaliUsno() const {
        return daliUsno;
    }

    ~StudentKurs() {};

    StudentKurs() {
        strcpy(this->ime, "BezImenko");
        this->ocenka = 0;
        this->daliUsno = false;
    }

    StudentKurs(char *ime, int finalenIspit) {
        strcpy(this->ime, ime);
        this->ocenka = finalenIspit;
        this->daliUsno = false;
    }

    StudentKurs(const StudentKurs &s) {
        strcpy(this->ime, s.ime);
        this->ocenka = s.ocenka;
        this->daliUsno = s.daliUsno;
    }

    StudentKurs &operator=(const StudentKurs &s) {
        strcpy(this->ime, s.ime);
        this->ocenka = s.ocenka;
        this->daliUsno = s.daliUsno;

        return *this;
    }

    friend ostream &operator<<(ostream &os, const StudentKurs &kurs) {
        os << kurs.ime << " --- " << kurs.ocenka << endl;
        return os;
    }

    virtual int getOcenka() {
        return this->ocenka;
    }

};


class StudentKursUsno : public StudentKurs {
private:
    char *opisnaOcenka; //odlicen = +2, dobro = +1, losho = -1

public:

    ~StudentKursUsno() {
        delete[] this->opisnaOcenka;
    }

    StudentKursUsno() : StudentKurs() {
        this->opisnaOcenka = nullptr;
    }

    StudentKursUsno(char *ime, int finalenIspit, char *opisnaOcenka) : StudentKurs(ime, finalenIspit) {
        this->opisnaOcenka = new char[strlen(opisnaOcenka) + 1];
        strcpy(this->opisnaOcenka, opisnaOcenka);
        this->daliUsno = true;

    }

    StudentKursUsno(char *ime, int finalenIspit) : StudentKurs(ime, finalenIspit) {
        this->opisnaOcenka = nullptr;
        this->daliUsno = true;

    }

    StudentKursUsno(const StudentKursUsno &s) : StudentKurs(s) {
        if (s.opisnaOcenka != nullptr) {
            this->opisnaOcenka = new char[strlen(s.opisnaOcenka) + 1];
            strcpy(this->opisnaOcenka, s.opisnaOcenka);
        } else {
            this->opisnaOcenka = nullptr;
            this->daliUsno = true;
        }
    }

    StudentKursUsno &operator=(const StudentKursUsno &s) {
        StudentKurs::operator=(s);

        delete[] this->opisnaOcenka;
        this->opisnaOcenka = new char[strlen(s.opisnaOcenka) + 1];
        strcpy(this->opisnaOcenka, s.opisnaOcenka);

        return *this;
    }


    StudentKursUsno &operator+=(char *novaOpisnaOcenka) {    // sekoe novo dodaovanje ke ja prebrishuva starata ocenka, nema logika da se redat u niza
        bool imaBroj = false;

        char *tmp = new char[strlen(novaOpisnaOcenka) + 1];
        int j = 0;

        for (int i = 0; i < strlen(novaOpisnaOcenka); i++) {
            if (!isalpha(novaOpisnaOcenka[i])) {
                imaBroj = true;
            }
        }
        for (int i = 0; i <= strlen(novaOpisnaOcenka); i++) {
            if (isalpha(novaOpisnaOcenka[i])) {
                tmp[j] = novaOpisnaOcenka[i];
                j++;
            }

        }
//        char *tmp2 = new char[j + 1];
//        for (int i = 0; i < j; i++) {
//            tmp2[i] = tmp[i];
//        }
//        tmp2[j] = NULL;
//
//        cout<<"Originalna: "<<novaOpisnaOcenka<<" strlen: "<<strlen(novaOpisnaOcenka)<<endl;
//
//        cout<<"Trganit broevi:"<<tmp<<" strlen: "<<strlen(tmp)<<endl;
//
//        cout<<"Trganti broevi + skratena nizata: "<<tmp2<<" strlen: "<<strlen(tmp2)<<endl;

        delete[]this->opisnaOcenka;
        this->opisnaOcenka = new char[strlen(tmp) + 1];
        strcpy(this->opisnaOcenka, tmp);

        if (strcmp(tmp, "odlicen") == 0 && (this->ocenka + 2) < MAX) {
            this->ocenka = this->ocenka + 2;
        } else if (strcmp(tmp, "dobro") == 0 && (this->ocenka + 1) < MAX) {
            this->ocenka = this->ocenka + 1;
        } else if (strcmp(tmp, "losho") == 0) {
            this->ocenka = this->ocenka - 1;
        }

        if (imaBroj == true) {
            throw BadInputException();
        }


        return *this;
    }

    friend ostream &operator<<(ostream &os, const StudentKursUsno &usno) {
        os << usno.ime << " --- " << usno.ocenka << endl;
        return os;
    }

};

class KursFakultet {
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;

public:
    KursFakultet(char *naziv, StudentKurs **studenti, int broj) {
        strcpy(this->naziv, naziv);
        for (int i = 0; i < broj; i++) {
            //ako studentot ima usno isprashuvanje
            if (studenti[i]->getDaliUsno()) {
                this->studenti[i] = new StudentKursUsno(*dynamic_cast<StudentKursUsno *>(studenti[i]));
            } else this->studenti[i] = new StudentKurs(*studenti[i]);
        }
        this->broj = broj;
    }

    ~KursFakultet() {
        for (int i = 0; i < broj; i++) delete studenti[i];
    }

    void pecatiStudenti() {

        int polozeni = 0;
        cout << "Kursot " << this->naziv << " go polozile:" << endl;

        for (int i = 0; i < this->broj; i++) {

            if (this->studenti[i]->getOcenka() > this->studenti[i]->getMinocenka()) {       // neznam kako poinaku da pristapam do static promenlivava
                polozeni++;
            }
        }

        for (int i = 0; i < this->broj; i++) {

            //  cout << this->studenti[i]->getIme() <<" ima ocenka: " <<this->studenti[i]->getOcenka() <<"" <<endl;

            if (this->studenti[i]->getOcenka() >= this->studenti[i]->getMinocenka()) {       // neznam kako poinaku da pristapam do static promenlivava
                cout << this->studenti[i]->getIme() << " --- " << this->studenti[i]->getOcenka() << endl;
            }
        }
    }

    void postaviOpisnaOcenka(char *ime, char *opisnaOcenka) {

        for (int i = 0; i < broj; i++) {

            if (strcmp(this->studenti[i]->getIme(), ime) == 0 && this->studenti[i]->getDaliUsno() == true) {
                dynamic_cast<StudentKursUsno *>(this->studenti[i])->operator+=(opisnaOcenka);
            }
        }

    }

};

int StudentKurs::MAX = 10;
int StudentKurs::MINOCENKA = 6;

int main() {

    StudentKurs **niza;
    int n, m, ocenka;
    char ime[30], opisna[10];
    bool daliUsno;
    cin >> n;
    niza = new StudentKurs *[n];
    for (int i = 0; i < n; i++) {
        cin >> ime;
        cin >> ocenka;
        cin >> daliUsno;
        if (!daliUsno)
            niza[i] = new StudentKurs(ime, ocenka);
        else
            niza[i] = new StudentKursUsno(ime, ocenka);
    }

    KursFakultet programiranje("OOP", niza, n);
    for (int i = 0; i < n; i++) delete niza[i];
    delete[] niza;
    cin >> m;

    for (int i = 0; i < m; i++) {
        cin >> ime >> opisna;
        try {
            programiranje.postaviOpisnaOcenka(ime, opisna);
        } catch (BadInputException &b) {
            b.message();
        }
    }

    StudentKurs::setMAX(9);

    programiranje.pecatiStudenti();

}
