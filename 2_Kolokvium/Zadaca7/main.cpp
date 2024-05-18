#include<iostream>
#include <cstring>

using namespace std;

static const int P = 4;

class OutOfBoundException {

public:

    void message() {
        cout << "Brojot na pin kodovi ne moze da go nadmine dozvolenoto" << endl;
    }
};

class Karticka {
protected:
    char smetka[16];
    int pin;
    bool povekjePin;

public:

    Karticka() {
        strcpy(this->smetka, "null");
        this->pin = 0;
        this->povekjePin = false;
    }

    Karticka(char *smetka, int pin) {
        strcpy(this->smetka, smetka);
        this->pin = pin;
        this->povekjePin = false;
    }

    Karticka(const Karticka &k) {
        strcpy(this->smetka, k.smetka);
        this->pin = k.pin;
        this->povekjePin = k.povekjePin;
    }

    Karticka &operator=(const Karticka &k) {
        strcpy(this->smetka, k.smetka);
        this->pin = k.pin;
        this->povekjePin = k.povekjePin;

        return *this;
    }

    const char *getSmetka() const {
        return smetka;
    }

    int getPin() const {
        return pin;
    }

    void setPin(int pin) {
        Karticka::pin = pin;
    }

    bool getDopolnitelenPin() const {
        return povekjePin;
    }

    void setPovekjePin(bool povekjePin) {
        Karticka::povekjePin = povekjePin;
    }


    virtual int tezinaProbivanje() {  //kolku e podolg pinot, tolku e potezok
        int s = 0, c = pin;
        while (c) {
            s++;
            c = c / 10;
        }
        return s;
    }

    friend ostream &operator<<(ostream &os, Karticka &karticka) {
        os << karticka.smetka << ": " << karticka.tezinaProbivanje() << endl;
        return os;
    }

};


class SpecijalnaKarticka : public Karticka {

private:
    int *dopolnitelenPin;
    int num_of_pin;


public:

    SpecijalnaKarticka() : Karticka() {
        this->dopolnitelenPin = nullptr;
        this->num_of_pin = 0;
    }

    SpecijalnaKarticka(char *smetka, int pin) : Karticka(smetka, pin) {//     SpecijalnaKarticka(smetka, pin); vakov konstruktor se koristi vo main
        this->dopolnitelenPin = nullptr;
        this->num_of_pin = 0;
    }

    SpecijalnaKarticka(const SpecijalnaKarticka &s) : Karticka(s) {

        for (int i = 0; i < s.num_of_pin; i++) {
            this->dopolnitelenPin[i] = s.dopolnitelenPin[i];
        }
        this->num_of_pin = s.num_of_pin;
    }

    ~SpecijalnaKarticka() {
        delete[]dopolnitelenPin;
    }

    SpecijalnaKarticka &operator=(const SpecijalnaKarticka &s) {
        Karticka::operator=(s);

        for (int i = 0; i < s.num_of_pin; i++) {
            this->dopolnitelenPin[i] = s.dopolnitelenPin[i];
        }
        this->num_of_pin = s.num_of_pin;

        return *this;
    }

    int tezinaProbivanje() {  //kolku e podolg pinot, tolku e potezok

        int s;
        s = Karticka::tezinaProbivanje() + this->num_of_pin;

        return s;
    }

    friend ostream &operator<<(ostream &os, SpecijalnaKarticka &karticka) {
        os << karticka.smetka << ": " << karticka.tezinaProbivanje() << endl;
        return os;
    }

    SpecijalnaKarticka &operator+=(int nov_pin) {

        for (int i = 0; i < num_of_pin; i++) {
            if (this->num_of_pin == P) {
                throw OutOfBoundException();
            }
        }

        int *tmp = new int[this->num_of_pin + 1];

        for (int i = 0; i < num_of_pin; i++) {
            tmp[i] = this->dopolnitelenPin[i];
        }

        tmp[this->num_of_pin] = nov_pin;
        this->num_of_pin++;


        delete[] this->dopolnitelenPin;
        this->dopolnitelenPin = tmp;


        return *this;
    }


    int *getDopolnitelenPin() const {
        return dopolnitelenPin;
    }

    void setDopolnitelenPin(int *dopolnitelenPin) {
        SpecijalnaKarticka::dopolnitelenPin = dopolnitelenPin;
    }

    int getNumOfPin() const {
        return num_of_pin;
    }

    void setNumOfPin(int numOfPin) {
        num_of_pin = numOfPin;
    }
};

class Banka {

private:

    char naziv[30];
    Karticka *karticki[20];
    int broj;

public:
    static int LIMIT;

    Banka(char *naziv, Karticka **karticki, int broj) {
        strcpy(this->naziv, naziv);
        for (int i = 0; i < broj; i++) {
            //ako kartickata ima dopolnitelni pin kodovi
            if (karticki[i]->getDopolnitelenPin()) {
                this->karticki[i] = new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka *>(karticki[i]));
            } else this->karticki[i] = new Karticka(*karticki[i]);
        }
        this->broj = broj;
    }

    ~Banka() {
        for (int i = 0; i < broj; i++) delete karticki[i];
    }

    static void setLIMIT(int novLimit) {
        LIMIT = novLimit;
    }


    void pecatiKarticki() {
        cout << "Vo bankata " << this->naziv << " moze da se probijat kartickite:" << endl;

        for (int i = 0; i < this->broj; i++) {
            if (this->karticki[i]->tezinaProbivanje() < LIMIT) {
                cout << *this->karticki[i];
            }

        }
    }

    void dodadiDopolnitelenPin(char *smetka, int novPin) {

        SpecijalnaKarticka *tmp;

        for (int i = 0; i < this->broj; i++) {
            if ((strcmp(this->karticki[i]->getSmetka(), smetka) == 0) && (dynamic_cast<SpecijalnaKarticka *>(this->karticki[i])) != nullptr) {
                this->karticki[i]->setPovekjePin(true);
                dynamic_cast<SpecijalnaKarticka *>(this->karticki[i])->operator+=(novPin);

            }
        }
    }

};

int Banka::LIMIT = 7;

int main() {

    Karticka **niza;
    int n, m, pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin >> n;
    niza = new Karticka *[n];
    for (int i = 0; i < n; i++) {
        cin >> smetka;
        cin >> pin;
        cin >> daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i] = new Karticka(smetka, pin);
        else
            niza[i] = new SpecijalnaKarticka(smetka, pin);
    }

    Banka komercijalna("Komercijalna", niza, n);
    for (int i = 0; i < n; i++) delete niza[i];
    delete[] niza;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> smetka >> pin;
        try {
            komercijalna.dodadiDopolnitelenPin(smetka, pin);
        } catch (OutOfBoundException &e) {
            e.message();
        }
    }

    Banka::setLIMIT(5);

    komercijalna.pecatiKarticki();

}
