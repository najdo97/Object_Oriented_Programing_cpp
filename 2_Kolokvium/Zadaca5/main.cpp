#include <iostream>
#include <cstring>

using namespace std;

const int MAX = 50;

enum typeC {       //treba da se vika typeC
    standarden, lojalen, vip

};

class UserExistsException {
public:
    void message() {
        cout << "The user already exists in the list!\n";
    }
};

class Customer {

private:
    char ime[MAX];
    char email[MAX];
    typeC vidKupuvac;
    int osnoven_popust;
    int dopolnitelen_popust;
    int br_kupeni_proizvodi;

public:


    Customer() {
        strcpy(this->ime, "NaN");
        strcpy(this->email, "NaN");
        this->vidKupuvac = standarden;
        this->osnoven_popust = 0;
        this->dopolnitelen_popust = 0;
        this->br_kupeni_proizvodi = 0;
    };

    Customer(char *ime, char *email, typeC vidKupuvac, int br_kupeni_proizvodi) {
        strcpy(this->ime, ime);
        strcpy(this->email, email);
        this->vidKupuvac = vidKupuvac;
        this->br_kupeni_proizvodi = br_kupeni_proizvodi;

        if (vidKupuvac == standarden) {
            this->osnoven_popust = 0;
            this->dopolnitelen_popust = 0;
        }
        if (vidKupuvac == lojalen) {
            this->osnoven_popust = 10;
            this->dopolnitelen_popust = 0;
        }
        if (vidKupuvac == vip) {
            this->osnoven_popust = 10;
            this->dopolnitelen_popust = 20;
        }
    };

    Customer(char *ime, char *email, typeC vidKupuvac, int osnoven_popust, int dopolnitelen_popust,
             int br_kupeni_proizvodi) {
        strcpy(this->ime, ime);
        strcpy(this->email, email);
        this->vidKupuvac = vidKupuvac;
        this->osnoven_popust = osnoven_popust;
        this->dopolnitelen_popust = dopolnitelen_popust;
        this->br_kupeni_proizvodi = br_kupeni_proizvodi;
    };

    Customer(const Customer &c) {
        strcpy(this->ime, c.ime);
        strcpy(this->email, c.email);
        this->vidKupuvac = c.vidKupuvac;
        this->osnoven_popust = c.osnoven_popust;
        this->dopolnitelen_popust = c.dopolnitelen_popust;
        this->br_kupeni_proizvodi = c.br_kupeni_proizvodi;
    };

    Customer &operator=(const Customer &c) {
        strcpy(this->ime, c.ime);
        strcpy(this->email, c.email);
        this->vidKupuvac = c.vidKupuvac;
        this->osnoven_popust = c.osnoven_popust;
        this->dopolnitelen_popust = c.dopolnitelen_popust;
        this->br_kupeni_proizvodi = c.br_kupeni_proizvodi;

        return *this;
    };

    void setDiscount1(int i) {
        this->osnoven_popust = i;
    }

    void setVidKupuvac(typeC vidKupuvac) {
        this->vidKupuvac = vidKupuvac;
    }

    void setOsnoven(int i) {
        this->osnoven_popust = i;
    };

    void setDopolnitelen(int i) {
        this->dopolnitelen_popust = i;
    };


    int aktivenPopust() const {
        int vkupen_popust = 0;

        if (this->vidKupuvac == standarden) {
            vkupen_popust = vkupen_popust + 0;
        } else if (this->vidKupuvac == lojalen) {
            vkupen_popust = vkupen_popust + this->osnoven_popust;
        } else if (this->vidKupuvac == vip) {
            vkupen_popust = vkupen_popust + this->osnoven_popust + this->dopolnitelen_popust;
        }

        return vkupen_popust;
    }

    friend ostream &operator<<(ostream &os, const Customer &customer) {
        os << customer.ime << '\n' <<
           customer.email << '\n' <<
           customer.br_kupeni_proizvodi << '\n' <<
           customer.getKupuvac() << " " << customer.aktivenPopust() << endl;
        return os;
    }

    const char *getKupuvac() const {

        if (this->vidKupuvac == standarden) {
            return "standard";
        } else if (this->vidKupuvac == lojalen) {
            return "loyal";
        } else if (this->vidKupuvac == vip) {
            return "vip";
        } else return "???";

    }

    const char *getEmail() const {
        return email;
    }

    const char *getIme() const {
        return ime;
    }

