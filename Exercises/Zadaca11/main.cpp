#include <iostream>
#include <cstring>

using namespace std;

class InvalidDiscount {
private:

public:
    void message(int value) {
        cout << "Invalid discount value: " << value << endl;
    }
};

class IceCream {

private:

    char *name;
    char ingredients[100];
    float price;
    static int discount;
public:


    IceCream() {
        this->name = nullptr;
        strcpy(this->ingredients, "NaN");
        this->price = 0;
    }

    IceCream(char *name, char *ingredients, float price) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);

        strcpy(this->ingredients, ingredients);
        this->price = price;
    }

    IceCream(const IceCream &other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);

        strcpy(this->ingredients, other.ingredients);
        this->price = other.price;
    }

    IceCream &operator=(const IceCream &other) {
        delete[]this->name;
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);

        strcpy(this->ingredients, other.ingredients);
        this->price = other.price;

        return *this;
    }

    float discountPrice() {
        float new_price = 0;
        new_price = this->price - ((this->price / 100) * discount);
        return new_price;
    }

    friend ostream &operator<<(ostream &os, IceCream &cream) {
        if (discount == 0) {
            os << cream.name << ": " << cream.ingredients << " " << cream.price;
        } else {
            os << cream.name << ": " << cream.ingredients << " " << cream.price << " " << cream.discountPrice();
        }

        return os;
    }

    IceCream &operator++() {
        discount = discount + 5;
        return *this;
    }

    IceCream &operator+(char *str) {
        char *tmp = new char[strlen(this->name) + strlen(str) + 2];
        strcat(tmp, this->name);
        strcat(tmp, "+");
        strcat(tmp, str);

        delete[]this->name;
        this->name = tmp;

        this->price = this->price + 10;
        return *this;
    }

    void setDiscount(int discount_new) {

        if (discount_new < 0 || discount_new > 100) {
            throw InvalidDiscount();
        } else discount = discount_new;
    }

    void setName(char *name) {
        delete[]this->name;
        this->name = new char[strlen(name) + 1];

        strcpy(this->name, name);
    }

    ~IceCream() {
        delete[]this->name;
    }
};

class IceCreamShop {
private:
    char store_name[50];
    IceCream *sladoledi;
    int br_sladoledi;

public:

    IceCreamShop() {
        strcpy(this->store_name, "NaN");
        this->sladoledi = nullptr;
        this->br_sladoledi = 0;
    }

    IceCreamShop(char *store_name) {
        strcpy(this->store_name, store_name);
        this->sladoledi = nullptr;
        this->br_sladoledi = 0;
    }

    IceCreamShop(const IceCreamShop &other) {
        strcpy(this->store_name, other.store_name);

        this->sladoledi = new IceCream[other.br_sladoledi];
        for (int i = 0; i < other.br_sladoledi; i++) {
            this->sladoledi[i] = other.sladoledi[i];
        }
        this->br_sladoledi = other.br_sladoledi;
    }

    IceCreamShop &operator=(const IceCreamShop &other) {
        strcpy(this->store_name, other.store_name);

        delete[]this->sladoledi;
        this->sladoledi = new IceCream[other.br_sladoledi];
        for (int i = 0; i < other.br_sladoledi; i++) {
            this->sladoledi[i] = other.sladoledi[i];
        }
        this->br_sladoledi = other.br_sladoledi;

        return *this;
    }


    IceCreamShop &operator+=(const IceCream &other) {

        IceCream *tmp = new IceCream[this->br_sladoledi + 1];
        for (int i = 0; i < this->br_sladoledi; i++) {
            tmp[i] = this->sladoledi[i];
        }
        tmp[this->br_sladoledi] = other;
        this->br_sladoledi++;

        delete[]this->sladoledi;
        this->sladoledi = tmp;

        return *this;
    }

    ~IceCreamShop() {
        delete[] this->sladoledi;
    }

    friend ostream &operator<<(ostream &os, const IceCreamShop &shop) {

        os << shop.store_name << endl;

        for (int i = 0; i < shop.br_sladoledi; i++) {
            os << shop.sladoledi[i] << endl;
        }
        return os;
    }
};

int IceCream::discount = 0;
// DO NOT CHANGE THE MAIN FUNCTION, EXCEPT THE MARKED PART FOR HANDLING WITH THE EXCEPTION

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
        cout << "TESTING EXCEPTION" << endl;

        // your exception handling code
        try {
            cin >> discount;
            ic1.setDiscount(discount);
        } catch (InvalidDiscount &e) {
            e.message(discount);
        }

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

