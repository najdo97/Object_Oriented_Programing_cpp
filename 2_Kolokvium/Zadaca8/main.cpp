#include <iostream>
#include <cstring>

using namespace std;

class Koncert {
private:
    char naziv[20];
    char lokacija[20];
    static float sezonski_popust;
    double denari_cena;


public:

    const char *getNaziv() const {
        return naziv;
    }

    float static getSezonskiPopust() {
        return sezonski_popust;
    }

    static void setSezonskiPopust(float p) {
        sezonski_popust = p;
    }

    Koncert() {
        strcpy(this->naziv, "NaN");
        strcpy(this->lokacija, "NaN");
        this->denari_cena = 0.0;
    }

    Koncert(char *naziv, char *lokacija, double denari_cena) {
        strcpy(this->naziv, naziv);
        strcpy(this->lokacija, lokacija);
        this->denari_cena = denari_cena;
    }

    Koncert(const Koncert &k) {
        strcpy(this->naziv, k.naziv);
        strcpy(this->lokacija, k.lokacija);
        this->denari_cena = k.denari_cena;
    }

    Koncert &operator=(const Koncert &k) {
        strcpy(this->naziv, k.naziv);
        strcpy(this->lokacija, k.lokacija);
        this->denari_cena = k.denari_cena;

        return *this;
    };


    virtual double cena() {
        double nova_cena = 0.0;
        nova_cena = this->denari_cena - (this->denari_cena * sezonski_popust);
        return nova_cena;
    }

};

class ElektronskiKoncert : public Koncert {

private:
    char *imeDJ;
    float vremetraenje;
    bool vidZabava;

public:

    float getSezonskiPopust() {
        return Koncert::getSezonskiPopust();
    }

    static void setSezonskiPopust(float p) {
        Koncert::setSezonskiPopust(p);
    }

    ElektronskiKoncert() : Koncert() {

        this->imeDJ = nullptr;
        this->vremetraenje = 0.0;
        this->vidZabava = true;
    }

    ElektronskiKoncert(char *naziv, char *lokacija, double denari_cena, char *imeDJ, float vremetraenje, bool vidZabava) : Koncert(naziv, lokacija, denari_cena) {

        this->imeDJ = new char[strlen(imeDJ) + 1];
        strcpy(this->imeDJ, imeDJ);

        this->vremetraenje = vremetraenje;
        this->vidZabava = vidZabava;
    }

    ElektronskiKoncert(const ElektronskiKoncert &e) : Koncert(e) {

        this->imeDJ = new char[strlen(e.imeDJ) + 1];
        strcpy(this->imeDJ, e.imeDJ);

        this->vremetraenje = e.vremetraenje;
        this->vidZabava = e.vidZabava;
    }

    ElektronskiKoncert &operator=(const ElektronskiKoncert &e) {

        Koncert::operator=(e);

        delete[] this->imeDJ;
        this->imeDJ = new char[strlen(e.imeDJ) + 1];
        strcpy(this->imeDJ, e.imeDJ);

        this->vremetraenje = e.vremetraenje;
        this->vidZabava = e.vidZabava;

        return *this;
    }

    ~ElektronskiKoncert() {
        delete[] this->imeDJ;
    }

    double cena() {

        double nova_cena = 0.0;

        if (this->vremetraenje <= 5.0) {
            nova_cena = Koncert::cena();
        } else if (this->vremetraenje > 5.0 && this->vremetraenje <= 7) {
            nova_cena = Koncert::cena() + 150;
        } else if (this->vremetraenje > 7.0) {
            nova_cena = Koncert::cena() + 360;
        }

        if (this->vidZabava == true) {
            nova_cena = nova_cena - 50;
        } else {
            nova_cena = nova_cena + 100;
        }

        return nova_cena;
    }

};

float Koncert::sezonski_popust = 0.2;

