#include <iostream>
#include <cstring>

using namespace std;

class Cinema {
private:
    char name[20];
    int showRooms;
    static float discount_student;
    float ticket_price;

public:

    float getStudentDiscount() {
        return discount_student;
    }

    const char *getname() const {
        return name;
    }

    int getShowRooms() const {
        return showRooms;
    }

    float getTicketPrice() const {
        return ticket_price;
    }

    Cinema() {
        strcpy(this->name, "bezimenko");
        this->showRooms = 0;
        this->ticket_price = 0.0;
    }

    Cinema(char *name, int showRooms, float ticket_price) {
        strcpy(this->name, name);
        this->showRooms = showRooms;
        this->ticket_price = ticket_price;
    }

    Cinema(const Cinema &c) {
        strcpy(this->name, c.name);
        this->showRooms = c.showRooms;
        this->ticket_price = c.ticket_price;
    }

    Cinema &operator=(const Cinema &c) {
        strcpy(this->name, c.name);
        this->showRooms = c.showRooms;
        this->ticket_price = c.ticket_price;

        return *this;
    }

    static void setStudentDiscount(float discount) {
        discount_student = discount;
    }

    virtual float price(bool isStudent) {
        float new_price = this->ticket_price;
        if (isStudent == true) {
            new_price = new_price - (this->ticket_price * discount_student);
        }
        return new_price;
    }

};

class ThreeDCinema : public Cinema {

private:
    char *movie_name;
    float duartion;
    bool isPremiere;

public:
    char *getMovieName() const {
        return movie_name;
    }

    float getDuartion() const {
        return duartion;
    }

    bool isPremiere1() const {
        return isPremiere;
    }

    ThreeDCinema() : Cinema() {
        this->movie_name = nullptr;
        this->duartion = 0.0;
        this->isPremiere = false;
    }

    ThreeDCinema(char *name, int showRooms, float ticket_price, char *movie_name, float duartion, bool isPremiere) : Cinema(name, showRooms, ticket_price) {

        this->movie_name = new char[strlen(movie_name) + 1];
        strcpy(this->movie_name, movie_name);

        this->duartion = duartion;
        this->isPremiere = isPremiere;
    }

    ThreeDCinema(const ThreeDCinema &_3D) : Cinema(_3D) {

        this->movie_name = new char[strlen(_3D.movie_name) + 1];
        strcpy(this->movie_name, _3D.movie_name);

        this->duartion = _3D.duartion;
        this->isPremiere = _3D.isPremiere;
    }


    ThreeDCinema &operator=(const ThreeDCinema &_3D) {
        Cinema::operator=(_3D);

        delete this->movie_name;
        this->movie_name = new char[strlen(_3D.movie_name) + 1];
        strcpy(this->movie_name, _3D.movie_name);

        this->duartion = _3D.duartion;
        this->isPremiere = _3D.isPremiere;

        return *this;
    }


    float price(bool isStudent) {
        float new_price = this->getTicketPrice();


        if (isStudent) {
            new_price = new_price - (new_price * getStudentDiscount());
        }

        if (this->duartion > 2.5 && this->duartion <= 3.0) {
            new_price = new_price + 50;
        } else if (this->duartion > 3) {
            new_price = new_price + 70;
        }
        if (this->isPremiere) {
            new_price = new_price + 60;
        }


        return new_price;
    }
};

bool searchCinema(Cinema **c, int n, char *title, bool premiere, bool isStudent) {
    if (premiere == true) {
        for (int i = 0; i < n; i++) {

            if (dynamic_cast<ThreeDCinema *>(c[i]) != nullptr) {

                if (strcmp(dynamic_cast<ThreeDCinema *>(c[i])->getname(), title) == 0 ) {

                    cout << dynamic_cast<ThreeDCinema *>(c[i])->getname() << " " << dynamic_cast<ThreeDCinema *>(c[i])->price(isStudent) << endl;
                    return true;

                }
            };
        }
    } else {
        for (int i = 0; i < n; i++) {
            if (strcmp(c[i]->getname(), title) == 0) {
                cout << c[i]->getname() << " " << c[i]->price(isStudent) << endl;
                return true;
            }
        }
    }
    return false;
}

