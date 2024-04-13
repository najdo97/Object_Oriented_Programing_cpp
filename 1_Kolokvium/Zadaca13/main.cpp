#include<iostream>
#include<cstring>

#include<string.h>


using namespace std;

class Zichara {
private:
    char *mesto;
    int cena;

public:
    char *getMesto() const {
        return this->mesto;
    }

    void setMesto(char *mesto) {
        this->mesto = mesto;
    }

    int getCena() const {
        return this->cena;
    }

    void setCena(int cena) {
        this->cena = cena;
    }


    Zichara() {
        strcpy(this->mesto, "nan");
        this->cena = 0;
    }

    Zichara(char *mesto, int cena) {
        this->mesto = new char[strlen(mesto) + 1];
        strcpy(this->mesto, mesto);

        this->cena = cena;
    }

    Zichara(const Zichara &z) {
        this->mesto = new char[strlen(z.mesto) + 1];
        strcpy(this->mesto, z.mesto);

        this->cena = z.cena;
    }

    virtual ~Zichara() {
        delete[]mesto;
    }

    Zichara &operator=(const Zichara &z) {
        delete[]this->mesto;

        this->mesto = new char[strlen(z.mesto) + 1];
        strcpy(this->mesto, z.mesto);

        this->cena = z.cena;

        return *this;
    }


};

class PlaninarskiDom {

private:
    char ime[15];
    int cena_sezona[2]; //0-Letna cena ; 1-Zimska cena
    char kvalitet;      // ova moze i so enum da e izvede
    bool zicara;
    Zichara *planinskiDom_zicara;

public:
    void setIme(char *Ime) {
        strcpy(this->ime, ime);
    }

    void setCena_Sezona(int *cena_sezona) {
        for (int i = 0; i < 2; i++) {
            this->cena_sezona[i] = cena_sezona[i];
        }
    }

    void setKvalitet(char kvalitet) {
        this->kvalitet = kvalitet;
    }

    void setZichara(Zichara z) {

        this->planinskiDom_zicara[0] = z;
        this->zicara = true;
    }

    void setPlaninskiDom_zicara(Zichara *planinskiDomZicara) {
        this->planinskiDom_zicara = planinskiDomZicara;
    }

    const char *getIme() const {
        return this->ime;
    }

    const int *getCenaSezona() const {
        return this->cena_sezona;
    }

    char getKvalitet() const {
        return this->kvalitet;
    }

    bool isZicara() const {
        return this->zicara;
    }

    Zichara *getPlaninskiDomZicara() const {
        return planinskiDom_zicara;
    }

    PlaninarskiDom() {

        strcpy(this->ime, "nan");
        for (int i = 0; i < 2; i++) {
            this->cena_sezona[i] = 0;
        }
        this->kvalitet = 'n';
        this->zicara = false;
        this->planinskiDom_zicara = nullptr;
    }

    PlaninarskiDom(char *ime, int *cenaSezona, char kvalitet) {
        strcpy(this->ime, ime);
        for (int i = 0; i < 2; i++) {
            this->cena_sezona[i] = cenaSezona[i];
        }
        this->kvalitet = kvalitet;

        this->zicara = false;
        this->planinskiDom_zicara = nullptr;
    }

    PlaninarskiDom(char *ime, int *cenaSezona, char kvalitet, bool zicara, Zichara planinskiDomZicara) {
        strcpy(this->ime, ime);
        for (int i = 0; i < 2; i++) {
            this->cena_sezona[i] = cenaSezona[i];
        }
        this->kvalitet = kvalitet;
        this->zicara = zicara;

        this->planinskiDom_zicara = new Zichara[1];
        this->planinskiDom_zicara[0] = planinskiDomZicara;
    }


    PlaninarskiDom(const PlaninarskiDom &p) {
        strcpy(this->ime, p.ime);
        for (int i = 0; i < 2; i++) {
            this->cena_sezona[i] = p.cena_sezona[i];
        }
        this->kvalitet = p.kvalitet;
        this->zicara = p.zicara;


        this->planinskiDom_zicara = new Zichara[1];
        this->planinskiDom_zicara[0] = p.planinskiDom_zicara[0];

    }

    ~PlaninarskiDom() {

        delete[] this->planinskiDom_zicara;
    }

    PlaninarskiDom &operator=(const PlaninarskiDom &p) {

        strcpy(this->ime, p.ime);
        for (int i = 0; i < 2; i++) {
            this->cena_sezona[i] = p.cena_sezona[i];
        }
        this->kvalitet = p.kvalitet;
        this->zicara = p.zicara;

        delete[] this->planinskiDom_zicara;

        this->planinskiDom_zicara = new Zichara[1];
        this->planinskiDom_zicara[0] = p.planinskiDom_zicara[0];

        return *this;
    };


    friend ostream &operator<<(ostream &os, const PlaninarskiDom &dom) {
        if (dom.zicara == true) {
            os << dom.ime << " klasa:" << dom.kvalitet << " so zichara" << endl;
        } else os << dom.ime << " klasa:" << dom.kvalitet << endl;


        return os;
    }

    bool operator<=(const char c) const {

        if (this->kvalitet >= c) {
            return false;
        } else return true;
    }

    PlaninarskiDom &operator--() {

        if (this->kvalitet < 'F') {
            this->kvalitet--;
        }

        return *this;
    }

    void presmetajDnevenPrestoj(int den, int mesec, int dneven_prestoj_cena) {

        if ((den > 31 || den < 1) || (mesec > 12 || mesec < 1)) {
            return;
        }
        if(this->zicara==true)
        {

        }

    }

};


int main() {

    PlaninarskiDom p; //креирање на нов објект од класата планинарски дом

    //во следниот дел се вчитуваат информации за планинарскиот дом
    char imePlaninarskiDom[15], mestoZichara[30], klasa;
    int ceni[12];
    int dnevnakartaZichara;
    bool daliZichara;
    cin >> imePlaninarskiDom;
    for (int i = 0; i < 2; i++) cin >> ceni[i];
    cin >> klasa;
    cin >> daliZichara;

    //во следниот дел се внесуваат информации и за жичарата ако постои
    if (daliZichara) {
        cin >> mestoZichara >> dnevnakartaZichara;
        PlaninarskiDom pom(imePlaninarskiDom, ceni, klasa);
        Zichara r(mestoZichara, dnevnakartaZichara);
        pom.setZichara(r);
        p = pom;
    } else {
        PlaninarskiDom *pok = new PlaninarskiDom(imePlaninarskiDom, ceni, klasa);
        p = *pok;
    }

    //се намалува класата на планинарскиот дом за 2
    --p;
    --p;

    int cena;
    int den, mesec;
    cin >> den >> mesec;
    try {
        p.presmetajDnevenPrestoj(den, mesec, cena); //тука се користи функцијата presmetajDnevenPrestoj
        cout << "Informacii za PlaninarskiDomot:" << endl;
        cout << p;
        if (p <= 'D')
            cout << "Planinarskiot dom za koj se vneseni informaciite ima klasa poniska ili ista so D\n";

        cout << "Cenata za " << den << "." << mesec << " e " << cena; //се печати цената за дадениот ден и месец
    }
    catch (int) {
        cout << "Mesecot ili denot e greshno vnesen!";
    }
}