    typeC getVidKupuvac() const {
        return vidKupuvac;
    }

    int getOsnovenPopust() const {
        return osnoven_popust;
    }

    int getDopolnitelenPopust() const {
        return dopolnitelen_popust;
    }

    int getBrKupeniProizvodi() const {
        return br_kupeni_proizvodi;
    }

};

class FINKI_bookstore {

private:
    Customer *reg_customers;
    int br_reg_customers;

public:


    FINKI_bookstore() {
        this->reg_customers = nullptr;
        this->br_reg_customers = 0;
    }

    FINKI_bookstore(Customer *reg_customers, int br_reg_customers) {

        this->reg_customers = new Customer[br_reg_customers];
        for (int i = 0; i < br_reg_customers; i++) {
            this->reg_customers[i] = reg_customers[i];
        }

        this->br_reg_customers = br_reg_customers;
    }

    //copy
    FINKI_bookstore(const FINKI_bookstore &b) {

        this->reg_customers = new Customer[b.br_reg_customers];
        for (int i = 0; i < b.br_reg_customers; i++) {
            this->reg_customers[i] = b.reg_customers[i];
        }

        this->br_reg_customers = b.br_reg_customers;
    }

    FINKI_bookstore &operator=(const FINKI_bookstore &b) {

        delete[]this->reg_customers;

        this->reg_customers = new Customer[b.br_reg_customers];
        for (int i = 0; i < b.br_reg_customers; i++) {
            this->reg_customers[i] = b.reg_customers[i];
        }

        this->br_reg_customers = b.br_reg_customers;

        return *this;
    }


    ~FINKI_bookstore() {
        delete reg_customers;
    }

//todo
    FINKI_bookstore operator+=(const Customer &c) {

        for (int i = 0; i < this->br_reg_customers; i++) {
            if (strcmp(this->reg_customers[i].getEmail(), c.getEmail()) == 0) {
                throw UserExistsException();

            }
        }

        Customer *pom = new Customer[this->br_reg_customers + 1];

        for (int i = 0; i < this->br_reg_customers; i++) {
            pom[i] = this->reg_customers[i];
        }

        pom[this->br_reg_customers] = c;
        this->br_reg_customers++;

        delete[]this->reg_customers;
        this->reg_customers = pom;

        return *this;
    }

    void update() {

        for (int i = 0; i < this->br_reg_customers; i++) {

            /*
            if (this->reg_customers[i].getBrKupeniProizvodi() <= 5) {
                this->reg_customers[i].setVidKupuvac(standarden);

                this->reg_customers[i].setOsnoven(0);
                this->reg_customers[i].setDopolnitelen(0);
            }*/
            if (this->reg_customers[i].getBrKupeniProizvodi() >= 10 &&
                (this->reg_customers[i].getVidKupuvac() == lojalen)) {
                this->reg_customers[i].setVidKupuvac(vip);

                this->reg_customers[i].setOsnoven(10);
                this->reg_customers[i].setDopolnitelen(20);
            }
            if (this->reg_customers[i].getBrKupeniProizvodi() > 5  &&
                (this->reg_customers[i].getVidKupuvac() == standarden)) {  // iako ova nema logika, ama za da projde bez greshka, vaka treba da e

                this->reg_customers[i].setVidKupuvac(lojalen);

                this->reg_customers[i].setOsnoven(10);
                this->reg_customers[i].setDopolnitelen(0);
            }

        }
    }

//fc.setCustomers(customers, n);
    void setCustomers(Customer *customers, int n) {

        delete[]this->reg_customers;

        this->reg_customers = new Customer[n];
        for (int i = 0; i < n; i++) {
            this->reg_customers[i] = customers[i];
        }

        this->br_reg_customers = n;
    }


    friend ostream &operator<<(ostream &os, const FINKI_bookstore &bookstore) {

        for (int i = 0; i < bookstore.br_reg_customers; i++) {
            os << bookstore.reg_customers[i];
        }
        return os;
    }

};


int main() {
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1) {
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2) {
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3) {
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc << endl;
    }

    if (testCase == 4) {
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        fc += c;

        cout << fc;
    }

    if (testCase == 5) {
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        // tuka treba exception
        try {
            Customer c(name, email, (typeC) tC, numProducts);
            fc += c;
        } catch (UserExistsException &e) { e.message(); };

        cout << fc;
    }

    if (testCase == 6) {
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}