void cheapestCinema(Cinema **halls, int n, bool isStudent) {
    int halls_3D = 0, obicni = 0;

    float min_price = halls[0]->price(isStudent);
    int min_idx = 0;
    for (int i = 0; i < n; i++) {
        if (dynamic_cast<ThreeDCinema *>(halls[i]) != nullptr) {
            halls_3D++;
        } else obicni++;

        if (min_price > halls[i]->price(isStudent)) {
            min_price = halls[i]->price(isStudent);
            min_idx = i;
        }
    }

    cout << "Cheapest movie hall: " << halls[min_idx]->getname() << " " << halls[min_idx]->price(isStudent) << endl;
    cout << "3D cinema halls: " << halls_3D << " from total " << n << endl;

}


float Cinema::discount_student = 0.17;

int main() {

    int tip, n;
    char name[100], movieName[40];
    int no;
    bool premiere;
    float ticketPrice;
    float hours;
    bool isStudent;

    cin >> tip;
    if (tip == 1) {//Cinema
        cin >> name >> no >> ticketPrice;
        Cinema k1(name, no, ticketPrice);
        cout << "Cinema created with name: " << k1.getname() << endl;
    } else if (tip == 2) {//price - Cinema
        cin >> name >> no >> ticketPrice >> isStudent;
        Cinema k1(name, no, ticketPrice);
        cout << "Initial price for the cinema with name " << k1.getname() << " is: " << k1.price(isStudent) << endl;
    } else if (tip == 3) {//3D Cinema
        cin >> name >> no >> ticketPrice >> movieName >> hours >> premiere;
        ThreeDCinema s(name, no, ticketPrice, movieName, hours, premiere);
        cout << "Cinema created with name " << s.getname() << " and discount " << s.getStudentDiscount() << endl;
    } else if (tip == 4) {//price - 3DCinema
        cin >> name >> no >> ticketPrice >> movieName >> hours >> premiere >> isStudent;
        ThreeDCinema s(name, no, ticketPrice, movieName, hours, premiere);
        cout << "The price for the cinema " << s.getname() << " is: " << s.price(isStudent) << endl;
    } else if (tip == 5) {//cheapest Cinema
        Cinema **halls = new Cinema *[5];
        int n;
        halls[0] = new Cinema("Cineplexx1", 1, 350);
        halls[1] = new ThreeDCinema("Milenium3D", 44, 285, "Shrek", 2.5, false);
        halls[2] = new ThreeDCinema("Vardar", 12, 333, "StarWars", 4, true);
        halls[2] = new ThreeDCinema("Home", 44, 299, "Godfather", 5, false);
        halls[3] = new Cinema("Cineplexx2", 2, 333);
        halls[4] = new ThreeDCinema("Cinedays", 1, 310, "ManInBlack", 5, true);
        cheapestCinema(halls, 5, true);
    } else if (tip == 6) {//search
        Cinema **halls = new Cinema *[5];
        halls[0] = new Cinema("Cineplexx1", 1, 350);
        halls[1] = new ThreeDCinema("Milenium3D", 44, 285, "Shrek", 2.5, false);
        halls[2] = new ThreeDCinema("Vardar", 12, 333, "StarWars", 4, true);
        halls[3] = new Cinema("Cineplexx2", 2, 333);
        halls[4] = new ThreeDCinema("Cinedays", 1, 310, "ManInBlack", 5, true);

        if (searchCinema(halls, 5, "Milenium3D", true, true))
            cout << "Found" << endl;
        else cout << "Not found" << endl;

        if (searchCinema(halls, 5, "CinePlexx1", false, false))
            cout << "Found" << endl;
        else cout << "Not found" << endl;

    } else if (tip == 7) {//change price
        Cinema **halls = new Cinema *[5];
        halls[0] = new Cinema("Cineplexx1", 1, 350);
        halls[1] = new ThreeDCinema("Milenium3D", 44, 285, "Shrek", 2.5, false);
        halls[2] = new ThreeDCinema("Vardar", 12, 333, "StarWars", 4, true);
        halls[2] = new ThreeDCinema("Domasno", 44, 299, "Godfather", 5, false);
        halls[3] = new Cinema("Cineplexx2", 2, 333);
        halls[4] = new ThreeDCinema("Cinedays", 1, 310, "ManInBlack", 5, true);
        halls[2]->setStudentDiscount(0.9);
        cheapestCinema(halls, 4, true);
    }

    return 0;
}