#include <iostream>
#include <cstring>

using namespace std;


class Ucesnik {

private:
    char *ime;
    bool pol;
    int vozrast;

public:

    Ucesnik() {
       // this->ime = nullptr;
    };

    Ucesnik(char *ime, bool pol, int vozrast) {

        this->ime = new char[strlen(ime)];
        strcpy(this->ime, ime);

        this->pol = pol;
        this->vozrast = vozrast;
    }

    Ucesnik(const Ucesnik &u) {

        this->ime = new char[strlen(u.ime)];
        strcpy(this->ime, u.ime);

        this->pol = u.pol;
        this->vozrast = u.vozrast;
    };

    ~Ucesnik() {

        delete[] ime;
    };

    bool operator>(const Ucesnik &d) {      // neznam koe treba da e pogolemo, koe pomalo

        if (this->vozrast > d.vozrast) {
            return true;
        } else return false;
    }

    friend ostream &operator<<(ostream &output, const Ucesnik &u) {
        output << u.ime << " " << u.pol << " " << u.vozrast << " " << endl;
        return output;
    };

    int getVozrast() {
        return this->vozrast;
    }

};

class Maraton {

private:
    char lokacija[100];
    Ucesnik *ucesnici;
    int br_ucesnici;
public:

    Maraton() {
        this->ucesnici = nullptr;
        this->br_ucesnici = 0;
    };

    Maraton(char *lokacija) {
        strcpy(this->lokacija, lokacija);

        this->ucesnici = nullptr;
        this->br_ucesnici = 0;
    };

    Maraton(char *lokacija, Ucesnik *ucesnici, int br_ucesnici) {
        strcpy(this->lokacija, lokacija);

        this->ucesnici = new Ucesnik[br_ucesnici];
        for (int i = 0; i < br_ucesnici; i++) {
            this->ucesnici[i] = Ucesnik(ucesnici[i]);
        }

        this->br_ucesnici = br_ucesnici;
    };


    Maraton(const Maraton &m) {
        strcpy(this->lokacija, m.lokacija);

        this->ucesnici = new Ucesnik[m.br_ucesnici];
        for (int i = 0; i < m.br_ucesnici; i++) {
            this->ucesnici[i] = Ucesnik(m.ucesnici[i]);
        }
        this->br_ucesnici = m.br_ucesnici;
    };


    ~Maraton() {
        delete[] ucesnici;
    };

    Maraton &operator+=(const Ucesnik &u) {         // ne sum siguren deka return typeot e validen i toa sho se ocekuva

        Ucesnik *pom = new Ucesnik[this->br_ucesnici + 1];

        for (int i = 0; i < this->br_ucesnici; i++) {
            pom[i] = Ucesnik(this->ucesnici[i]);
        }
        this->br_ucesnici++;
        pom[this->br_ucesnici] = Ucesnik(u);

        delete[]this->ucesnici;

        this->ucesnici = pom;

        return *this;
    }

    float prosecnoVozrast() {
        float prosecna = 0.0, zbir_vozrast = 0.0;
        for (int i = 0; i < this->br_ucesnici; i++) {
            zbir_vozrast = zbir_vozrast + this->ucesnici[i].getVozrast();
        }
        prosecna = zbir_vozrast / (float) this->br_ucesnici;

        return prosecna;
    }

    void pecatiPomladi(Ucesnik &u){

        for (int i = 0; i < this->br_ucesnici; i++) {
         if(u.getVozrast()>this->ucesnici[i].getVozrast())  // moze da se iskoristi  overloadnatiot > operator
         {
             cout << this->ucesnici[i];
         }
        }
    }


};


int main() {
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);
    Ucesnik **u = new Ucesnik *[n];
    for (int i = 0; i < n; ++i) {
        cin >> ime >> maski >> vozrast;
        u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
    m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for (int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete[] u;
    return 0;
}