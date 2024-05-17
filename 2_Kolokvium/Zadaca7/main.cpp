#include<iostream>
#include <cstring>

using namespace std;

static const int P = 4;

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

    bool isPovekjePin() const {
        return povekjePin;
    }

    void setPovekjePin(bool povekjePin) {
        Karticka::povekjePin = povekjePin;
    }

    //todo - kako se presmetuva tezinata?

    virtual void tezinaProbivanje() {

    }

    //todo - treba i tezinata na probivanje da se odcita
    friend ostream &operator<<(ostream &os, const Karticka &karticka) {
        os << karticka.smetka;

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


};


class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
public:
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

    //да се дополни класата

};


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

        komercijalna.dodadiDopolnitelenPin(smetka, pin);

    }

    Banka::setLIMIT(5);

    komercijalna.pecatiKarticki();

}
