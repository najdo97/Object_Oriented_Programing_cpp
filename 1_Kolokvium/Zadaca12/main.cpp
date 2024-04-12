#include <iostream>
#include <cstring>

using namespace std;

class Pica {
private:
    char ime[15];
    int cena;
    char *sostojki;
    int namaluvanje_procent;


public:
    void setCena(int cena) {
        this->cena = cena;
    }

    void setSostojki(char *sostojki) {
        Pica::sostojki = sostojki;
    }

    void setNamaluvanjeProcent(int namaluvanjeProcent) {
        namaluvanje_procent = namaluvanjeProcent;
    }

    void setIme(char *ime) {
        strcpy(this->ime, ime);
    }

    const char *getIme() const {
        return ime;
    }

    int getCena() const {
        return cena;
    }

    char *getSostojki() const {
        return sostojki;
    }

    int getNamaluvanjeProcent() const {
        return namaluvanje_procent;
    }

    Pica() {
        strcpy(this->ime, "NaN");
        this->cena = 0;
        this->sostojki = nullptr;
        this->namaluvanje_procent = 0;
    };

    Pica(char *ime, int cena, char *sostojki, int namaluvanjeProcent) {

        strcpy(this->ime, ime);
        this->cena = cena;

        this->sostojki = new char[strlen(sostojki) + 1];
        strcpy(this->sostojki, sostojki);

        this->namaluvanje_procent = namaluvanjeProcent;
    }


    Pica(const Pica &p) {

        strcpy(this->ime, p.ime);
        this->cena = p.cena;

        delete[]this->sostojki;
        this->sostojki = new char[strlen(p.sostojki) + 1];
        strcpy(this->sostojki, p.sostojki);

        this->namaluvanje_procent = p.namaluvanje_procent;
    };

    ~Pica() {
        delete[]this->sostojki;
    };

    void pecati() {
        cout << this->ime << " - " << this->sostojki << ", " << this->cena << " ";

    }

    bool istiSe(Pica p) {
        if (strcmp(this->sostojki, p.getSostojki()) == 0) {
            return true;
        } else return false;
    }

    Pica &operator=(const Pica &p) {

        strcpy(this->ime, p.ime);
        this->cena = p.cena;

        delete[]this->sostojki;
        this->sostojki = new char[strlen(p.sostojki) + 1];
        strcpy(this->sostojki, p.sostojki);

        this->namaluvanje_procent = p.namaluvanje_procent;

        return *this;
    }



};

class Picerija {

private:

    char ime[15];
    Pica *lista_pici;
    int br_pici;

public:

    void setListaPici(Pica *listaPici) {
        this->lista_pici = listaPici;
    }

    void setBrPici(int brPici) {
        this->br_pici = brPici;
    }

    void setIme(char *ime) {
        strcpy(this->ime, ime);
    }

    const char *getIme() const {
        return this->ime;
    }

    Pica *getListaPici() const {
        return this->lista_pici;
    }

    int getBrPici() const {
        return this->br_pici;
    }

    Picerija() {
        strcpy(this->ime, "NaN");
        this->lista_pici = nullptr;
        this->br_pici = 0;

    }

    Picerija(char *ime) {
        strcpy(this->ime, ime);
        this->lista_pici = nullptr;
        this->br_pici = 0;

    }

    Picerija(char *ime, Pica *listaPici, int brPici) {
        strcpy(this->ime, ime);


        this->lista_pici = new Pica[brPici];
        for (int i = 0; i < brPici; i++) {
            this->lista_pici[i] = listaPici[i];
        }
        this->br_pici = brPici;

    }


    Picerija(const Picerija &p) {
        strcpy(this->ime, p.ime);

        //delete[]this->lista_pici;

        /*
            Copy constuctor se povikuva samo koga se asajnuva vrednost na SHTOTUKU inicijalizirana promenliva,
            nemoze da brishesh neshto shto ne ni bilo rezervirano. Sekoja naredna situacija koa se asajnuva od eden objekt na drug,
            ke se koristi overload-natiot operator=, vo nego se koristi delete[] !
        */

        this->lista_pici = new Pica[p.br_pici];
        for (int i = 0; i < p.br_pici; i++) {
            this->lista_pici[i] = p.lista_pici[i];
        }

        this->br_pici = p.br_pici;
    };

    ~Picerija() {
        delete[] lista_pici;
    };


    Picerija &operator=(const Picerija &p) {
        strcpy(this->ime, p.ime);

        delete[]this->lista_pici;

        this->lista_pici = new Pica[p.br_pici];
        for (int i = 0; i < p.br_pici; i++) {
            this->lista_pici[i] = p.lista_pici[i];
        }
        this->br_pici = p.br_pici;

        return *this;
    };

    Picerija &operator+=(const Pica &p) {
        bool pica_postoi;

        for (int i = 0; i < this->br_pici; i++) {

            if (strcmp(this->lista_pici[i].getSostojki(), p.getSostojki()) == 0) {
                pica_postoi = true;
                break;
            }
        }

        if (pica_postoi == false) {
            Pica *pom = new Pica[this->br_pici + 1];

            for (int i = 0; i < this->br_pici; i++) {
                pom[i] = this->lista_pici[i];
            }
            pom[this->br_pici] = p;
            this->br_pici++;

            delete[]this->lista_pici;

            this->lista_pici = pom;

        }
        return *this;
    };

    void dodadi(Pica p) {

        bool pica_postoi;

        for (int i = 0; i < this->br_pici; i++) {

            if (strcmp(this->lista_pici[i].getSostojki(), p.getSostojki()) == 0) {
                pica_postoi = true;
                break;
            }
        }


        if (pica_postoi == false) {
            Pica *pom = new Pica[this->br_pici + 1];

            for (int i = 0; i < this->br_pici; i++) {
                pom[i] = this->lista_pici[i];
            }
            pom[this->br_pici] = p;
            this->br_pici++;

            delete[]this->lista_pici;

            this->lista_pici = pom;
        } else return;

    };


    void piciNaPromocija() {

        int cena_so_popust = 0;

        for (int i = 0; i < this->br_pici; i++) {
            if (this->lista_pici[i].getNamaluvanjeProcent() != 0) {
                this->lista_pici[i].pecati();
                cena_so_popust = this->lista_pici[i].getCena() -
                                 (this->lista_pici[i].getCena() * this->lista_pici[i].getNamaluvanjeProcent() / 100);

                cout << cena_so_popust << endl;

            }
        }
    };



};


int main() {

    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for (int i = 0; i < n; i++) {
        char imp[100];
        cin.get();
        cin.getline(imp, 100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki, 100);
        int popust;
        cin >> popust;
        Pica p(imp, cena, sostojki, popust);
        p1 += p;
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp, 100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki, 100);
    int popust;
    cin >> popust;
    Pica p(imp, cena, sostojki, popust);
    p2 += p;

    cout << p1.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p1.piciNaPromocija();

    cout << p2.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p2.piciNaPromocija();

    return 0;
}