void najskapKoncert(Koncert **koncerti, int n) {

    int elektronski = 0, najskap_index;
    double najskap = 0.0;

    for (int i = 0; i < n; i++) {
        if (dynamic_cast<ElektronskiKoncert *>(koncerti[i]) != nullptr) {
            elektronski++;
            if (najskap < dynamic_cast<ElektronskiKoncert *>(koncerti[i])->cena()) {
                najskap = dynamic_cast<ElektronskiKoncert *>(koncerti[i])->cena();
                najskap_index = i;
            }
        } else {
            if (najskap < koncerti[i]->cena()) {
                najskap = koncerti[i]->cena();
                najskap_index = i;
            }
        }
    }

    cout << "Najskap koncert: " << koncerti[najskap_index]->getNaziv() << " " << najskap << endl;
    cout << "Elektronski koncerti: " << elektronski << " od vkupno " << n << endl;

}

bool prebarajKoncert(Koncert **koncerti, int n, char *naziv, bool elektronski) {


    if (elektronski == true) {
        for (int i = 0; i < n; i++) {
            if (dynamic_cast<ElektronskiKoncert *>(koncerti[i]) != nullptr) {
                if (strcmp(naziv, dynamic_cast<ElektronskiKoncert *>(koncerti[i])->getNaziv()) == 0) {
                    cout << dynamic_cast<ElektronskiKoncert *>(koncerti[i])->getNaziv() << " " << dynamic_cast<ElektronskiKoncert *>(koncerti[i])->cena() << endl;
                    return true;
                }
            }
        }

    } else {
        for (int i = 0; i < n; i++) {
            if (dynamic_cast<ElektronskiKoncert *>(koncerti[i]) != nullptr) {
                if (strcmp(naziv, dynamic_cast<ElektronskiKoncert *>(koncerti[i])->getNaziv()) == 0) {
                    cout << dynamic_cast<ElektronskiKoncert *>(koncerti[i])->getNaziv() << " " << dynamic_cast<ElektronskiKoncert *>(koncerti[i])->cena() << endl;
                    return true;
                }
            } else {
                if (strcmp(naziv, koncerti[i]->getNaziv()) == 0) {
                    cout << koncerti[i]->getNaziv() << " " << koncerti[i]->cena() << endl;
                    return true;
                }
            }

        }
    }
    return false;
}

int main() {

    int tip, n, novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

    cin >> tip;
    if (tip == 1) {//Koncert
        cin >> naziv >> lokacija >> cenaBilet;
        Koncert k1(naziv, lokacija, cenaBilet);
        cout << "Kreiran e koncert so naziv: " << k1.getNaziv() << endl;
    } else if (tip == 2) {//cena - Koncert
        cin >> naziv >> lokacija >> cenaBilet;
        Koncert k1(naziv, lokacija, cenaBilet);
        cout << "Osnovna cena na koncertot so naziv " << k1.getNaziv() << " e: " << k1.cena() << endl;
    } else if (tip == 3) {//ElektronskiKoncert
        cin >> naziv >> lokacija >> cenaBilet >> imeDJ >> casovi >> dnevna;
        ElektronskiKoncert s(naziv, lokacija, cenaBilet, imeDJ, casovi, dnevna);
        cout << "Kreiran e elektronski koncert so naziv " << s.getNaziv() << " i sezonskiPopust " << s.getSezonskiPopust() << endl;
    } else if (tip == 4) {//cena - ElektronskiKoncert
        cin >> naziv >> lokacija >> cenaBilet >> imeDJ >> casovi >> dnevna;
        ElektronskiKoncert s(naziv, lokacija, cenaBilet, imeDJ, casovi, dnevna);
        cout << "Cenata na elektronskiot koncert so naziv " << s.getNaziv() << " e: " << s.cena() << endl;
    } else if (tip == 5) {//najskapKoncert

    } else if (tip == 6) {//prebarajKoncert
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso", "Mykonos", 8800, "Guetta", 3, true);
        char naziv[100];
        najskapKoncert(koncerti, 5);
    } else if (tip == 7) {//prebaraj
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso", "Mykonos", 8800, "Guetta", 3, true);
        char naziv[100];
        bool elektronski;
        cin >> elektronski;
        if (prebarajKoncert(koncerti, 5, "Area", elektronski))
            cout << "Pronajden" << endl;
        else cout << "Ne e pronajden" << endl;

        if (prebarajKoncert(koncerti, 5, "Area", !elektronski))
            cout << "Pronajden" << endl;
        else cout << "Ne e pronajden" << endl;

    } else if (tip == 8) {//smeni cena
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[2]->setSezonskiPopust(0.9);
        najskapKoncert(koncerti, 4);
    }

    return 0;
}