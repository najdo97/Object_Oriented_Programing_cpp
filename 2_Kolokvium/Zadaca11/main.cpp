#include<iostream>
#include<string.h>

using namespace std;


class Delo {

private:

    char ime[50];
    int godina;
    char zemja[50];

public:
    const char *getIme() const {
        return ime;
    }

    int getGodina() const {
        return godina;
    }

    const char *getZemja() const {
        return zemja;
    }

    Delo() {
        strcpy(this->ime, "NaN");
        this->godina = 0;
        strcpy(this->zemja, "NaN");
    }

    Delo(char *ime, int godina, char *zemja) {
        strcpy(this->ime, ime);
        this->godina = godina;
        strcpy(this->zemja, zemja);
    }

    Delo(const Delo &d) {
        strcpy(this->ime, d.ime);
        this->godina = d.godina;
        strcpy(this->zemja, d.zemja);
    }

    Delo &operator=(const Delo &d) {
        strcpy(this->ime, d.ime);
        this->godina = d.godina;
        strcpy(this->zemja, d.zemja);

        return *this;
    }

    bool operator==(const Delo &d) {
        if (strcmp(this->ime, d.ime) == 0) {
            return true;
        } else return false;
    }

};

class Pretstava {

private:
    Delo igrano_delo;
    int prodadeni_karti;
    char datum[15];

public:

    Delo getDelo() {
        return this->igrano_delo;
    }

    Pretstava() {
        this->igrano_delo = Delo();
        this->prodadeni_karti = 0;
        strcpy(this->datum, "NaN");
    }

    Pretstava(Delo igrano_delo, int prodadeni_karti, char *datum) {
        this->igrano_delo = igrano_delo;
        this->prodadeni_karti = prodadeni_karti;
        strcpy(this->datum, datum);
    }

    Pretstava(const Pretstava &p) {
        this->igrano_delo = p.igrano_delo;
        this->prodadeni_karti = p.prodadeni_karti;
        strcpy(this->datum, p.datum);
    }

    Pretstava &operator=(const Pretstava &p) {
        this->igrano_delo = p.igrano_delo;
        this->prodadeni_karti = p.prodadeni_karti;
        strcpy(this->datum, p.datum);

        return *this;
    }

    virtual int cena() {

        int M = 0, N = 0, cena = 0;

        if (this->igrano_delo.getGodina() > 1900) {
            M = 50;   //21 i 20 vek
        } else if (this->igrano_delo.getGodina() > 1800) {
            M = 75; //19 vek
        } else if (this->igrano_delo.getGodina() > 1700) {
            M = 100;    //18 vek
        }

        if (strcmp(this->igrano_delo.getZemja(), "Italija") == 0) {
            N = 100;
        } else if (strcmp(this->igrano_delo.getZemja(), "Rusija") == 0) {
            N = 150;
        } else N = 80;


        cena = M + N;

        return cena;
    }

};

class Balet : public Pretstava {

private:
    static int dopolnitelna_cena;

public:
    Balet() : Pretstava() {}

    Balet(Delo igrano_delo, int prodadeni_karti, char *datum) : Pretstava(igrano_delo, prodadeni_karti, datum) {}

    Balet(const Balet &b) : Pretstava(b) {}

    Balet &operator=(const Balet &b) {
        Pretstava::operator=(b);

        return *this;
    }

    void static setCenaBalet(int c) {
        dopolnitelna_cena = c;
    }

    int cena() {
        int nova_cena = 0;

        nova_cena = Pretstava::cena() + dopolnitelna_cena;

        return nova_cena;
    }


};


class Opera : public Pretstava {
private:

public:
    Opera() : Pretstava() {}

    Opera(Delo igrano_delo, int prodadeni_karti, char *datum) : Pretstava(igrano_delo, prodadeni_karti, datum) {}

    Opera(const Opera &b) : Pretstava(b) {}

