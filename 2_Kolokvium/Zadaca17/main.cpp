#include <iostream>
#include <cstring>

using namespace std;

class FudbalskaEkipa {

protected:
    char trener[100];
    int dadeni_golovi[10];

public:

    const char *getTrener() const {
        return trener;
    }

    FudbalskaEkipa() {
        strcpy(this->trener, "NaN");
        for (int i = 0; i < 10; i++) {
            this->dadeni_golovi[i] = 0;
        }
    }

    FudbalskaEkipa(char *trener, int *dadeni_golovi) {
        strcpy(this->trener, trener);
        for (int i = 0; i < 10; i++) {
            this->dadeni_golovi[i] = dadeni_golovi[i];
        }
    }

    FudbalskaEkipa(const FudbalskaEkipa &f) {
        strcpy(this->trener, f.trener);
        for (int i = 0; i < 10; i++) {
            this->dadeni_golovi[i] = f.dadeni_golovi[i];
        }
    }

    FudbalskaEkipa &operator=(const FudbalskaEkipa &f) {
        strcpy(this->trener, f.trener);
        for (int i = 0; i < 10; i++) {
            this->dadeni_golovi[i] = f.dadeni_golovi[i];
        }
        return *this;
    }

    virtual int uspeh() = 0;

    FudbalskaEkipa &operator+=(const int dadeni_golovi) {

        int tmp[10];

        for (int i = 1, j = 0; i < 10; i++, j++) {
            tmp[j] = this->dadeni_golovi[i];
        }
        tmp[9] = dadeni_golovi;

        for (int i = 0; i < 10; i++) {
            this->dadeni_golovi[i] = tmp[i];
        }

        return *this;
    }


};


class Klub : public FudbalskaEkipa {

private:
    char *ime_klub;
    int br_tituli;
public:

    char *getImeKlub() const {
        return ime_klub;
    }

    Klub() : FudbalskaEkipa() {
        this->ime_klub = nullptr;
        this->br_tituli = 0;
    }

    Klub(char *trener, int *dadeni_golovi, char *ime_klub, int br_tituli) : FudbalskaEkipa(trener, dadeni_golovi) {

        this->ime_klub = new char[strlen(ime_klub) + 1];
        strcpy(this->ime_klub, ime_klub);

        this->br_tituli = br_tituli;
    }

    Klub(const Klub &k) : FudbalskaEkipa(k) {

        this->ime_klub = new char[strlen(k.ime_klub) + 1];
        strcpy(this->ime_klub, k.ime_klub);

        this->br_tituli = k.br_tituli;
    }

    Klub &operator=(const Klub &k) {

        FudbalskaEkipa::operator=(k);

        delete this->ime_klub;
        this->ime_klub = new char[strlen(k.ime_klub) + 1];
        strcpy(this->ime_klub, k.ime_klub);

        this->br_tituli = k.br_tituli;

        return *this;
    }

    int uspeh() {
        int vkupno_golovi = 0;
        int total_uspeh = 0;
        for (int i = 0; i < 10; i++) {
            vkupno_golovi = vkupno_golovi + this->dadeni_golovi[i];
        }
        total_uspeh = (vkupno_golovi * 3) + (this->br_tituli * 1000);

        return total_uspeh;
    }


};

class Reprezentacija : public FudbalskaEkipa {

private:
    char *ime_drzava;
    int nastapi;

public:

    Reprezentacija() : FudbalskaEkipa() {
        this->ime_drzava = nullptr;
        this->nastapi = 0;
    }

    Reprezentacija(char *trener, int *dadeni_golovi, char *ime_drzava, int nastapi) : FudbalskaEkipa(trener, dadeni_golovi) {

        this->ime_drzava = new char[strlen(ime_drzava) + 1];
        strcpy(this->ime_drzava, ime_drzava);

        this->nastapi = nastapi;

    }

    Reprezentacija(const Reprezentacija &r) : FudbalskaEkipa(r) {

        this->ime_drzava = new char[strlen(r.ime_drzava) + 1];
        strcpy(this->ime_drzava, r.ime_drzava);

        this->nastapi = r.nastapi;
    }

    Reprezentacija &operator=(const Reprezentacija &r) {

        FudbalskaEkipa::operator=(r);

        delete this->ime_drzava;
        this->ime_drzava = new char[strlen(r.ime_drzava) + 1];
        strcpy(this->ime_drzava, r.ime_drzava);

        this->nastapi = r.nastapi;

        return *this;
    }

    char *getImeRep() {
        return this->ime_drzava;
    }

    int uspeh() {
        int vkupno_golovi = 0;
        int total_uspeh = 0;
        for (int i = 0; i < 10; i++) {
            vkupno_golovi = vkupno_golovi + this->dadeni_golovi[i];
        }
        total_uspeh = vkupno_golovi * 3 + this->nastapi * 50;

        return total_uspeh;
    }


};


ostream &operator<<(ostream &os, FudbalskaEkipa &klub) {

    if (dynamic_cast<Klub *>(&klub) != nullptr) {
        os << dynamic_cast<Klub *>(&klub)->getImeKlub() << "\n" << klub.getTrener() << "\n" << dynamic_cast<Klub *>(&klub)->uspeh() << endl;
    }
    if (dynamic_cast<Reprezentacija *>(&klub) != nullptr) {
        os << dynamic_cast<Reprezentacija *>(&klub)->getImeRep() << "\n" << klub.getTrener() << "\n" << dynamic_cast<Reprezentacija *>(&klub)->uspeh() << endl;
    }


    return os;
}

void najdobarTrener(FudbalskaEkipa **timovi, int n) {

    int naj_uspesen = timovi[0]->uspeh(), brojac = 0;
    for (int i = 1; i < n; i++) {
        if (naj_uspesen < timovi[i]->uspeh()) {
            naj_uspesen = timovi[i]->uspeh();
            brojac = i;
        }
    }
    cout << (*timovi[brojac]) << endl;
}


int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa *[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete[] ekipi;
    return 0;
}