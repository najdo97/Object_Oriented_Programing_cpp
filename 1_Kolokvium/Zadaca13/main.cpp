#include<iostream>
#include<cstring>

#include<string.h>

using namespace std;

class Zichara {

private:
    char *mesto;
    int cena;

public:
    Zichara() {
        this->mesto = nullptr;
        this->cena = 0;
    };

    Zichara(char *mesto, int cena) {
        this->mesto = new char[strlen(mesto) + 1];
        strcpy(this->mesto, mesto);

        this->cena = cena;
    };

    Zichara(const Zichara &z) {
        this->mesto = new char[strlen(z.mesto) + 1];
        strcpy(this->mesto, z.mesto);

        this->cena = z.cena;
    };

    ~Zichara() {
        delete[]this->mesto;
    };

    int getCena() {
        return this->cena;
    }

    Zichara &operator=(const Zichara &z) {

        delete[]this->mesto;

        this->mesto = new char[strlen(z.mesto) + 1];
        strcpy(this->mesto, z.mesto);

        this->cena = z.cena;
        return *this;
    };
};

class PlaninarskiDom {

private:
    char ime[15];
    int sezonska_cena[2];
    char klasa_na_dom;
    bool imaZichara;
    Zichara *zichara;

public:
    PlaninarskiDom() {

        strcpy(this->ime, "NaN");

        this->sezonska_cena[0] = 0;  // leto
        this->sezonska_cena[1] = 0;  // zimo

        this->klasa_na_dom = 'F';
        this->imaZichara = false;

        this->zichara = nullptr;
    };

    PlaninarskiDom(char *ime, int *sezonska_cena, char klasa) {
        strcpy(this->ime, ime);

        this->sezonska_cena[0] = sezonska_cena[0];  // leto
        this->sezonska_cena[1] = sezonska_cena[1];  // zimo
        this->klasa_na_dom = klasa;

        this->imaZichara = false;       // za ovie treba set metoda
        this->zichara = nullptr;        // za ovie treba set metoda

    };

    PlaninarskiDom(const PlaninarskiDom &p) {
        strcpy(this->ime, p.ime);

        this->sezonska_cena[0] = p.sezonska_cena[0];  // leto
        this->sezonska_cena[1] = p.sezonska_cena[1];  // zimo
        this->klasa_na_dom = p.klasa_na_dom;
        this->imaZichara = p.imaZichara;

        this->zichara = p.zichara;       //   I vaka da e napishano, bi trebalo da raboti     this->zichara[0] = p.zichara[0];

    };

    ~PlaninarskiDom() {
        delete[] this->zichara;
    };

    void setZichara(Zichara z) {
        this->imaZichara = true;
        this->zichara = &z;
    };

    /// OVERLOAD OPERATOR = ZA OVAA KLASA !!!!!



    friend ostream &operator<<(ostream &os, const PlaninarskiDom &dom) {

        if (dom.imaZichara) {
            os << dom.ime << " klasa:" << dom.klasa_na_dom << " so zichara" << endl;
        } else os << dom.ime << " klasa:" << dom.klasa_na_dom << endl;

        return os;
    }

    PlaninarskiDom &operator--() {

        if (this->klasa_na_dom < 'F') {
            this->klasa_na_dom++;
        }
        return *this;
    }

    const bool &operator<=(char z) {

        if (this->klasa_na_dom >= z) {
            return true;
        } else return false;
    };


    void presmetajDnevenPrestoj(int den, int mesec, int cena) {

        cena = 0;
        if (this->imaZichara) {
            cena = cena + this->zichara->getCena();
        }

        if (mesec < 1 || mesec > 12 || den < 1 || den > 31) {
            throw -1;
        }

            cena =cena+ (mesec >= 4 && mesec <= 8) || mesec == 9 && den == 1 ? sezonska_cena[0] : sezonska_cena[1];


    };
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
