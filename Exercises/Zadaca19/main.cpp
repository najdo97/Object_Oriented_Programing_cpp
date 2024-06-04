#include <iostream>
#include <string.h>
#include <cstring>

using namespace std;

class Parcel {

private:
    int parcel_ID;
    static int processing_price;

public:

    int getId() const {
        return parcel_ID;
    }

    Parcel() {
        this->parcel_ID = 0;
    }

    Parcel(int parcel_ID) {
        this->parcel_ID = parcel_ID;
    }

    Parcel(const Parcel &other) {
        this->parcel_ID = other.parcel_ID;
    }

    Parcel &operator=(const Parcel &other) {
        this->parcel_ID = other.parcel_ID;
        return *this;
    }

    ~Parcel() {}
    static void setProcessingPrice(int pom) {
        processing_price = pom;
    }

    int getProcessingPrice() {
        return processing_price;
    }
};

class Envelope : public Parcel {

private:
    int width;
    int highth;
    char reciver[50];

public:
    const char *getReceiver() const {
        return reciver;
    }

    Envelope() : Parcel() {
        this->width = 0;
        this->highth = 0;
        strcpy(this->reciver, "NaN");
    }

    Envelope(int parcel_ID, char *reciver, int width, int highth) : Parcel(parcel_ID) {
        strcpy(this->reciver, reciver);
        this->width = width;
        this->highth = highth;
    }

    Envelope(const Envelope &other) : Parcel(other) {
        strcpy(this->reciver, other.reciver);
        this->width = other.width;
        this->highth = other.highth;
    }

    Envelope &operator=(const Envelope &other) {
        Parcel::operator=(other);

        strcpy(this->reciver, other.reciver);
        this->width = other.width;
        this->highth = other.highth;
        return *this;
    }

    int price() {
        int total = 0;
        total = this->getProcessingPrice() + (this->highth * this->width * 0.3);

        return total;
    }

};

class PostOffice {
private:
    Envelope arr[100];
    int n;
public:
    PostOffice() {
        this->n = 0;
    }

    PostOffice(Envelope *arr, int n) {
        for (int i = 0; i < n; i++) {
            this->arr[i] = arr[i];
        }
        this->n = n;
    }

    PostOffice(const PostOffice &other) {
        for (int i = 0; i < other.n; i++) {
            this->arr[i] = other.arr[i];
        }
        this->n = other.n;
    }

    PostOffice &operator=(const PostOffice &other) {
        for (int i = 0; i < other.n; i++) {
            this->arr[i] = other.arr[i];
        }
        this->n = other.n;
        return *this;
    }

//  that adds an envelop with the given arguments in the array of envelops. This method returns the price for sending the envelope. (5 points)
    int sendEnvelope(int id, char *receiver, int length, int width) {
        if (n < 100) {
            Envelope *tmp = new Envelope(id, receiver, width, length);

            this->arr[n] = *tmp;
            this->n++;
        }

        return this->arr[this->n - 1].price();
    }

// that prints the ID of the envelops that are addressed to the passed receiver. The printing is in the following format (5 points):
//
//For [receiver] are envelops with ids:  [ID1] [ID2]  ...
    void printEnvelopsTo(char *receiver) {
        int idx = 0;
        for (int i = 0; i < n; i++) {
            if (strcmp(this->arr[i].getReceiver(), receiver) == 0) {
                idx = i;

            }
        }
        cout <<"For " <<this->arr[idx].getReceiver() << " are envelops with ids: ";

        for (int i = 0; i < n; i++) {
            if (strcmp(this->arr[i].getReceiver(), receiver) == 0) {
                cout  << this->arr[i].getId() <<" ";
            }
        }

        cout<<'\n';
    }

};


int Parcel::processing_price = 150;

int main() {

    int type;
    int n;
    int price;
    int id;
    int height, width;
    char receiver[50];

    PostOffice p;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> type;
        if (type == 1) { // send envelope
            cin >> id >> receiver >> width >> height;
            cout << "The price of sending envelope with id " << id << " is:"
                 << p.sendEnvelope(id, receiver, width, height) << endl;
        } else if (type == 2) { // print envelops to
            cin >> receiver;
            p.printEnvelopsTo(receiver);
        } else if (type == 3) { // set processing price
            cin >> price;
            Parcel::setProcessingPrice(price);
        } else if (type == 4) { // Parcel
            cin >> id;
            Parcel p1(id);
            cout << "Parcel with id [" << p1.getId() << "] is created" << endl;
        } else {// Envelope
            cin >> id >> receiver >> width >> height;
            Envelope p2(id, receiver, width, height);
            cout << "Price of sending envelope with ID: " << p2.getId() << " To: " << p2.getReceiver() << " is: "
                 << p2.price() << endl;
        }
    }
    return 0;
}
