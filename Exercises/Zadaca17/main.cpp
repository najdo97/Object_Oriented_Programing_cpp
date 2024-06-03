#include <iostream>

#include <cstring>

using namespace std;

class Piano {

private:
    char serial[25];
    float price;
    int production_year;

public:
     char *getSerial()  {
        return serial;
    }

    void setSerial(char *tmp) {
        strcpy(this->serial, tmp);
    }

    float getPrice() const {
        return price;
    }

    int getProductionYear() const {
        return production_year;
    }

    Piano(char *serial) {
        strcpy(this->serial, serial);
        this->price = 0;
        this->production_year = 0;
    }

    Piano() {
        strcpy(this->serial, "nan");
        this->price = 0.0;
        this->production_year = 0;

    }

    Piano(char *serial, float price, int production_year) {
        strcpy(this->serial, serial);
        this->price = price;
        this->production_year = production_year;
    }

    Piano(const Piano &other) {
        strcpy(this->serial, other.serial);
        this->price = other.price;
        this->production_year = other.production_year;
    }

    Piano &operator=(const Piano &other) {
        strcpy(this->serial, other.serial);
        this->price = other.price;
        this->production_year = other.production_year;

        return *this;
    }

    ~Piano() {

    }

    bool equals(Piano &other) {
        if (strcmp(this->serial, other.serial) == 0) {
            return true;
        }
        return false;
    }

    void print() {
        cout << this->serial << " " << this->production_year << " " << this->price << endl;
    }

};


class PShop {

private:
    char store_name[50];
    Piano *arr;
    int arr_size;
public:

    Piano &getP(int i) {
        return this->arr[i];
    }

    PShop() {
        strcpy(this->store_name, "NaN");
        this->arr = nullptr;
        this->arr_size = 0;
    }

    PShop(char *store_name) {
        strcpy(this->store_name, store_name);
        this->arr = nullptr;
        this->arr_size = 0;
    }

    PShop(char *store_name, Piano *arr, int arr_size) {
        strcpy(this->store_name, store_name);

        this->arr = new Piano[arr_size];
        for (int i = 0; i < arr_size; i++) {
            this->arr[i] = arr[i];
        }
        this->arr_size = arr_size;
    }

    PShop(const PShop &other) {
        strcpy(this->store_name, other.store_name);

        this->arr = new Piano[other.arr_size];
        for (int i = 0; i < other.arr_size; i++) {
            this->arr[i] = other.arr[i];
        }
        this->arr_size = other.arr_size;
    }

    PShop &operator=(const PShop &other) {
        strcpy(this->store_name, other.store_name);

        delete[]this->arr;
        this->arr = new Piano[other.arr_size];
        for (int i = 0; i < other.arr_size; i++) {
            this->arr[i] = other.arr[i];
        }
        this->arr_size = other.arr_size;

        return *this;
    }


    ~PShop() {
        delete[]this->arr;
    }

    double value() {
        double total_sum = 0;
        for (int i = 0; i < this->arr_size; i++) {
            total_sum = total_sum + this->arr[i].getPrice();
        }
        return total_sum;
    }

    void add(Piano p) {

        Piano *tmp = new Piano[this->arr_size + 1];
        for (int i = 0; i < this->arr_size; i++) {
            tmp[i] = this->arr[i];
        }
        tmp[this->arr_size] = p;
        this->arr_size++;

        delete[]this->arr;
        this->arr = tmp;
    }

    void sell(Piano p) {
        int j = 0;
        Piano *tmp = new Piano[this->arr_size];
        for (int i = 0; i < this->arr_size; i++) {
            if (strcmp(this->arr[i].getSerial(), p.getSerial()) == 0) {
                continue;
            }
            tmp[j] = this->arr[i];
            j++;
        }

        this->arr_size = j;
        delete[]this->arr;

        this->arr = new Piano[j];
        for (int i = 0; i < j; i++) {
            this->arr[i] = tmp[i];
        }

        delete[]tmp;

    }

    void print() {
        cout << this->store_name << endl;

        for (int i = 0; i < this->arr_size; i++) {
            cout << i + 1<<". ";
            this->arr[i].print();
        }
    }

};

int main() {

    int n;
    cin >> n;


    if (n == 1) {
        cout << "---Class Piano---" << endl;
        char serialNo[25];
        int pYear;
        float price;
        cin >> serialNo >> price >> pYear;
        Piano p(serialNo, price, pYear);
        p.print();
    } else if (n == 2) {
        cout << "---Equals---" << endl;
        char serialNo[25];
        int pYear;
        float price;
        cin >> serialNo >> price >> pYear;
        Piano p1(serialNo, price, pYear);
        Piano p2(p1);
        if (p1.equals(p2))
            cout << "Equality" << endl;
        else
            cout << "Inequality" << endl;
        p2.setSerial("12344");
        if (p1.equals(p2))
            cout << "Equality" << endl;
        else
            cout << "Inequality" << endl;
    } else if (n == 3) {
        cout << "---Class PShop---" << endl;
        char name[50];
        cin >> name;
        PShop ps(name);
        ps.print();
    } else if (n == 4) {
        cout << "---Add method---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin >> no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i = 0; i < no; i++) {
            cin >> serialNo >> price >> pYear;
            Piano p(serialNo, price, pYear);
            ps.add(p);
        }
        ps.print();
    } else if (n == 5) {
        cout << "---Add method---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin >> no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i = 0; i < no; i++) {
            cin >> serialNo >> price >> pYear;
            Piano p(serialNo, price, pYear);
            ps.add(p);
        }
        PShop ps2(ps), ps3;

        cin >> serialNo >> price >> pYear;
        Piano p1(serialNo, price, pYear);
        ps2.add(p1);

        ps.print();
        ps2.print();

        ps3 = ps;
        cin >> serialNo >> price >> pYear;
        Piano p2(serialNo, price, pYear);
        ps3.add(p2);

        ps.print();
        ps3.print();

    } else if (n == 6) {
        cout << "---value method---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin >> no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i = 0; i < no; i++) {
            cin >> serialNo >> price >> pYear;
            Piano p(serialNo, price, pYear);
            ps.add(p);
        }
        cout << "Total price: " << ps.value() << endl;
    } else if (n == 7) {
        cout << "---sell method---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin >> no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i = 0; i < no; i++) {
            cin >> serialNo >> price >> pYear;
            Piano p(serialNo, price, pYear);
            ps.add(p);
        }
        int d;
        cin >> d;
        Piano p1(ps.getP(d).getSerial());
        ps.sell(p1);
        ps.print();
    } else if (n == 8) {
        cout << "---Full Test---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin >> no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i = 0; i < no; i++) {
            cin >> serialNo >> price >> pYear;
            Piano p(serialNo, price, pYear);
            ps.add(p);
        }
        ps.print();

        cout << endl;

        PShop ps2(ps), ps3;

        cin >> serialNo >> price >> pYear;
        Piano p1(serialNo, price, pYear);
        ps2.add(p1);

        ps.print();
        ps2.print();

        ps3 = ps;
        cin >> serialNo >> price >> pYear;
        Piano p2(serialNo, price, pYear);
        ps3.add(p2);

        ps.print();
        ps3.print();

        cout << endl;

        cout << "Total price: " << ps.value() << endl;

        cout << endl;

        int d;
        cin >> d;
        Piano p3(ps.getP(d).getSerial());
        ps.sell(p3);
        ps.print();

        cout << "Total price: " << ps.value() << endl;
    }
    return 0;
}