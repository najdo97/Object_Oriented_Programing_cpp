#include <iostream>
#include <string.h>

using namespace std;

class Parcel {

private:
    int parcel_ID;
    static int processing_price;

public:

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

    void setProcessingPrice(int pom) {
        processing_price = pom;
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
