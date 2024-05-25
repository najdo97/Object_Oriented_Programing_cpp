#include<iostream>
#include<string.h>

using namespace std;

class ExistingBill {

private:
public:
    void message() {
        cout << "The bill already exists" << endl;
    }
};

class Bill {

private:
    char *billNumber;
    int expense;
    char issued_date[8];    //MM.YYYY
    bool isPaied;

public:

    int getExpense() const {
        return expense;
    }

    bool getIsPaied() const {
        return isPaied;
    }

    const char *getIssuedDate() const {
        return issued_date;
    }

    Bill() {
        this->billNumber = nullptr;
        this->expense = 0;
        strcpy(this->issued_date, "NaN");
        this->isPaied = false;
    }

    Bill(char *billNumber, int expense, char *issued_date, bool isPaied) {
        this->billNumber = new char[strlen(billNumber) + 1];
        strcpy(this->billNumber, billNumber);

        this->expense = expense;
        strcpy(this->issued_date, issued_date);
        this->isPaied = isPaied;
    }

    Bill(const Bill &b) {
        this->billNumber = new char[strlen(b.billNumber) + 1];
        strcpy(this->billNumber, b.billNumber);

        this->expense = b.expense;
        strcpy(this->issued_date, b.issued_date);
        this->isPaied = b.isPaied;
    }

    Bill &operator=(const Bill &b) {
        delete this->billNumber;
        this->billNumber = new char[strlen(b.billNumber) + 1];
        strcpy(this->billNumber, b.billNumber);

        this->expense = b.expense;
        strcpy(this->issued_date, b.issued_date);
        this->isPaied = b.isPaied;

        return *this;
    }

    bool operator==(const Bill &b) {
        if (this->billNumber == nullptr) {
            return false;
        }
        if (strcmp(this->billNumber, b.billNumber) == 0) {
            return true;
        } else return false;
    }

    friend ostream &operator<<(ostream &os, const Bill &bill) {
        os << bill.billNumber << "(" << bill.issued_date << ") - " << bill.expense << endl;
        return os;
    }

};


class UserProfile {

private:
    char username[30];
    Bill billsArray[30];
    int numBills;
public:

    UserProfile() {
        strcpy(this->username, "NaN");
        for (int i = 0; i < 30; i++) {
            billsArray[i] = Bill();
        }
        this->numBills = 0;
    }

    UserProfile(char *username) {
        strcpy(this->username, username);

//        for (int i = 0; i < 30; i++) {
//            billsArray[i] = Bill();
//        }
        this->numBills = 0;
    }

    UserProfile(char *username, Bill *billsArray, int numBills) {
        strcpy(this->username, username);
        for (int i = 0; i < numBills; i++) {
            billsArray[i] = billsArray[i];
        }
        this->numBills = numBills;
    }

    UserProfile(const UserProfile &u) {
        strcpy(this->username, u.username);
        for (int i = 0; i < u.numBills; i++) {
            billsArray[i] = u.billsArray[i];
        }
        this->numBills = u.numBills;
    }

    UserProfile &operator=(const UserProfile &u) {
        strcpy(this->username, u.username);
        for (int i = 0; i < u.numBills; i++) {
            billsArray[i] = u.billsArray[i];
        }
        this->numBills = u.numBills;
        return *this;
    }


    UserProfile &operator+=(Bill &b) {

        if (this->billsArray != nullptr) {
            for (int i = 0; i < this->numBills; i++) {
              //  cout << "vlaga - i:" << i << endl;
                if ((this->billsArray[i].operator==(b)) == true) {
                    throw ExistingBill();
                }
            }
        }

        this->billsArray[this->numBills] = b;
        numBills++;


        return *this;
    }


    friend ostream &operator<<(ostream &os, UserProfile &profile) {

        os << "Unpaid bills of user " << profile.username << " are: " << endl;
        for (int i = 0; i < profile.numBills; i++) {
            if (profile.billsArray[i].getIsPaied() == false) {

                cout << profile.billsArray[i];
            }
        }
        return os;
    }

    int totalDue(int month, int year) {
        char tmp1[8];
        int m = 0, g = 0;
        char pom;
        int total = 0;
        for (int i = 0; i < this->numBills; i++) {
            strcpy(tmp1, this->billsArray[i].getIssuedDate());
            pom = tmp1[0];
            m = pom - '0';
            m = m * 10;
            pom = tmp1[1];
            m = m + (pom - '0');
            if (m == month) {
                pom = tmp1[3];
                g = pom - '0';
                g = g * 10;

                pom = tmp1[4];
                g = g + (pom - '0');
                g = g * 10;

                pom = tmp1[5];
                g = g + (pom - '0');
                g = g * 10;

                pom = tmp1[6];
                g = g + (pom - '0');
                if (g == year) {

                    total = total + this->billsArray[i].getExpense();

                }


            }
        }
        return total;
    }

};


int main() {
    char number[50], month[8], name[50];
    int price, n;
    bool status;


    int type;
    cin >> type;

    if (type == 1) {
        cout << "-----Test Bill & operator &lt;&lt;-----" << endl;
        cin >> number >> price >> month >> status;
        Bill b(number, price, month, status);
        cout << b;
    } else if (type == 2) {
        cout << "-----Test Bill & operator == -----" << endl;
        cin >> number >> price >> month >> status;
        Bill b1(number, price, month, status);
        cin >> number >> price >> month >> status;
        Bill b2(number, price, month, status);
        if (b1 == b2) cout << "Equal" << endl;
        else cout << "Not equal" << endl;

    } else if (type == 3) {
        cout << "-----Test UserProfile & operator += &&lt;&lt; -----" << endl;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            Bill s(number, price, month, status);
            try {
                up += s;
            } catch (ExistingBill &e) {
                e.message();
            }

        }
        cout << up;
    } else if (type == 4) {
        cout << "-----Test UserProfile & operator += & totalDue -----" << endl;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            Bill s(number, price, month, status);
            try {
                up += s;
            } catch (ExistingBill &e) {
                e.message();
            }
        }
        int m, y;
        cin >> m >> y;
        cout << "Total due for month " << m << " and year " << y << " is:";
        cout << up.totalDue(m, y) << endl;
    } else if (type == 5) {
        cout << "-----Test all -----" << endl;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            Bill s(number, price, month, status);
            try {
                up += s;
            } catch (ExistingBill &e) {
                e.message();
            }
        }
        cout << up;
        int m, y;
        cin >> m >> y;
        cout << "Total due for month " << m << " and year " << y << " is:";
        cout << up.totalDue(m, y) << endl;
    }

    return 0;
}
