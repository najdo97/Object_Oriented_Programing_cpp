#include <iostream>
#include <cstring>

using namespace std;


class IceCream {

private:
    char *ime;
    char sostav[100];
    float cena;
    int popust;

public:

    IceCream() {
        this->ime = nullptr;

        strcpy(this->sostav, "NaN");
        this->cena = 0.0;
        this->popust = 0;
    };

    IceCream(char *ime, char *sostav, float cena) {

        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);

        strcpy(this->sostav, sostav);
        this->cena = cena;
        this->popust = 0;
    };

    IceCream(const IceCream &i) {
        this->ime = new char[strlen(i.ime) + 1];
        strcpy(this->ime, i.ime);

        strcpy(this->sostav, i.sostav);
        this->cena = i.cena;
        this->popust = i.popust;
    };

    ~IceCream() {
        delete[] this->ime;
    };


    IceCream &operator=(const IceCream &i) {

        delete[]this->ime;
        this->ime = new char[strlen(i.ime) + 1];
        strcpy(this->ime, i.ime);

        strcpy(this->sostav, i.sostav);
        this->cena = i.cena;
        this->popust = i.popust;

        return *this;
    }

    void setName(char *ime) {
        delete[]this->ime;
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
    }

    void setDiscount(int popust) {
        this->popust = popust;      // rangot e od 0-100, moze ke treba if-uslov i throw error message za nadvor od tie granici
    }


    friend ostream &operator<<(ostream &os, const IceCream &c) {

        if (c.popust == 0) {
            os << c.ime << " " << c.sostav << " " << c.cena << endl;
        } else {

            int cena_so_popust = 0;
            cena_so_popust = c.cena - (c.cena * c.popust / 100);
            os << c.ime << " " << c.sostav << " " << cena_so_popust << endl;
        }
        return os;
    }

    IceCream &operator++() {

        this->popust = this->popust + 5;
        return *this;
    }

    IceCream &operator+(const char *i) {

        char *pom = new char[strlen(this->ime) + strlen(i) + 1];

        strcpy(pom, this->ime);
        strcat(pom, i);     // mislam deka nema da ima prazno mesto vo dodadeniot zbor

        delete[]this->ime;

        this->ime = pom;

        return *this;
    }


};


class IceCreamShop {

private:

    char ime[50];
    IceCream *sladoledi;
    int br_sladoledi;

public:

    IceCreamShop() {
        strcpy(this->ime, "NaN");
        this->sladoledi = nullptr;
        this->br_sladoledi = 0;
    };

    IceCreamShop(char *ime) {

        strcpy(this->ime, ime);

        this->sladoledi = nullptr;
        this->br_sladoledi = 0;

    };

    IceCreamShop(char *ime, IceCream *sladoledi, int br_sladoledi) {
        strcpy(this->ime, ime);

        this->sladoledi = new IceCream[br_sladoledi];
        for (int i = 0; i < br_sladoledi; i++) {
            this->sladoledi[i] = sladoledi[i];
        }
        this->br_sladoledi = br_sladoledi;
    };

    IceCreamShop(const IceCreamShop &ice) {
        strcpy(this->ime, ice.ime);

        this->sladoledi = new IceCream[ice.br_sladoledi];
        for (int i = 0; i < ice.br_sladoledi; i++) {
            this->sladoledi[i] = ice.sladoledi[i];
        }
        this->br_sladoledi = ice.br_sladoledi;
    };

    ~IceCreamShop() {
        delete[]this->sladoledi;
    };

    IceCreamShop &operator=(const IceCreamShop &ice) {
        strcpy(this->ime, ice.ime);

        delete[]this->sladoledi;

        this->sladoledi = new IceCream[ice.br_sladoledi];
        for (int i = 0; i < ice.br_sladoledi; i++) {
            this->sladoledi[i] = ice.sladoledi[i];
        }
        this->br_sladoledi = ice.br_sladoledi;

        return *this;
    };


    //todo
    IceCreamShop &operator+=(const IceCream &i){

        return*this;
    }

    //todo
    friend ostream &operator<<(ostream &os, const IceCreamShop &shop) {

        os  << shop.ime << endl;

        for(int i=0;i<shop.br_sladoledi;i++) {

            os << shop.sladoledi[i]. << endl;

        }
        return os;
    }


};

int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
    cin.get();
    if (testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name, 100);
        cin.getline(ingr, 100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name, 100);
        cin.getline(ingr, 100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR <<" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if (testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name, 100);
        cin.getline(ingr, 100);
        cin >> price;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name, 100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name, 100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;

        cin >> discount;
        ic1.setDiscount(discount);


    } else if (testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName, 100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, 100);
            cin.getline(ingr, 100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if (testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName, 100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, 100);
            cin.getline(ingr, 100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics += x;
        cout << ics << endl;
        cout << icp << endl;
    }


    return 0;
}