#include <iostream>
#include <cstring>

using namespace std;

class Gitara {

private:
    char tip[40];
    char seriski_broj[25];
    int godina_proizvodstvo;
    float nabavna_cena;

public:
    Gitara() {

        this->godina_proizvodstvo = 0;
        this->nabavna_cena = 0;
    };     // so ovoj konstruktor se kreira objekt, mozno e da treba da se inicijaliziraat promenlivite

    Gitara(char *tip, char *seriski_broj, int godina_proizvodstvo, float nabavna_cena) {
        strcpy(this->tip, tip);
        strcpy(this->seriski_broj, seriski_broj);

        this->godina_proizvodstvo = godina_proizvodstvo;
        this->nabavna_cena = nabavna_cena;
    };

    //copy constructor
    Gitara(const Gitara &gitara_copy) {
        strcpy(this->tip, gitara_copy.tip);
        strcpy(this->seriski_broj, gitara_copy.seriski_broj);

        this->godina_proizvodstvo = gitara_copy.godina_proizvodstvo;
        this->nabavna_cena = gitara_copy.nabavna_cena;
    };


    ~Gitara() {};


    const char *getTip() {
        return this->tip;
    }

    const char *getSeriski() {
        return this->seriski_broj;
    }

    const int getGodina() {
        return this->godina_proizvodstvo;
    }

    const float getNabavna() {
        return this->nabavna_cena;
    }


    bool daliIsti(Gitara pom) {
        if (strcmp(this->seriski_broj, pom.getSeriski()) == 0)        // this should work
        {
            return true;
        } else return false;
    }

    void pecati() {
        cout << this->seriski_broj << " " << this->tip << " " << this->nabavna_cena
             << endl;        // mozno e tuka da ima greshka
    }

};


class Magacin {

private:
    char ime[30];
    char lokacija[30];
    Gitara *gitari_na_lager;
    int broj_na_gitari;
    int godina_otvaranje;

public:

    Magacin() {
        strcpy(this->ime, "NaN");
        strcpy(this->lokacija, "NaN");

        this->broj_na_gitari = 0;
        this->gitari_na_lager = nullptr;
        this->godina_otvaranje = 0;

    };

    Magacin(char *ime, char *lokacija) {

        strcpy(this->ime, ime);
        strcpy(this->lokacija, lokacija);

        this->broj_na_gitari = 0;
        this->gitari_na_lager = nullptr;
        this->godina_otvaranje = 0;

    };

    Magacin(char *ime, char *lokacija, int godina_otvaranje) {

        strcpy(this->ime, ime);
        strcpy(this->lokacija, lokacija);
        this->godina_otvaranje = godina_otvaranje;

        this->broj_na_gitari = 0;
        this->gitari_na_lager = nullptr;


    };

    Magacin(const Magacin &m) {

        strcpy(this->ime, m.ime);
        strcpy(this->lokacija, m.lokacija);
        this->godina_otvaranje = m.godina_otvaranje;

        this->broj_na_gitari = m.broj_na_gitari;

        this->gitari_na_lager=new Gitara[m.broj_na_gitari];
        for (int i = 0; i < m.broj_na_gitari; i++) {
            this->gitari_na_lager[i] = m.gitari_na_lager[i];
        }
    };

    ~Magacin() {

        // cout<<"vlegov"<<endl;
        delete[]this->gitari_na_lager;
        // cout<<"izlegov"<<endl;

    };

    void dodadi(Gitara d) {


        if (this->gitari_na_lager != nullptr) {
            Gitara *pom = new Gitara[this->broj_na_gitari + 1];


            for (int i = 0; i < this->broj_na_gitari; i++) {
                pom[i] = Gitara(this->gitari_na_lager[i]);
            }

            pom[this->broj_na_gitari] = Gitara(d);
            this->broj_na_gitari++;

            delete[] this->gitari_na_lager;

            this->gitari_na_lager = pom;

/*            this->gitari_na_lager = new Gitara[this->broj_na_gitari];

            for (int i = 0; i < this->broj_na_gitari; i++) {
                this->gitari_na_lager[i] = Gitara(pom[i]);
            }
            delete[] pom;
*/
        } else if (this->gitari_na_lager == nullptr) {
            this->broj_na_gitari++;
            this->gitari_na_lager = new Gitara[this->broj_na_gitari];
            this->gitari_na_lager[0] = Gitara(d);

        }


    }


