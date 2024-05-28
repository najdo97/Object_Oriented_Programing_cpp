#include<iostream>
#include <cstring>

using namespace std;

class nonDigitException {

public:
    void message() {
        cout << "The id number has a non-digit character" << endl;
    }


};

class tooLongException {
public:
    void message() {
        cout << "The id number has more than 9 characters" << endl;
    }
};

class DonaciskiApel {
private:
    char *name;
    char id_num[15];
    int collected_fund;
    int needed_fund;

public:

    const char *getID() const {
        return id_num;
    }

    DonaciskiApel() {
        this->name = nullptr;
        strcpy(this->id_num, "nan");
        this->collected_fund = 0;
        this->needed_fund = 0;
    }


    DonaciskiApel(char *name, char *id_num, int needed_fund) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);

        if (strlen(id_num) > 9) {
            throw tooLongException();
        }
        for (int i = 0; i < strlen(id_num); i++) {
            if (isalpha(id_num[i]) == true) {
                throw nonDigitException();
            }
        }
        strcpy(this->id_num, id_num);

        this->needed_fund = needed_fund;
    }

    DonaciskiApel(char *name, char *id_num, int collected_fund, int needed_fund) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);

        strcpy(this->id_num, id_num);
        this->collected_fund = collected_fund;
        this->needed_fund = needed_fund;
    }

    DonaciskiApel(const DonaciskiApel &other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);

        strcpy(this->id_num, other.id_num);
        this->collected_fund = other.collected_fund;
        this->needed_fund = other.needed_fund;
    }

    DonaciskiApel &operator=(const DonaciskiApel &other) {
        delete [] this->name;
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);

        strcpy(this->id_num, other.id_num);
        this->collected_fund = other.collected_fund;
        this->needed_fund = other.needed_fund;

        return *this;
    }

    friend ostream &operator<<(ostream &os, const DonaciskiApel &apel) {
        if (apel.collected_fund >= apel.needed_fund) {
            os << apel.id_num << " " << apel.name << " collected" << endl;
        } else {
            os << apel.id_num << " " << apel.name << " " << apel.needed_fund - apel.collected_fund << " more denars are needed" << endl;
        }

        return os;
    }

    DonaciskiApel &operator+=(const int donacija) {

        this->collected_fund = this->collected_fund + donacija;

        return *this;
    }

    bool operator<(DonaciskiApel &d) {
        if ((this->needed_fund - this->collected_fund) < (d.needed_fund - d.collected_fund)) {
            return true;
        } else if ((this->needed_fund - this->collected_fund) == (d.needed_fund - d.collected_fund)) {
            // todo - comapre by id
        }

        return false;
    }

    ~DonaciskiApel() {
        delete [] this->name;
    }
};

class DonaciskoDurstvo {
private:

    char president[30];
    DonaciskiApel *apeli;
    int br_apeli;

public:
    DonaciskoDurstvo() {
        strcpy(this->president, "NaN");
        this->apeli = nullptr;
        this->br_apeli = 0;
    }

    DonaciskoDurstvo(char *president) {
        strcpy(this->president, president);
        this->apeli = nullptr;
        this->br_apeli = 0;
    }

    DonaciskoDurstvo(char *president, DonaciskiApel *apeli, int br_apeli) {
        strcpy(this->president, president);

        this->apeli = new DonaciskiApel[br_apeli];
        for (int i = 0; i < br_apeli; i++) {
            this->apeli[i] = apeli[i];
        }

        this->br_apeli = br_apeli;
    }

    DonaciskoDurstvo(const DonaciskoDurstvo &other) {
        strcpy(this->president, other.president);

        this->apeli = new DonaciskiApel[other.br_apeli];
        for (int i = 0; i < other.br_apeli; i++) {
            this->apeli[i] = other.apeli[i];
        }

        this->br_apeli = other.br_apeli;
    }

    DonaciskoDurstvo &operator=(const DonaciskoDurstvo &other) {
        strcpy(this->president, other.president);

        delete [] this->apeli;
        this->apeli = new DonaciskiApel[other.br_apeli];
        for (int i = 0; i < other.br_apeli; i++) {
            this->apeli[i] = other.apeli[i];
        }

        this->br_apeli = other.br_apeli;

        return *this;
    }

    ~DonaciskoDurstvo() {
        delete []this->apeli;
    }

    bool primiiDonacija(char *id, int donirana_suma) {

        for (int i = 0; i < this->br_apeli; i++) {
            if (strcmp(this->apeli[i].getID(), id) == 0) {
                this->apeli[i].operator+=(donirana_suma);
                return true;
            }
        }
        return false;
    }

    DonaciskoDurstvo &operator+=(const DonaciskiApel &d) {
        for (int i = 0; i < this->br_apeli; i++) {
            if (strcmp(this->apeli[i].getID(), d.getID()) == 0) {
                return *this;
            }
        }
        DonaciskiApel *tmp = new DonaciskiApel[this->br_apeli + 1];

        for (int i = 0; i < this->br_apeli; i++) {
            tmp[i] = this->apeli[i];
        }

        tmp[this->br_apeli] = d;
        this->br_apeli++;
        delete[] this->apeli;
        this->apeli = tmp;

        return *this;
    }

    friend ostream &operator<<(ostream &os, const DonaciskoDurstvo &durstvo) {
        for (int i = 0; i < durstvo.br_apeli; i++) {

            os << durstvo.apeli[i]; // trebda da se podredi po descending order
        }

        os << "President: " << durstvo.president << endl;
        return os;
    }


};

int main() {


    DonaciskoDurstvo donacii("Velko Velkovski");
    int n;
    char naziv[50], id[50];
    int potrebnasuma, doniranasuma;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin.get();
        cin.getline(naziv, 50);
        cin >> id >> potrebnasuma;
        try {
            DonaciskiApel edna(naziv, id, potrebnasuma);
            donacii += edna;
        } catch (tooLongException &e) {
            e.message();

        } catch (nonDigitException &e) {
            e.message();
        }

    }

    //donation
    cin >> n;
    for (int i = 0; i < n; i++) {

        cin >> id >> doniranasuma;

        if (!donacii.primiiDonacija(id, doniranasuma))
            cout << "The donation is not taken. Wrong ID." << endl;
    }
    cout << "===============" << endl;
    cout << donacii;

    return 0;
}
