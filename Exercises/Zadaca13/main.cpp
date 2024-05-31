#include <iostream>
#include <cstring>


using namespace std;

class Pasta {

private:
    char *pasta_name;
    float price;
    int discount;
    int kcal;
public:

    Pasta() {
        this->pasta_name = nullptr;
        this->price = 0.0;
        this->discount = 0;
        this->kcal = 0;
    }


    Pasta(char *pasta_name, float price, int kcal) {
        this->pasta_name = new char[strlen(pasta_name) + 1];
        strcpy(this->pasta_name, pasta_name);

        this->price = price;
        this->discount = 0;
        this->kcal = kcal;
    }

    Pasta(char *pasta_name, float price, int discount, int kcal) {
        this->pasta_name = new char[strlen(pasta_name) + 1];
        strcpy(this->pasta_name, pasta_name);

        this->price = price;
        this->discount = discount;
        this->kcal = kcal;
    }

    Pasta(const Pasta &other) {
        this->pasta_name = new char[strlen(other.pasta_name) + 1];
        strcpy(this->pasta_name, other.pasta_name);

        this->price = other.price;
        this->discount = other.discount;
        this->kcal = other.kcal;
    }

    Pasta &operator=(const Pasta &other) {
        delete[]this->pasta_name;
        this->pasta_name = new char[strlen(other.pasta_name) + 1];
        strcpy(this->pasta_name, other.pasta_name);

        this->price = other.price;
        this->discount = other.discount;
        this->kcal = other.kcal;

        return *this;
    }

    ~Pasta() {
        delete[]this->pasta_name;
    }

    void print() {
        if (this->discount == 0) {
            cout << this->pasta_name << " " << this->kcal << " " << this->price << endl;
        } else {
            cout << this->pasta_name << " " << this->kcal << " " << this->price << " (" << this->price - (this->price * this->discount / 100) << ")" << endl;
        }
    }

    void dby5() {
        this->discount = this->discount - 5;
    }

    Pasta light(int subtractKcal) {

        char *tmp = new char[strlen(this->pasta_name) + 7];
        strcat(tmp, this->pasta_name);
        strcat(tmp, "Light");
        delete[]this->pasta_name;
        this->pasta_name = tmp;

        this->price = this->price - (this->price * 0.2);

        this->kcal = this->kcal - subtractKcal;

        this->discount = 0;
        return *this;
    }

    void setDiscount(int discount) {

        this->discount = discount;
    }

    void setName(char *name) {
        delete[]this->pasta_name;

        this->pasta_name = new char[strlen(name) + 1];
        strcpy(this->pasta_name, name);

    }


};

class ItalianRestaurant {

private:
    char name[50];
    Pasta *pasta_arr;
    int num_pasta;

public:

    ItalianRestaurant() {
        strcpy(this->name, "NaN");
        this->pasta_arr = nullptr;
        this->num_pasta = 0;
    }

    ItalianRestaurant(char *name) {
        strcpy(this->name, name);
        this->pasta_arr = nullptr;
        this->num_pasta = 0;
    }

    ItalianRestaurant(char *name, Pasta *pasta_arr, int num_pasta) {

        strcpy(this->name, name);

        if (pasta_arr != nullptr) {
            this->pasta_arr = new Pasta[num_pasta];
            for (int i = 0; i < num_pasta; i++) {
                this->pasta_arr[i] = pasta_arr[i];
            }
        } else this->pasta_arr = nullptr;

        this->num_pasta = num_pasta;
    }

    ItalianRestaurant(const ItalianRestaurant &other) {

        strcpy(this->name, other.name);

        if (other.pasta_arr != nullptr) {
            this->pasta_arr = new Pasta[other.num_pasta];
            for (int i = 0; i < other.num_pasta; i++) {
                this->pasta_arr[i] = other.pasta_arr[i];
            }
        } else this->pasta_arr = nullptr;

        this->num_pasta = other.num_pasta;
    }

