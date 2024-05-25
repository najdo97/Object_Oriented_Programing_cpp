#include <iostream>
#include <cstring>

using namespace std;

class AlcoholicDrink {
private:

    char name[100];
    char country_origin[100];
    float alc_percent;
    float base_price;

    static int discount;
public:

    static void changeDiscount(int d) {
        discount = d;
    }

    AlcoholicDrink() {
        strcpy(this->name, "nan");
        strcpy(this->country_origin, "nan");
        this->alc_percent = 0;
        this->base_price = 0;
    }

    AlcoholicDrink(float alc_percent, char *name, char *country_origin, float base_price) {
        this->alc_percent = alc_percent;

        strcpy(this->name, name);
        strcpy(this->country_origin, country_origin);
        this->base_price = base_price;
    }

    AlcoholicDrink(const AlcoholicDrink &a) {
        strcpy(this->name, a.name);
        strcpy(this->country_origin, a.country_origin);
        this->alc_percent = a.alc_percent;
        this->base_price = a.base_price;
    }

    AlcoholicDrink &operator=(const AlcoholicDrink &a) {
        strcpy(this->name, a.name);
        strcpy(this->country_origin, a.country_origin);
        this->alc_percent = a.alc_percent;
        this->base_price = a.base_price;

        return *this;
    }

    virtual float computePrice() = 0;

    const char *getName() const {
        return name;
    }

    const char *getCountryOrigin() const {
        return country_origin;
    }

    float getAlcPercent() const {
        return alc_percent;
    }

    float getBasePrice() const {
        return base_price;
    }

    static void total(AlcoholicDrink **ad, int n) {
        float discPrice = 0.0;

        for (int i = 0; i < n; i++) {
            discPrice += ad[i]->computePrice();
        }
        cout << "Total price: " << discPrice << endl;


        cout << "Total price with discount: " << (discPrice - ((discPrice / 100) * discount)) << endl;

    }

};

class Beer : public AlcoholicDrink {
private:
    bool ingridient;    // barley or wheat

public:
    Beer() : AlcoholicDrink() {
        this->ingridient = false;
    }


    Beer(float alc_percent, char *name, char *country_origin, float base_price, bool ingridient) : AlcoholicDrink(
            alc_percent, name, country_origin, base_price) {
        this->ingridient = ingridient;
    }

    Beer(const Beer &b) : AlcoholicDrink(b) {
        this->ingridient = b.ingridient;
    }

    Beer &operator=(const Beer &b) {
        AlcoholicDrink::operator=(b);
        this->ingridient = b.ingridient;

        return *this;
    }

    float computePrice() {
        float new_price = this->getBasePrice();
        if (this->ingridient == false) {
            new_price = new_price + (this->getBasePrice() * 0.1);
        }
        if (strcmp(this->getCountryOrigin(), "Germany") == 0) {
            new_price = new_price + (this->getBasePrice() * 0.05);
        }
        return new_price;
    }
};

class Wine : public AlcoholicDrink {
private:
    int manufacturing_year;
    char grapes_type[20];
public:

    Wine() : AlcoholicDrink() {
        this->manufacturing_year = 0;
        strcpy(this->grapes_type, "NaN");
    }

    Wine(float alc_percent, char *name, char *country_origin, float base_price, int manufacturing_year,
         char *grapes_type) : AlcoholicDrink(alc_percent, name, country_origin, base_price) {
        this->manufacturing_year = manufacturing_year;
        strcpy(this->grapes_type, grapes_type);
    }

    Wine(const Wine &w) : AlcoholicDrink(w) {
        this->manufacturing_year = w.manufacturing_year;
        strcpy(this->grapes_type, w.grapes_type);
    }

    Wine &operator=(const Wine &w) {
        AlcoholicDrink::operator=(w);

        this->manufacturing_year = w.manufacturing_year;
        strcpy(this->grapes_type, w.grapes_type);

        return *this;
    }

    float computePrice() {
        float new_price = this->getBasePrice();
        if (this->manufacturing_year < 2005) {
            new_price = new_price + (this->getBasePrice() * 0.15);
        }
        if (strcmp(this->getCountryOrigin(), "Italy") == 0) {
            new_price = new_price + (this->getBasePrice() * 0.05);
        }
        return new_price;
    }
};

