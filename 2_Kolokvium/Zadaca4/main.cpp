#include <cstring>
#include <iostream>

using namespace std;

// Your Code goes here
enum Size {
    mala, golema, familijarna
};

class Pizza {

private:
    char ime[20];
    char sostojki[100];
    float osnovna_cena;

public:

    Pizza() {
        strcpy(this->ime, "NaN");
        strcpy(this->sostojki, "NaN");
        this->osnovna_cena = 0;
    };

    Pizza(char *ime, char *sostojki, float osnovna_cena) {
        strcpy(this->ime, ime);
        strcpy(this->sostojki, sostojki);
        this->osnovna_cena = osnovna_cena;
    };

    Pizza(const Pizza &p) {
        strcpy(this->ime, p.ime);
        strcpy(this->sostojki, p.sostojki);
        this->osnovna_cena = p.osnovna_cena;
    };


    Pizza &operator=(const Pizza &p) {
        strcpy(this->ime, p.ime);
        strcpy(this->sostojki, p.sostojki);
        this->osnovna_cena = p.osnovna_cena;

        return *this;
    };


    virtual float price() = 0;

    float getBasePrice() {
        return this->osnovna_cena;
    }

    friend ostream &operator<<(ostream &os, const Pizza &pizza) {};

    const char *getIme() const {
        return ime;
    }

    const char *getSostojki() const {
        return sostojki;
    }

    float getOsnovnaCena() const {
        return osnovna_cena;
    }

    bool operator<(Pizza &f) {
        if (this->price() < f.price()) {
            return true;
        } else return false;
    }


};

class FlatPizza : public Pizza {

private:
    Size golemina;

public:

    FlatPizza() : Pizza() {
        this->golemina = mala;
    }

    FlatPizza(char *ime, char *sostojki, float osnovna_cena) : Pizza(ime, sostojki, osnovna_cena) {
        this->golemina = mala;
    }


    FlatPizza(char *ime, char *sostojki, float osnovna_cena, Size golemina) : Pizza(ime, sostojki, osnovna_cena) {
        this->golemina = golemina;
    }

    FlatPizza(const FlatPizza &p) : Pizza(p) {
        this->golemina = p.golemina;
    }

    FlatPizza &operator=(const FlatPizza &p) {
        Pizza::operator=(p);
        this->golemina = p.golemina;
        return *this;
    }


    float price() override {

        float new_price = 0.0;

        if (golemina == mala) {
            new_price = Pizza::getBasePrice() + ((Pizza::getBasePrice() / 100) * 10);
        } else if (golemina == golema) {
            new_price = Pizza::getBasePrice() + ((Pizza::getBasePrice() / 100) * 20);
        } else if (golemina == familijarna) {
            new_price = Pizza::getBasePrice() + ((Pizza::getBasePrice() / 100) * 30);
        }

        return new_price;
    };

    Size getGolemina() const {
        return golemina;
    }
};


class FoldedPizza : public Pizza {
private:
    bool isBeloBrasno;
public:

    FoldedPizza() : Pizza() {
        this->isBeloBrasno = true;
    }

    FoldedPizza(char *ime, char *sostojki, float osnovna_cena) : Pizza(ime, sostojki, osnovna_cena) {
        this->isBeloBrasno = true;
    }


    FoldedPizza(char *ime, char *sostojki, float osnovna_cena, bool isBeloBrasno) : Pizza(ime, sostojki, osnovna_cena) {
        this->isBeloBrasno = isBeloBrasno;
    }

    FoldedPizza(const FoldedPizza &f) : Pizza(f) {
        this->isBeloBrasno = f.isBeloBrasno;
    }

    FoldedPizza &operator=(const FoldedPizza &f) {

        Pizza::operator=(f);
        this->isBeloBrasno = f.isBeloBrasno;

        return *this;
    }


    float price() override {

        float new_price = 0.0;
        if (isBeloBrasno == true) {
            new_price = Pizza::getBasePrice() + ((Pizza::getBasePrice() / 100) * 10);
        } else if (isBeloBrasno == false) {
            new_price = Pizza::getBasePrice() + ((Pizza::getBasePrice() / 100) * 30);
        }

        return new_price;
    };

    void setWhiteFlour(bool isBelo) {
        this->isBeloBrasno = isBelo;
    }

    bool isBeloBrasno1() const {
        return isBeloBrasno;
    }

};

ostream &operator<<(ostream &os, Pizza &pizza) {


   // os << pizza.getIme() << ": " << pizza.getSostojki();

    if (dynamic_cast<FlatPizza *>(&pizza) == nullptr) {
       FoldedPizza *folded_ptr;

        folded_ptr=dynamic_cast<FoldedPizza*>(&pizza);
        if (folded_ptr->isBeloBrasno1() == true) {
            os << pizza.getIme() << ": " << pizza.getSostojki() << ", wf - " << folded_ptr->price() << endl;
        } else if (folded_ptr->isBeloBrasno1() == false) {
            os << pizza.getIme() << ": " << pizza.getSostojki() << ", nwf - " << folded_ptr->price() << endl;        }

    } else if (dynamic_cast<FlatPizza *>(&pizza) != nullptr) {
        FlatPizza *flat_ptr;
        flat_ptr=dynamic_cast<FlatPizza*>(&pizza);

        if (flat_ptr->getGolemina() == mala) {
            os << pizza.getIme() << ": " << pizza.getSostojki() << ", small - " << flat_ptr->price() << endl;
        } else if (flat_ptr->getGolemina() == golema) {
            os << pizza.getIme()<< ": " << pizza.getSostojki() << ", large - " << flat_ptr->price() << endl;
        } else if (flat_ptr->getGolemina() == familijarna) {
            os << pizza.getIme() << ": " << pizza.getSostojki() << ", family - " << flat_ptr->price() << endl;
        }

    }

    return os;
}


void expensivePizza(Pizza **pici, int n) {

    float max_price = (*pici[0]).price();
    int max_index;
    for (int i = 0; i < n; i++) {

        if (max_price < (*pici[i]).price()) {
            max_price = (*pici[i]).price();
            max_index = i;
        }
    }

    cout << *pici[max_index];

}

int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        int s;
        cin >> s;
        FlatPizza fp(name, ingredients, inPrice, (Size) s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        cin >> s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size) s);
        cout << *fp1;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        cin >> s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size) s);
        cout << *fp2;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout << "Lower price: " << endl;
        if (*fp1 < *fp2)
            cout << fp1->price() << endl;
        else cout << fp2->price() << endl;

        if (*fp1 < *fp3)
            cout << fp1->price() << endl;
        else cout << fp3->price() << endl;

        if (*fp4 < *fp2)
            cout << fp4->price() << endl;
        else cout << fp2->price() << endl;

        if (*fp3 < *fp4)
            cout << fp3->price() << endl;
        else cout << fp4->price() << endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name, 20);

                cin.getline(ingredients, 100);
                cin >> inPrice;
                int s;
                cin >> s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size) s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name, 20);
                cin.getline(ingredients, 100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza(name, ingredients, inPrice);
                if (j % 2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi, num_p);


    }
    return 0;
}
