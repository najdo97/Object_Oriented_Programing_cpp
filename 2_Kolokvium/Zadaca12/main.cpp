#include <iostream>
#include <cstring>

using namespace std;


enum tip {
    smartfon, kompjuter
};

class InvalidProductionDate {
private:

public:
    void message() {
        cout << "Невалидна година на производство" << endl;
    }
};

class Device {

private:
    char model[100];
    tip tip_ured;
    static double proverka;
    int god_poizvodstvo;

public:

    int getGodPoizvodstvo() const {
        return god_poizvodstvo;
    }

    static void setPocetniCasovi(double vremetraenje) {
        proverka = vremetraenje;
    }

    Device() {
        strcpy(this->model, "NaN");
        this->tip_ured = (tip) 0;
        //   this->proverka = 0.0;
        this->god_poizvodstvo = 0;
    }

    Device(char *model, tip tip_ured, int god_poizvodstvo) {
        strcpy(this->model, model);
        this->tip_ured = tip_ured;
        //  this->proverka = proverka;
        this->god_poizvodstvo = god_poizvodstvo;
    }

    Device(const Device &d) {
        strcpy(this->model, d.model);
        this->tip_ured = d.tip_ured;
        //   this->proverka = d.proverka;
        this->god_poizvodstvo = d.god_poizvodstvo;
    }

    Device &operator=(const Device &d) {
        strcpy(this->model, d.model);
        this->tip_ured = d.tip_ured;
        //  this->proverka = d.proverka;
        this->god_poizvodstvo = d.god_poizvodstvo;

        return *this;
    }

    double presmetajVreme() {
        double total_time = proverka;
        if (this->god_poizvodstvo > 2015) {
            total_time = total_time + 2;
        }
        if (this->tip_ured == kompjuter) {
            total_time = total_time + 2;

        }
        return total_time;
    }

    friend ostream &operator<<(ostream &os, Device &device) {

        os << device.model << endl;
        if (device.tip_ured == smartfon) {
            os << "Mobilen " << device.presmetajVreme() << endl;
        } else if (device.tip_ured == kompjuter) {
            os << "Laptop " << device.presmetajVreme() << endl;
        }

        return os;
    }

};

class MobileServis {

private:

    char adresa[100];
    Device *uredi;
    int br_uredi;

public:

    MobileServis() {
        strcpy(this->adresa, "NaN");
        this->uredi = nullptr;
        this->br_uredi = 0;
    }

    MobileServis(char *adresa) {
        strcpy(this->adresa, adresa);
        this->uredi = nullptr;
        this->br_uredi = 0;
    }

    MobileServis(char *adresa, Device *uredi, int br_uredi) {
        strcpy(this->adresa, adresa);

        this->uredi = new Device[br_uredi];
        for (int i = 0; i < br_uredi; i++) {
            this->uredi[i] = uredi[i];
        }

        this->br_uredi = br_uredi;
    }

    MobileServis(const MobileServis &m) {
        strcpy(this->adresa, m.adresa);

        this->uredi = new Device[m.br_uredi];
        for (int i = 0; i < m.br_uredi; i++) {
            this->uredi[i] = m.uredi[i];
        }

        this->br_uredi = m.br_uredi;
    }

    MobileServis &operator=(const MobileServis &m) {

        strcpy(this->adresa, m.adresa);

        delete[]this->uredi;
        this->uredi = new Device[m.br_uredi];
        for (int i = 0; i < m.br_uredi; i++) {
            this->uredi[i] = m.uredi[i];
        }

        this->br_uredi = m.br_uredi;
        return *this;
    }

    MobileServis &operator+=(const Device &d) {

        if (d.getGodPoizvodstvo() < 2000 || d.getGodPoizvodstvo() > 2019) {
            throw InvalidProductionDate();
        }

        Device *tmp = new Device[this->br_uredi + 1];

        for (int i = 0; i < this->br_uredi; i++) {
            tmp[i] = this->uredi[i];
        }
        tmp[this->br_uredi] = d;
        this->br_uredi++;

        delete[]this->uredi;
        this->uredi = tmp;

        return *this;
    }

    void pecatiCasovi() {
        cout << "Ime: " << this->adresa << endl;
        for (int i = 0; i < this->br_uredi; i++) {
            cout << this->uredi[i];
        }
    }

};

double Device::proverka = 1;


int main() {
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1) {
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime, (tip) tipDevice, godina);
        cin >> ime;
        MobileServis t(ime);
        cout << ig;
    }
    if (testCase == 2) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            try {
                Device tmp(ime, (tip) tipDevice, godina);
                t += tmp;
            } catch (InvalidProductionDate &i) {
                i.message();
            }

        }
        t.pecatiCasovi();
    }
    if (testCase == 3) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            try {
                Device tmp(ime, (tip) tipDevice, godina);
                t += tmp;
            } catch (InvalidProductionDate &i) {
                i.message();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 4) {
        cout << "===== Testiranje na konstruktori ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            try {
                Device tmp(ime, (tip) tipDevice, godina);
                t += tmp;
            } catch (InvalidProductionDate &i) {
                i.message();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5) {
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            try {
                Device tmp(ime, (tip) tipDevice, godina);
                t += tmp;
            } catch (InvalidProductionDate &i) {
                i.message();
            }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6) {
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            try {
                Device tmp(ime, (tip) tipDevice, godina);
                t += tmp;
            } catch (InvalidProductionDate &i) {
                i.message();
            }
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;

}

