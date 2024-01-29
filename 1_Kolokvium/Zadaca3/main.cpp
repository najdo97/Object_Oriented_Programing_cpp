#include<iostream>
#include<cstring>

using namespace std;

// vasiot kod za klasite ovde
class StockRecord {
private:
    char stock_id[12];
    char company_name[50];
    double buying_price;
    double current_price;
    int number_of_shares;

public:
    //default constructor
    // parametarized constructor
    // copy constructor
    // destructor ? - mislam deka nemora ova


    void setNewPrice(double c) {
        this->current_price=c;
    }

    double value() {

        double value=0.0;
        value=this->number_of_shares*this->current_price;

        return value;
    };

    double profit() {

        double profit=0.0;
        profit=this->number_of_shares * (this->current_price - this->buying_price);

        return profit;

    };


    //todo - да се преоптовари операторот << за печатење на објектот во следниот формат:
    // Компанија БројНаАкции КуповнаЦена МоменталнаЦена Профит
    StockRecord &operator<<() {

    }

};

class Client {

    private:
    char name[60];
    int account_id;
    StockRecord owned_stocks;
    int num_of_owned_stocks;

    public:

    //  default constructor
    //  paramteiziran konstruktor
    //  copy constructor
    //  destruktor

/*todo - ја пресметува моменталната вредност на акциите кои ги поседува клиентот.
        Таа се пресметува како збир од вредноста на сите акции од секоја компанија од кои е составено клиентското портфолио
  */
    double totalValue(){

    }


    //todo - преоптоварат оператор += за купување на нова компанија во портфолиото (додавање на нов објект од класата StockRecord во низата со компании
    Client operator+=(){

    }


    //todo- преоптоварат оператор  << за печатење на информации за портфолиото на клиентот така што во првиот ред ќе бидат прикажани ID на сметката и
    // моменталната вредност на портфолиото одделени со празно место, а во секој нареден ред ќе бидат прикажани компаниите од кои е составено портфолиото, секоја во посебен ред
    Client operator<< (){

    };
};





// ne menuvaj vo main-ot

int main() {

    int test;
    cin >> test;

    if (test == 1) {
        double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    } else if (test == 2) {
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
        char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    } else if (test == 3) {
        cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for (int i = 0; i < n; ++i) {
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if (flag) {
                cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;

}