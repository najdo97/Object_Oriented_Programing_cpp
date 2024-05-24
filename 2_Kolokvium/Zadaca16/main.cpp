#include <iostream>
#include <cstring>

using namespace std;

class Transport {

private:
    char *destinacija;
    int osnovna_cena;
    int rastojanie;

public:

    char *getDestinacija() const {
        return destinacija;
    }

    int getOsnovnaCena() const {
        return osnovna_cena;
    }

    int getRastojanie() const {
        return rastojanie;
    }

    Transport() {
        this->destinacija = nullptr;
        this->osnovna_cena = 0;
        this->rastojanie = 0;
    }

    Transport(char *destinacija, int osnovna_cena, int rastojanie) {

        this->destinacija = new char[strlen(destinacija) + 1];
        strcpy(this->destinacija, destinacija);

        this->osnovna_cena = osnovna_cena;
        this->rastojanie = rastojanie;
    }

    Transport(const Transport &t) {

        this->destinacija = new char[strlen(t.destinacija) + 1]; //if t.destinacija is initilized as nullptr, it will give an error
        strcpy(this->destinacija, t.destinacija);

        this->osnovna_cena = t.osnovna_cena;
        this->rastojanie = t.rastojanie;
    }

    Transport &operator=(const Transport &t) {

        delete this->destinacija;
        this->destinacija = new char[strlen(t.destinacija) + 1]; //if t.destinacija is initilized as nullptr, it will give an error
        strcpy(this->destinacija, t.destinacija);

        this->osnovna_cena = t.osnovna_cena;
        this->rastojanie = t.rastojanie;

        return *this;
    }

    ~Transport() {
        delete this->destinacija;
    }

    virtual float cenaTransport() = 0;

    bool operator<(Transport &t) {


        if (this->rastojanie < t.rastojanie) {
            return true;
        } else return false;
    }

};


class AvtomobilTransport : public Transport {

private:

    bool isPlatenSofer;

public:
    AvtomobilTransport() : Transport() {
        this->isPlatenSofer = false;      // mozno e da treba da e true
    }

    AvtomobilTransport(char *destinacija, int osnovna_cena, int rastojanie, bool isPlatenSofer) : Transport(destinacija, osnovna_cena, rastojanie) {
        this->isPlatenSofer = isPlatenSofer;
    }

    AvtomobilTransport(const AvtomobilTransport &a) : Transport(a) {

        this->isPlatenSofer = a.isPlatenSofer;
    }

    ~AvtomobilTransport() {};

    AvtomobilTransport &operator=(const AvtomobilTransport &a) {

        Transport::operator=(a);
        this->isPlatenSofer = a.isPlatenSofer;

        return *this;
    }

    float cenaTransport() {
        float nova_cena = this->getOsnovnaCena();

        if (this->isPlatenSofer == true) {

            nova_cena = nova_cena + (this->getOsnovnaCena() * 0.2);
        }
        return nova_cena;
    }


};

class KombeTransport : public Transport {

private:
    int kapacitet;

public:
    KombeTransport() : Transport() {
        this->kapacitet = 0;
    }

    KombeTransport(char *destinacija, int osnovna_cena, int rastojanie, int kapacitet) : Transport(destinacija, osnovna_cena, rastojanie) {
        this->kapacitet = kapacitet;
    }

    KombeTransport(const KombeTransport &k) : Transport(k) {
        this->kapacitet = k.kapacitet;
    }

    ~KombeTransport() {}

    KombeTransport &operator=(const KombeTransport &k) {
        Transport::operator=(k);

        this->kapacitet = k.kapacitet;
        return *this;
    }

    float cenaTransport() {
        float nova_cena = this->getOsnovnaCena();

        nova_cena = nova_cena - (this->kapacitet * 200);

        return nova_cena;
    }

};

void pecatiPoloshiPonudi(Transport **ponudi, int n, AvtomobilTransport benchmark) {

    Transport *tmp;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            // j mora sekad da e pogolemo od i vo ovoj algoritam, vo sprotivno ako j=0, j=1  ili bilo koja druga vrednost, pri izminuvanjeto na nizata
            // ke se navrakjame na clenovi koi vekje se podredenbi spored baranjeto
            if (ponudi[i]->getRastojanie() > ponudi[j]->getRastojanie()) {
                tmp = ponudi[i];
                ponudi[i] = ponudi[j];
                ponudi[j] = tmp;

            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (benchmark.cenaTransport() < ponudi[i]->cenaTransport()) {
            cout << ponudi[i]->getDestinacija() << " " << ponudi[i]->getRastojanie() << " " << ponudi[i]->cenaTransport() << " " << endl;
        }
    }
}

int main() {

    char destinacija[20];
    int tip, cena, rastojanie, lugje;
    bool shofer;
    int n;
    cin >> n;
    Transport **ponudi;
    ponudi = new Transport *[n];

    for (int i = 0; i < n; i++) {

        cin >> tip >> destinacija >> cena >> rastojanie;
        if (tip == 1) {
            cin >> shofer;
            ponudi[i] = new AvtomobilTransport(destinacija, cena, rastojanie, shofer);

        } else {
            cin >> lugje;
            ponudi[i] = new KombeTransport(destinacija, cena, rastojanie, lugje);
        }


    }

    AvtomobilTransport nov("Ohrid", 2000, 600, false);
    pecatiPoloshiPonudi(ponudi, n, nov);

    for (int i = 0; i < n; i++) delete ponudi[i];
    delete[] ponudi;
    return 0;
}
