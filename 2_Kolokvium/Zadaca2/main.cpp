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

    Vozac(char ime[100], int vozrast, int br_trki, bool isVeteran) {
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
        os << vozac.ime << vozac.vozrast << vozac.br_trki << vozac.isVeteran; // veteran ne treba da se pecati na sekoe
        return os;
    }

    virtual bool operator==(const Vozac &v) = 0;

    virtual void danok() = 0;

    virtual float zarabotuvacka() = 0;

    int getBrTrki() {
        return this->br_trki;
    }

    bool getVeteran() {
        return this->isVeteran;
    }
};


class Avtomobilist : Vozac {

private:
    float cena_na_avto;

public:
//konstuktori , operator =

// DA SE PREPOKRIE
// friend ostream &operator<<(ostream &os, const Vozac &vozac) {}

        float zarabotuvacka() {

        float zarabotil = 0.0;
        zarabotil = this->cena_na_avto / 5;

        return zarabotil;
    }

    void danok() override {
        if (getBrTrki() > 10) {
            //danok 15%
        } else {
            // danok 10%
        }

    }

};

class Motociklist : Vozac {


private:
    int mokjnost_motor;

public:
//konstuktori , operator =

// DA SE PREPOKRIE
// friend ostream &operator<<(ostream &os, const Vozac &vozac) {}


    float zarabotuvacka() {

        float zarabotil = 0.0;
        zarabotil = this->mokjnost_motor * 20;

        return zarabotil;
    }

    void danok() override {
        if (getVeteran() == true) {
            //danok 25%
        } else {
            // danok 20%
        }

    }

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