    Opera &operator=(const Opera &b) {
        Pretstava::operator=(b);

        return *this;
    }

};


int prihod(Pretstava **pretstavi, int n) {

    int vkupen_prihod = 0;
    for (int i = 0; i < n; i++) {

        if (dynamic_cast<Balet *>(pretstavi[i]) != nullptr) {
            vkupen_prihod = vkupen_prihod + dynamic_cast<Balet *>(pretstavi[i])->cena();
        } else {
            vkupen_prihod = vkupen_prihod + pretstavi[i]->cena();
        }
    }

    return vkupen_prihod;
}

int brojPretstaviNaDelo(Pretstava **pretstavi, int n, Delo delo) {

    int kolku = 0;

    for (int i = 0; i < n; i++) {
        if (pretstavi[i]->getDelo() == delo) {
            kolku++;
        }
    }
    return kolku;
}


//citanje na delo
Delo readDelo() {
    char ime[50];
    int godina;
    char zemja[50];
    cin >> ime >> godina >> zemja;
    return Delo(ime, godina, zemja);
}

//citanje na pretstava
Pretstava *readPretstava() {
    int tip; //0 za Balet , 1 za Opera
    cin >> tip;
    Delo d = readDelo();
    int brojProdadeni;
    char data[15];
    cin >> brojProdadeni >> data;
    if (tip == 0) return new Balet(d, brojProdadeni, data);
    else return new Opera(d, brojProdadeni, data);
}

int Balet::dopolnitelna_cena = 150;

int main() {
    int test_case;
    cin >> test_case;

    switch (test_case) {
        case 1:
            //Testiranje na klasite Opera i Balet
        {
            cout << "======TEST CASE 1=======" << endl;
            Pretstava *p1 = readPretstava();
            cout << p1->getDelo().getIme() << endl;
            Pretstava *p2 = readPretstava();
            cout << p2->getDelo().getIme() << endl;
        }
            break;

        case 2:
            //Testiranje na  klasite Opera i Balet so cena
        {
            cout << "======TEST CASE 2=======" << endl;
            Pretstava *p1 = readPretstava();
            cout << p1->cena() << endl;
            Pretstava *p2 = readPretstava();
            cout << p2->cena() << endl;
        }
            break;

        case 3:
            //Testiranje na operator ==
        {
            cout << "======TEST CASE 3=======" << endl;
            Delo f1 = readDelo();
            Delo f2 = readDelo();
            Delo f3 = readDelo();

            if (f1 == f2) cout << "Isti se" << endl; else cout << "Ne se isti" << endl;
            if (f1 == f3) cout << "Isti se" << endl; else cout << "Ne se isti" << endl;

        }
            break;

        case 4:
            //testiranje na funkcijata prihod
        {
            cout << "======TEST CASE 4=======" << endl;
            int n;
            cin >> n;
            Pretstava **pole = new Pretstava *[n];
            for (int i = 0; i < n; i++) {
                pole[i] = readPretstava();

            }
            cout << prihod(pole, n);
        }
            break;

        case 5:
            //testiranje na prihod so izmena na cena za 3d proekcii
        {
            cout << "======TEST CASE 5=======" << endl;
            int cenaBalet;
            cin >> cenaBalet;
            Balet::setCenaBalet(cenaBalet);
            int n;
            cin >> n;
            Pretstava **pole = new Pretstava *[n];
            for (int i = 0; i < n; i++) {
                pole[i] = readPretstava();
            }
            cout << prihod(pole, n);
        }
            break;

        case 6:
            //testiranje na brojPretstaviNaDelo
        {
            cout << "======TEST CASE 6=======" << endl;
            int n;
            cin >> n;
            Pretstava **pole = new Pretstava *[n];
            for (int i = 0; i < n; i++) {
                pole[i] = readPretstava();
            }

            Delo f = readDelo();
            cout << brojPretstaviNaDelo(pole, n, f);
        }
            break;

    };


    return 0;
}
