#include<iostream>
#include<cstring>

using namespace std;


class InvestmentPlan {
private:
    char investor_name[80];
    float sum_investment;
    float shares;
    bool isToday; //true - current day payment, false - old payment

public:

    const char *getInvestorName() const {
        return investor_name;
    }

    float getSumInvestment() const {
        return sum_investment;
    }

    float getShares() const {
        return shares;
    }

    bool isToday1() const {
        return isToday;
    }

    InvestmentPlan() {
        strcpy(this->investor_name, "NaN");
        this->sum_investment = 0.0;
        this->shares = 0.0;
        this->isToday = false; //true - current day payment, false - old payment
    }

    InvestmentPlan(char *investor_name, float sum_investment, float shares, bool isToday) {
        strcpy(this->investor_name, investor_name);
        this->sum_investment = sum_investment;
        this->shares = shares;
        this->isToday = isToday;
    }

    InvestmentPlan(const InvestmentPlan &other) {
        strcpy(this->investor_name, other.investor_name);
        this->sum_investment = other.sum_investment;
        this->shares = other.shares;
        this->isToday = other.isToday;
    }

    InvestmentPlan &operator=(const InvestmentPlan &other) {
        strcpy(this->investor_name, other.investor_name);
        this->sum_investment = other.sum_investment;
        this->shares = other.shares;
        this->isToday = other.isToday;

        return *this;
    }

};

class InvestmentFund {

private:
    char fund_name[50];
    InvestmentPlan *investment_plans;
    int num_plans;
    float price_share;

public:

    double totalSum() {
        double vkupno = 0;
        for (int i = 0; i < num_plans; i++) {
            vkupno = vkupno + (this->investment_plans[i].getShares() * price_share);
        }
        return vkupno;
    }

    double newPlansSum() {
        double vkupno = 0;
        for (int i = 0; i < num_plans; i++) {
            if (this->investment_plans[i].isToday1()) {
                vkupno = vkupno + this->investment_plans[i].getSumInvestment();
            }
        }
        return vkupno;
    }


    const char *getFundName() const {
        return fund_name;
    }

    InvestmentPlan *getInvestmentPlans() const {
        return investment_plans;
    }

    int getNumPlans() const {
        return num_plans;
    }

    float getPriceShare() const {
        return price_share;
    }

    InvestmentFund() {
        strcpy(this->fund_name, "NaN");
        this->investment_plans = nullptr;
        this->num_plans = 0;
        this->price_share = 0;

    }

    InvestmentFund(char *fund_name, InvestmentPlan *investment_plans, int num_plans, float price_share) {
        strcpy(this->fund_name, fund_name);

        this->investment_plans = new InvestmentPlan[num_plans];
        for (int i = 0; i < num_plans; i++) {
            this->investment_plans[i] = investment_plans[i];
        }

        this->num_plans = num_plans;
        this->price_share = price_share;

    }

    InvestmentFund(const InvestmentFund &other) {
        strcpy(this->fund_name, other.fund_name);

        this->investment_plans = new InvestmentPlan[other.num_plans];
        for (int i = 0; i < other.num_plans; i++) {
            this->investment_plans[i] = other.investment_plans[i];
        }

        this->num_plans = other.num_plans;
        this->price_share = other.price_share;

    }

    InvestmentFund &operator=(const InvestmentFund &other) {
        strcpy(this->fund_name, other.fund_name);

        delete[]this->investment_plans;
        this->investment_plans = new InvestmentPlan[other.num_plans];
        for (int i = 0; i < other.num_plans; i++) {
            this->investment_plans[i] = other.investment_plans[i];
        }

        this->num_plans = other.num_plans;
        this->price_share = other.price_share;

        return *this;
    }

    virtual double profit() = 0;

};

class MoneyFund : public InvestmentFund {
private:
    static float provison;
public:

    MoneyFund() : InvestmentFund() {};

    MoneyFund(char *fund_name, InvestmentPlan *investment_plans, int num_plans, float price_share) : InvestmentFund(fund_name, investment_plans, num_plans, price_share) {};

    MoneyFund(const MoneyFund &other) : InvestmentFund(other) {};

    MoneyFund &operator=(const MoneyFund &other) {
        InvestmentFund::operator=(other);
        return *this;
    };

    double profit() {
        double profitMoneyFund = 0;
        profitMoneyFund = (this->totalSum() * provison / 100) / 365;

        return profitMoneyFund;
    }

};

class ActionFund : public InvestmentFund {
private:
    static float yearly_provision;
    static float entry_provision;

public:
    ActionFund() : InvestmentFund() {}

    ActionFund(char *fund_name, InvestmentPlan *investment_plans, int num_plans, float price_share) : InvestmentFund(fund_name, investment_plans, num_plans, price_share) {}

    ActionFund(const ActionFund &other) : InvestmentFund(other) {};

    ActionFund &operator=(const ActionFund &other) {
        InvestmentFund::operator=(other);
        return *this;
    }

    double profit() {
        double profitActionFund = 0;

        profitActionFund = ((this->totalSum() * (yearly_provision / 100)) / 365) + (this->newPlansSum() * entry_provision / 100);

        return profitActionFund;
    }


};

float MoneyFund::provison = 1.0;
float ActionFund::entry_provision = 3.0;
float ActionFund::yearly_provision = 1.5;

double totalProfit(InvestmentFund **funds, int n) {
    double totalen = 0;
    for (int i = 0; i < n; i++) {
        totalen = totalen + funds[i]->profit();
    }

    return totalen;
}

int main() {

    char investitor[80], ime[50];
    double plan, brUdeli, udel;
    bool flag = false;
    int n, m;
    cin >> n;
    InvestmentFund **fondovi = new InvestmentFund *[n];
    for (int i = 0; i < n; i++) {
        cin >> ime;
        cin >> m;
        InvestmentPlan *ip = new InvestmentPlan[m];
        for (int j = 0; j < m; j++) {
            cin >> investitor >> plan >> brUdeli;
            if (j % 2) flag = true;
            else flag = false;
            InvestmentPlan IP(investitor, plan, brUdeli, flag);
            ip[j] = IP;
        }
        cin >> udel;
        if (i % 2) {
            fondovi[i] = new ActionFund(ime, ip, m, udel);

        } else {
            fondovi[i] = new MoneyFund(ime, ip, m, udel);
        }
    }
    cout << totalProfit(fondovi, n);
    return 0;
}
