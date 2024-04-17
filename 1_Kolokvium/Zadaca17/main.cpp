/*
 *  Vo zadacata ima baranje da se napishe funkcijata dodadi() vo klasata Repozitorium,
 *  so koja ke dodademe nov operativen sistem vo repozitoriumot.
 *
 *  Kodot vo zadacata e napishan spored baranjata, no vo primerite najverojatno ima greshka.
 *  Vo prvite 2 primera se vnesuvaat 2 Operativni sistema od ista familija, a toa ne treba da go dozvoluva funkcijata dodadi().
 *  Spored baranjata, ako se najdat 2 operativni sistemi od ista familija (ime i tip), togash treba da se zavuca ponoviot.
 *  Vo prvite 2 primera se zacuvuvaat 2 Operativni sitemi od ist tip.
 */


#include <iostream>
#include<cstring>

using namespace std;
enum Tip {
    LINUX, UNIX, WINDOWS
};

class OperativenSistem {

private:
    char *ime_OS;
    float verzija;
    Tip tip;
    float golemina;


public:

    float getVerzija() const {
        return this->verzija;
    }

    OperativenSistem() {
        this->ime_OS = nullptr;
        this->verzija = 0.0;
        this->tip = Tip(0);
        this->golemina = 0.0;
    };

    OperativenSistem(char *ime_OS, float verzija, Tip tip, float golemina) {

        this->ime_OS = new char[strlen(ime_OS) + 1];
        strcpy(this->ime_OS, ime_OS);

        this->verzija = verzija;
        this->tip = tip;
        this->golemina = golemina;
    };

    OperativenSistem(const OperativenSistem &o) {
        this->ime_OS = new char[strlen(o.ime_OS) + 1];
        strcpy(this->ime_OS, o.ime_OS);

        this->verzija = o.verzija;
        this->tip = o.tip;
        this->golemina = o.golemina;
    };

    ~OperativenSistem() {
        delete[]this->ime_OS;
    };

    OperativenSistem &operator=(const OperativenSistem &o) {

        delete[]this->ime_OS;
        this->ime_OS = new char[strlen(o.ime_OS) + 1];
        strcpy(this->ime_OS, o.ime_OS);

        this->verzija = o.verzija;
        this->tip = o.tip;
        this->golemina = o.golemina;

        return *this;
    };

    void pecati() {
        cout << "Ime: " << this->ime_OS << " Verzija: " << this->verzija << " Tip: " << this->tip << " Golemina:"
             << this->golemina << "GB" << endl;
    }

    //  два оперативни системи се еднакви ако имаат исто име, верзија, тип и големина
    bool ednakviSe(const OperativenSistem &os) {
        if ((strcmp(this->ime_OS, os.ime_OS) == 0) &&
            (this->verzija == os.verzija) &&
            (this->tip == os.tip) &&
            (this->golemina == os.golemina)) {
            return true;
        } else return false;
    }

    // кој ќе враќа 0 доколку верзиите се исти, -1 доколку верзијата на оперативниот систем од аргументот е поголема и 1 во преостанатиот случај
    int sporediVerzija(const OperativenSistem &os) {
        if (this->verzija == os.verzija) {
            return 0;
        } else if (this->verzija < os.verzija) {
            return -1;
        } else return 1;
    }

//    Два оперативни системи се од иста фамилија доколку имаат исто име и се од ист тип
    bool istaFamilija(const OperativenSistem &sporedba) {

        if ((strcmp(this->ime_OS, sporedba.ime_OS) == 0) && (this->tip == sporedba.tip)) {
            return true;
        } else return false;
    }
};


class Repozitorium {
private:
    char ime[20];
    OperativenSistem *niza_OS;
    int br_OS;

public:

    Repozitorium() {
        strcpy(this->ime, "NaN");
        this->niza_OS = nullptr;
        this->br_OS = 0;
    }

    Repozitorium(const char *ime) {
        strcpy(this->ime, ime);

        this->niza_OS = nullptr;
        this->br_OS = 0;
    }

    Repozitorium(const Repozitorium &r) {
        strcpy(this->ime, r.ime);

        this->niza_OS = new OperativenSistem[r.br_OS];
        for (int i = 0; i < r.br_OS; i++) {
            this->niza_OS[i] = r.niza_OS[i];
        }

        this->br_OS = r.br_OS;
    }

    ~Repozitorium() {
        delete[]       this->niza_OS;
    }


    Repozitorium &operator=(const Repozitorium &r) {
        strcpy(this->ime, r.ime);

        if (this->niza_OS != nullptr) {
            delete[]this->niza_OS;
        }

        if (r.niza_OS != nullptr) {
            this->niza_OS = new OperativenSistem[r.br_OS];
            for (int i = 0; i < r.br_OS; i++) {
                this->niza_OS[i] = r.niza_OS[i];
            }
        } else {
            this->niza_OS = nullptr;
        }

        this->br_OS = r.br_OS;

        return *this;
    }

    void pecatiOperativniSistemi() {

        cout << "Repozitorium: " << this->ime << endl;

        for (int i = 0; i < this->br_OS; i++) {
            this->niza_OS[i].pecati();
        }
    }

    //кој ќе го избрише оперативниот систем проследен како аргумент, доколку тој се наоѓа во репозиториумот. Да се користи методот ednakviSe за споредба на два оперативни система.
    void izbrishi(const OperativenSistem &operativenSistem) {

        OperativenSistem *pom = new OperativenSistem[this->br_OS];

        int brojac = 0;
        for (int i = 0; i < this->br_OS; i++) {
            if (!this->niza_OS[i].ednakviSe(operativenSistem)) {
                pom[i] = this->niza_OS[i];
            } else brojac++;
        }
        if (brojac != 0) {

            this->br_OS = this->br_OS - brojac;
            delete[]this->niza_OS;
            this->niza_OS = new OperativenSistem[this->br_OS];

            for (int i = 0; i < this->br_OS; i++) {
                this->niza_OS[i] = pom[i];
            }
            delete[]pom;

        } else delete[]pom;
    }

//  Доколку веќе постои оперативен систем од иста фамилија (да се користи методот за проверка на фамилија)
//  кој е постар од проследениот оперативен систем, тогаш постоечкиот оперативен систем се заменува со новиот.

//  Во секој друг случај, проследениот оперативен систем се додава како дополнителен во репозиториумот.

    void dodadi(const OperativenSistem &nov) {

        int j = 0, duplikat_pozicija = 0;

        for (int i = 0; i < this->br_OS; i++) {
            if (this->niza_OS[i].istaFamilija(nov)) {
                j++;
                duplikat_pozicija = i;
            }
        }

        if (j != 0) {
            if (this->niza_OS[duplikat_pozicija].getVerzija() < nov.getVerzija()) {     // tuka moze da se iskoristi sporediVerzija()
                this->niza_OS[duplikat_pozicija] = nov;
            }
        } else {

            OperativenSistem *pom = new OperativenSistem[this->br_OS + 1];

            for (int i = 0; i < this->br_OS; i++) {
                pom[i] = this->niza_OS[i];
            }

            pom[this->br_OS] = nov;
            this->br_OS++;

            delete[]this->niza_OS;

            this->niza_OS = pom;

        }

    }


};

int main() {
    char repoName[20];
    cin >> repoName;
    Repozitorium repozitorium = Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin >> brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i < brojOperativniSistemi; i++) {
        cin >> ime;
        cin >> verzija;
        cin >> tip;
        cin >> golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip) tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
    cin >> ime;
    cin >> verzija;
    cin >> tip;
    cin >> golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip) tip, golemina);
    cout << "=====Brishenje na operativen sistem=====" << endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}