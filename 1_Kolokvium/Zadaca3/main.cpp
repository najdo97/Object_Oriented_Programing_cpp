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

    char  *get_company_name()
    {
        return company_name;
    }

    //default constructor
      StockRecord(){};

    // parametarized constructor

    StockRecord(char *stock_id, char *company_name, double buying_price, int number_of_shares){

        strcpy(this->stock_id,stock_id);
        strcpy(this->company_name,company_name);

        this->buying_price=buying_price;
        this->number_of_shares=number_of_shares;
    };





    StockRecord(char *stock_id, char *company_name, double buying_price, double current_price, int number_of_shares){

            strcpy(this->stock_id,stock_id);
            strcpy(this->company_name,company_name);

            this->buying_price=buying_price;
            this->current_price=current_price;
            this->number_of_shares=number_of_shares;
        };

        // copy constructor
    StockRecord(const StockRecord &other){
            strcpy(this->stock_id,other.stock_id);
            strcpy(this->company_name,other.company_name);

            this->buying_price=other.buying_price;
            this->current_price=other.current_price;
            this->number_of_shares=other.number_of_shares;
        }

    void setNewPrice(double c) {
        this->current_price=c;
    }

    double value() {

        double value=0.0;
        value=this->number_of_shares*this->current_price;

        return value;
    };

    // ne sum siguren deka ovaa funkcija mora / moze da e const
     double profit() const {

        double profit=0.0;
        profit=this->number_of_shares * (this->current_price - this->buying_price);

        return profit;

    };



    friend std::ostream& operator<<(std::ostream& os, const StockRecord& record) {

       os   <<  record.company_name << '\n'
            << record.number_of_shares << '\n'
            << record.buying_price << '\n'
            << record.current_price << '\n'
            << record.profit()<<'\n';
        return os;
    }

};

class Client {

private:
    char name[60];
    int account_id;
    int num_of_owned_stocks;
    StockRecord *owned_stocks;

public:


    Client(){};

    // Client c(clientName, clientID);
    Client(char *name, int account_id){

        strcpy(this->name,name);
        this->account_id=account_id;
    };


    Client(char *name, int account_id, int num_of_owned_stocks,StockRecord *owned_stocks){

        strcpy(this->name,name);
        this->account_id=account_id;
        this->num_of_owned_stocks=num_of_owned_stocks;

        this->owned_stocks=new StockRecord[num_of_owned_stocks];
        for(int i=0; i<num_of_owned_stocks; i++)
        {
            this->owned_stocks[i]=owned_stocks[i];
        }

    };

    Client(const Client &other){

        strcpy(this->name,other.name);
        this->account_id=other.account_id;
        this->num_of_owned_stocks=other.num_of_owned_stocks;

        this->owned_stocks=new StockRecord[other.num_of_owned_stocks];
        for(int i=0; i<other.num_of_owned_stocks; i++)
        {
            this->owned_stocks[i]=other.owned_stocks[i];
        }

    };

    ~Client()
    {
        delete [] owned_stocks;
    }


    double totalValue() const{

        double portfolioValue=0;

        for(int i=0; i < this->num_of_owned_stocks;i++)
        {
            portfolioValue = portfolioValue + this->owned_stocks[i].value();
        }

        return portfolioValue;
    }


    //todo - преоптоварат оператор += за купување на нова компанија во портфолиото (додавање на нов објект од класата StockRecord во низата со компании


    // Razberi kako funkcionira ova !!

    Client& operator+=(const StockRecord& stock) {

        this->owned_stocks[this->num_of_owned_stocks+1]=stock;

        return *this;
    }


    //todo- преоптоварат оператор  << за печатење на информации за портфолиото на клиентот така што во
    // првиот ред ќе бидат прикажани ID на сметката и моменталната вредност на портфолиото одделени со празно место,
    // а во секој нареден ред ќе бидат прикажани компаниите од кои е составено портфолиото, секоја во посебен ред


     friend std::ostream& operator<<(std::ostream& os, const Client& record) {

        os   <<  record.account_id << " " << record.totalValue() << '\n';
        for(int i = 0 ; i<<record.num_of_owned_stocks; i++)
        {
            os   <<  record.owned_stocks[i].get_company_name()<< '\n';

        }

        return os;
    }
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