//
// bool operator<(AlcoholicDrink &a) {
//    if (dynamic_cast<Beer *>(&a) != nullptr) {
//        if (this->computePrice() < dynamic_cast<Beer *>(&a)->computePrice()) {
//            return true;
//        }
//    }
//    if (dynamic_cast<Wine *>(&a) != nullptr) {
//        if (this->computePrice() < dynamic_cast<Wine *>(&a)->computePrice()) {
//            return true;
//        }
//    }
//    return false;
//}

ostream &operator<<(ostream &os, AlcoholicDrink &drink) {
    if (dynamic_cast<Beer *>(&drink) != nullptr) {
        os << dynamic_cast<Beer *>(&drink)->getName() << " " << dynamic_cast<Beer *>(&drink)->getCountryOrigin() << " "
           << dynamic_cast<Beer *>(&drink)->computePrice() << endl;
    }
    if (dynamic_cast<Wine *>(&drink) != nullptr) {
        os << dynamic_cast<Wine *>(&drink)->getName() << " " << dynamic_cast<Wine *>(&drink)->getCountryOrigin() << " "
           << dynamic_cast<Wine *>(&drink)->computePrice() << endl;
    }
    return os;
}

void lowestPrice(AlcoholicDrink **drinks, int n) {

    float cheapest = drinks[0]->computePrice();
    int cheapest_idx;
    for (int i = 0; i < n; i++) {
        if (drinks[i]->computePrice() < cheapest) {
            cheapest = drinks[i]->computePrice();
            cheapest_idx = i;
        }
    }

    cout << *drinks[cheapest_idx] << endl;
}

int AlcoholicDrink::discount = 5;


int main() {
    int testCase;
    cin >> testCase;
    float p;
    char name[100];
    char country[100];
    float price;
    bool mainI;
    int year;
    char grape[20];
    if (testCase == 1) {
        cout << "===== TESTING CONSTRUCTORS ======" << endl;
        cin >> p;
        cin >> name;
        cin >> country;
        cin >> price;
        cin >> mainI;
        Beer b(p, name, country, price, mainI);
        cout << b << endl;
        cin >> p;
        cin >> name;
        cin >> country;
        cin >> price;
        cin >> year;
        cin >> grape;
        Wine w(p, name, country, price, year, grape);
        cout << w << endl;

    } else if (testCase == 2) {
        cout << "===== TESTING LOWEST PRICE ======" << endl;
        int n;
        cin >> n;
        AlcoholicDrink **ad = new AlcoholicDrink *[n];
        for (int i = 0; i < n; ++i) {
            cin >> p;
            cin >> name;
            cin >> country;
            cin >> price;

            if (i % 2 == 1) {
                cin >> mainI;
                ad[i] = new Beer(p, name, country, price, mainI);
            } else {
                cin >> year;
                cin >> grape;
                ad[i] = new Wine(p, name, country, price, year, grape);
            }
        }

        lowestPrice(ad, n);
        for (int i = 0; i < n; ++i) {
            delete ad[i];
        }
        delete[] ad;
    } else if (testCase == 3) {
        cout << "===== TESTING DISCOUNT STATIC ======" << endl;
        int n;
        cin >> n;
        AlcoholicDrink **ad = new AlcoholicDrink *[n];
        for (int i = 0; i < n; ++i) {
            cin >> p;
            cin >> name;
            cin >> country;
            cin >> price;
            if (i % 2 == 1) {
                cin >> mainI;
                ad[i] = new Beer(p, name, country, price, mainI);
            } else {
                cin >> year;
                cin >> grape;
                ad[i] = new Wine(p, name, country, price, year, grape);
            }
        }
        AlcoholicDrink::total(ad, n);
        int d;
        cin >> d;
        AlcoholicDrink::changeDiscount(d);
        AlcoholicDrink::total(ad, n);
        for (int i = 0; i < n; ++i) {
            delete ad[i];
        }
        delete[] ad;
    }

}

