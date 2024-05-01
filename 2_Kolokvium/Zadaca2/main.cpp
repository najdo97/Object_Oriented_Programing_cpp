#include <iostream>
#include <cstring>

using namespace std;

class Vozac {
private:
    char ime[100];
    int vozrast;
    int br_trki;
    bool isVeteran;

public:
    Vozac() {
        strcpy(this->ime, "NAN");
        this->vozrast = 0;
        this->br_trki = 0;
        this->isVeteran = false;
    };

    Vozac(char *ime, int vozrast, int br_trki, bool isVeteran) {
        strcpy(this->ime, ime);
        this->vozrast = vozrast;
        this->br_trki = br_trki;
        this->isVeteran = isVeteran;
    };

    Vozac(const Vozac &v) {
        strcpy(this->ime, v.ime);
        this->vozrast = v.vozrast;
        this->br_trki = v.br_trki;
        this->isVeteran = v.isVeteran;
    };

    Vozac &operator=(const Vozac &v) {

        strcpy(this->ime, v.ime);
        this->vozrast = v.vozrast;
        this->br_trki = v.br_trki;
        this->isVeteran = v.isVeteran;

        return *this;
    };

    friend ostream &operator<<(ostream &os, const Vozac &vozac) {
        os << vozac.ime <<'\n'
        << vozac.vozrast <<'\n'
        << vozac.br_trki <<'\n'
        << vozac.isVeteran; // veteran ne treba da se pecati na sekoe
        return os;
    }

    bool operator==(const Vozac &v) {
        return false; //neznam sho drugo da staam
    };

    virtual float danok() const = 0;

    virtual float zarabotuvacka() const = 0;

    int getBrTrki() const {
        return this->br_trki;
    }

    bool getVeteran() const {
        return this->isVeteran;
    }
};


class Avtomobilist : public Vozac {

private:
    float cena_na_avto;

public:

    Avtomobilist() : Vozac() {
        this->cena_na_avto = 0.0;
    }

    Avtomobilist(char *ime, int vozrast, int br_trki, bool isVeteran, float cena_na_avto) : Vozac(ime, vozrast, br_trki,
                                                                                                  isVeteran) {
        this->cena_na_avto = cena_na_avto;
    }

    Avtomobilist(const Avtomobilist &a) : Vozac(a) {

        this->cena_na_avto = a.cena_na_avto;
    }

    Avtomobilist &operator=(const Avtomobilist &a) {
        Vozac::operator=(a);
        this->cena_na_avto = a.cena_na_avto;
        return *this;
    }


// friend ostream &operator<<(ostream &os, const Vozac &vozac) {}

    bool operator==(const Vozac &v) {

        return this->zarabotuvacka() == v.zarabotuvacka();

    };


    float zarabotuvacka() const override {

        float zarabotil = 0.0;
        zarabotil = this->cena_na_avto / 5;

        return zarabotil;
    }

    float danok() const override {

        if (getBrTrki() > 10) {
            return 15;
        } else {
            return 10;
        }

    }

};

class Motociklist : public Vozac {
private:
    int mokjnost_motor;

public:

    Motociklist() : Vozac() {
        this->mokjnost_motor = 0;
    }

    Motociklist(char *ime, int vozrast, int br_trki, bool isVeteran, int mokjnost_motor) : Vozac(ime, vozrast, br_trki,
                                                                                                 isVeteran) {
        this->mokjnost_motor = mokjnost_motor;
    }

    Motociklist(const Motociklist &m) : Vozac(m) {
        this->mokjnost_motor = 0;
    }

    Motociklist &operator=(const Motociklist &m) {

        Vozac::operator=(m);
        this->mokjnost_motor = m.mokjnost_motor;

        return *this;
    }


// friend ostream &operator<<(ostream &os, const Vozac &vozac) {}


    bool operator==(const Motociklist &v) {
        return this->zarabotuvacka() == v.zarabotuvacka();
    };


    float zarabotuvacka() const override {

        float zarabotil = 0.0;
        zarabotil = this->mokjnost_motor * 20;

        return zarabotil;
    }

    float danok() const override {
        if (this->getVeteran() == true) {
            return 25;
        } else {
            return 20;
        }

    }

};

int soIstaZarabotuvachka(Vozac **niza, int brojac, Vozac *sporeduvan_vozac) {
    int ista_zarabotka_brojac = 0;

    for (int i = 0; i < brojac; i++) {
        if (niza[i]->zarabotuvacka() == sporeduvan_vozac->zarabotuvacka()) {
            ista_zarabotka_brojac++;
        }
    }

    return ista_zarabotka_brojac;

};

int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac *[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for (int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if (i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for (int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete[] v;
    delete vx;
    return 0;
}