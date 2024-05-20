#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;

class NegativnaVrednost {
private:

public:

    void message() {
        cout << "Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!" << endl;
    }
};

class Oglas {

private:

    char naslov[50];
    char kategorija[50];
    char opis[100];
    float cena;

public:

    float getCena() const {
        return cena;
    }

    const char *getKategorija() const {
        return kategorija;
    }

    Oglas() {
        strcpy(this->naslov, "NaN");
        strcpy(this->kategorija, "NaN");
        strcpy(this->opis, "NaN");

        this->cena = 0.0;
    }

    Oglas(char *naslov, char *kategorija, char *opis, float cena) {
        strcpy(this->naslov, naslov);
        strcpy(this->kategorija, kategorija);
        strcpy(this->opis, opis);

        this->cena = cena;
    }

    Oglas(const Oglas &o) {
        strcpy(this->naslov, o.naslov);
        strcpy(this->kategorija, o.kategorija);
        strcpy(this->opis, o.opis);

        this->cena = o.cena;
    }

    Oglas &operator=(const Oglas &o) {
        strcpy(this->naslov, o.naslov);
        strcpy(this->kategorija, o.kategorija);
        strcpy(this->opis, o.opis);

        this->cena = o.cena;

        return *this;
    }

    bool operator>(const Oglas &o) {

        if (this->cena > o.cena) {
            return true;
        } else return false;
    }

    friend ostream &operator<<(ostream &os, const Oglas &oglas) {

        os << oglas.naslov << endl;
        os << oglas.opis << endl;
        os << oglas.cena << " evra" << endl;

        return os;
    }

};

class Oglasnik {

private:
    char ime[20];
    Oglas *niza_oglasi;
    int br_oglasi;

public:


    Oglasnik() {
        strcpy(this->ime, "NaN");
        this->niza_oglasi = nullptr;
        this->br_oglasi = 0;
    }

    Oglasnik(char *ime) {
        strcpy(this->ime, ime);
        this->niza_oglasi = nullptr;
        this->br_oglasi = 0;
    }


    Oglasnik(char *ime, Oglas *niza_oglasi, int br_oglasi) {

        strcpy(this->ime, ime);

        this->niza_oglasi = new Oglas[br_oglasi];
        for (int i = 0; i < br_oglasi; i++) {
            this->niza_oglasi[i] = niza_oglasi[i];
        }
        this->br_oglasi = br_oglasi;
    }

    Oglasnik(const Oglasnik &o) {

        strcpy(this->ime, o.ime);

        this->niza_oglasi = new Oglas[o.br_oglasi];
        for (int i = 0; i < o.br_oglasi; i++) {
            this->niza_oglasi[i] = o.niza_oglasi[i];
        }
        this->br_oglasi = o.br_oglasi;
    }

    ~Oglasnik() {
        delete[]this->niza_oglasi;
    }


    Oglasnik &operator=(const Oglasnik &o) {

        strcpy(this->ime, o.ime);

        delete[]this->niza_oglasi;
        this->niza_oglasi = new Oglas[o.br_oglasi];
        for (int i = 0; i < o.br_oglasi; i++) {
            this->niza_oglasi[i] = o.niza_oglasi[i];
        }
        this->br_oglasi = o.br_oglasi;

        return *this;
    }

    Oglasnik &operator+=(const Oglas &o) {

        if (o.getCena() < 0) {
            throw NegativnaVrednost();  // ako nema try/catch u main, ke mora brake da se stai pod komandava
        }

        Oglas *tmp = new Oglas[this->br_oglasi + 1];

        for (int i = 0; i < this->br_oglasi; i++) {
            tmp[i] = this->niza_oglasi[i];
        }

        tmp[this->br_oglasi] = o;
        this->br_oglasi++;

        delete[]this->niza_oglasi;
        this->niza_oglasi = tmp;

        return *this;
    }

    friend ostream &operator<<(ostream &os, const Oglasnik &oglasnik) {
        os << oglasnik.ime << endl;
        for (int i = 0; i < oglasnik.br_oglasi; i++) {
            os << oglasnik.niza_oglasi[i] << endl;
        }
        return os;
    }

    void oglasiOdKategorija(const char *k) {

        for (int i = 0; i < this->br_oglasi; i++) {

            if (strcmp(this->niza_oglasi[i].getKategorija(), k) == 0) {
                cout << this->niza_oglasi[i] << endl;
            }
        }
    }


    void najniskaCena() {

        float najniska = 1000000.0;
        int najniska_indeks = 0;

        for (int i = 0; i < this->br_oglasi; i++) {

            if (this->niza_oglasi[i].getCena() < najniska) {
                najniska = this->niza_oglasi[i].getCena();
                najniska_indeks = i;
            }
        }

        cout << this->niza_oglasi[najniska_indeks];
    }

};


int main() {

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin >> tip;

    if (tip == 1) {
        cout << "-----Test Oglas & operator <<-----" << endl;
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout << o;
    } else if (tip == 2) {
        cout << "-----Test Oglas & operator > -----" << endl;
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1 > o2) cout << "Prviot oglas e poskap." << endl;
        else cout << "Prviot oglas ne e poskap." << endl;
    } else if (tip == 3) {
        cout << "-----Test Oglasnik, operator +=, operator << -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cout << ogl;
    } else if (tip == 4) {
        cout << "-----Test oglasOdKategorija -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cin.get();
        cin.getline(k, 29);
        cout << "Oglasi od kategorijata: " << k << endl;
        ogl.oglasiOdKategorija(k);

    } else if (tip == 5) {
        cout << "-----Test Exception -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);

        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            try {
                Oglas o(naslov, kategorija, opis, cena);
                ogl += o;
            } catch (NegativnaVrednost &n) {
                n.message();
            }
        }


        cout << ogl;
    } else if (tip == 6) {
        cout << "-----Test najniskaCena -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cout << "Oglas so najniska cena:" << endl;
        ogl.najniskaCena();

    } else if (tip == 7) {
        cout << "-----Test All -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);

        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            try {
                Oglas o(naslov, kategorija, opis, cena);
                ogl += o;
            } catch (NegativnaVrednost &n) {
                n.message();
            }
        }

        cout << ogl;

        cin.get();
        cin.get();
        cin.getline(k, 29);
        cout << "Oglasi od kategorijata: " << k << endl;
        ogl.oglasiOdKategorija(k);

        cout << "Oglas so najniska cena:" << endl;
        ogl.najniskaCena();

    }

    return 0;
}