    ItalianRestaurant &operator=(const ItalianRestaurant &other) {

        strcpy(this->name, other.name);

        delete[]this->pasta_arr;
        if (other.pasta_arr != nullptr) {
            this->pasta_arr = new Pasta[other.num_pasta];
            for (int i = 0; i < other.num_pasta; i++) {
                this->pasta_arr[i] = other.pasta_arr[i];
            }
        } else this->pasta_arr = nullptr;

        this->num_pasta = other.num_pasta;

        return *this;
    }

    ~ItalianRestaurant() {
        delete[]this->pasta_arr;
    }

    void add(Pasta &p) {
        Pasta *tmp = new Pasta[this->num_pasta + 1];
        for (int i = 0; i < this->num_pasta; i++) {
            tmp[i] = this->pasta_arr[i];
        }
        tmp[this->num_pasta] = p;
        this->num_pasta++;

        delete[]this->pasta_arr;
        this->pasta_arr = tmp;
    }

    void print() {
        cout << this->name << endl;
        for (int i = 0; i < this->num_pasta; i++) {
            this->pasta_arr[i].print();
        }
    }

    void setPasta(int i, Pasta &p) {
        this->pasta_arr[i] = p;
    }

};

int main() {
    char name[100];
    float price;
    int discount;
    int calories;

    int testCase;

    cin >> testCase;

    if (testCase == 1) {
        cout << "====== TESTING Pasta CLASS ======" << endl;
        cin >> name;
        cin >> price;
        cin >> discount;
        cin >> calories;
        cout << "CONSTRUCTOR" << endl;
        Pasta c1(name, price, calories);
        c1.setDiscount(discount);
        cin >> name;
        cin >> price;
        cin >> discount;
        cin >> calories;
        Pasta c2(name, price, calories);
        c2.setDiscount(discount);
        cout << "Print" << endl;
        c1.print();
        // cout << endl;
        c2.print();
        //cout << endl;
        cout << "Decrease by 5" << endl;
        c1.dby5();
        c1.print();
        // cout << endl;
        cout << "Calories" << endl;
        int ca;
        cin >> ca;
        Pasta c3 = c1.light(ca);
        c3.print();
        // cout << endl;
    } else if (testCase == 2) {
        cout << "====== TESTING Pasta CONSTRUCTORS ======" << endl;
        cin >> name;
        cin >> price;
        cin >> discount;
        cin >> calories;
        cout << "CONSTRUCTOR" << endl;
        Pasta c1(name, price, calories);
        c1.print();
        //  cout << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        Pasta c2(c1);
        cin >> name;
        c2.setName(name);
        c1.print();
        // cout << endl;
        c2.print();
        // cout << endl;
        cout << "OPERATOR =" << endl;
        c1 = c2;
        cin >> name;
        c2.setName(name);
        c1.print();
        // cout << endl;
        c2.print();
        // cout << endl;

    } else if (testCase == 3) {
        cout << "====== TESTING Italian Restaurant ======" << endl;
        char csName[50];
        cin >> csName;
        cout << "CONSTRUCTOR" << endl;
        ItalianRestaurant cs(csName);
        int n;
        cin >> n;
        cout << "Add" << endl;
        for (int i = 0; i < n; ++i) {
            cin >> name;
            cin >> price;
            cin >> calories;
            Pasta c(name, price, calories);
            cs.add(c);
        }
        cs.print();
        // cout << endl;

    } else if (testCase == 4) {
        cout << "====== TESTING Italian Restaurant CONSTRUCTORS ======" << endl;
        char csName[50];
        cin >> csName;
        ItalianRestaurant cs(csName);
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> name;
            cin >> price;
            cin >> calories;
            Pasta c(name, price, calories);
            cs.add(c);
        }
        Pasta x("Funghi", 260, 275);
        ItalianRestaurant cp = cs;
        cs.setPasta(0, x);
        cs.print();
        cout << endl;
        cp.print();
        cout << endl;
    }


    return 0;
}