    void prodadi(Gitara p) { //test case 4 ima nekakov problem so fukncijava, novata niza
        Gitara *pom = new Gitara[this->broj_na_gitari];
        int azuriran_broj_gitari = 0;

        for (int i = 0; i < this->broj_na_gitari; i++) {
            if (strcmp(this->gitari_na_lager[i].getSeriski(), p.getSeriski()) != 0) {
                pom[azuriran_broj_gitari] = Gitara(this->gitari_na_lager[i]);
                azuriran_broj_gitari++;
            }
        }
        delete[] this->gitari_na_lager;

        this->gitari_na_lager = pom;
        this->broj_na_gitari = azuriran_broj_gitari;

        /*
         this->gitari_na_lager = new Gitara[azuriran_broj_gitari];

        for (int i = 0; i < azuriran_broj_gitari; i++) {
            this->gitari_na_lager[i] = Gitara(pom[i]);
        }


        delete[] pom;
    */
    }

    void pecati(bool daliNovi) {

        cout << this->ime << " " << this->lokacija << endl;

        if (daliNovi == true) {
            for (int i = 0; i < this->broj_na_gitari; i++) {

                if (this->godina_otvaranje < this->gitari_na_lager[i].getGodina()) {
                    this->gitari_na_lager[i].pecati();
                }
            }
        } else if (daliNovi == false) {
            for (int i = 0; i < this->broj_na_gitari; i++) {
                    this->gitari_na_lager[i].pecati();
            }
        }

    }

    Magacin &operator=(const Magacin &m) {
        strcpy(this->ime, m.ime);
        strcpy(this->lokacija, m.lokacija);
        this->godina_otvaranje = m.godina_otvaranje;

        this->broj_na_gitari = m.broj_na_gitari;

        this->gitari_na_lager=new Gitara[m.broj_na_gitari];
        for (int i = 0; i < m.broj_na_gitari; i++) {
            this->gitari_na_lager[i] = m.gitari_na_lager[i];
        }

        return *this;
    }

    double vrednost() {
        double vkupna_vrednost = 0;

        for (int i = 0; i < this->broj_na_gitari; i++) {
            vkupna_vrednost = vkupna_vrednost + this->gitari_na_lager[i].getNabavna();
        }
        return vkupna_vrednost;
    }


};


int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, godina;
    float cena;
    char seriski[50], tip[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasata Gitara ======" << endl;
        cin >> tip;
        cin >> seriski;
        cin >> godina;
        cin >> cena;
        Gitara g(tip, seriski, godina, cena);
        cout << g.getTip() << endl;
        cout << g.getSeriski() << endl;
        cout << g.getGodina() << endl;
        cout << g.getNabavna() << endl;
    } else if (testCase == 2) {
        cout << "===== Testiranje na klasata Magacin so metodot print() ======" << endl;
        Magacin kb("Magacin1", "Lokacija1");
        kb.pecati(false);
    } else if (testCase == 3) {
        cout << "===== Testiranje na klasata Magacin so metodot dodadi() ======" << endl;
        Magacin kb("Magacin1", "Lokacija1", 2005);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> tip;
            cin >> seriski;
            cin >> godina;
            cin >> cena;
            Gitara g(tip, seriski, godina, cena);
            cout << "gitara dodadi" << endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
    } else if (testCase == 4) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() ======" << endl;
        Magacin kb("Magacin1", "Lokacija1", 2012);
        cin >> n;
        Gitara brisi;
        for (int i = 0; i < n; i++) {
            cin >> tip;
            cin >> seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip, seriski, godina, cena);
            if (i == 2)
                brisi = g;
            cout << "gitara dodadi" << endl;
            kb.dodadi(g);
        }
        kb.pecati(false);
        kb.prodadi(brisi);
        kb.pecati(false);
    } else if (testCase == 5) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() i pecati(true) ======" << endl;
        Magacin kb("Magacin1", "Lokacija1", 2011);
        cin >> n;
        Gitara brisi;
        for (int i = 0; i < n; i++) {
            cin >> tip;
            cin >> seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip, seriski, godina, cena);
            if (i == 2)
                brisi = g;
            cout << "gitara dodadi" << endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
        kb.prodadi(brisi);
        cout << "Po brisenje:" << endl;
        Magacin kb3;
        kb3 = kb;
        kb3.pecati(true);
    } else if (testCase == 6) {
        cout << "===== Testiranje na klasata Magacin so metodot vrednost()======" << endl;
        Magacin kb("Magacin1", "Lokacija1", 2011);
        cin >> n;
        Gitara brisi;
        for (int i = 0; i < n; i++) {
            cin >> tip;
            cin >> seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip, seriski, godina, cena);
            if (i == 2)
                brisi = g;
            kb.dodadi(g);
        }
        cout << kb.vrednost() << endl;
        kb.prodadi(brisi);
        cout << "Po brisenje:" << endl;
        cout << kb.vrednost();
        Magacin kb3;
        kb3 = kb;
    }
    return 0;
}
