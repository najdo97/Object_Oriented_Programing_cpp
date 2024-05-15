#include <iostream>
#include <cstring>

using namespace std;

class ExistingGame {

public:

    ExistingGame() {};

    void message() {
        cout << "Igrata e vekje kupena" << endl;
    }

};

class Game {

private:
    char ime[50];
    float cena;
    bool kupena_na_rasprodazba;

public:
    Game() {
        strcpy(this->ime, "Nan");
        this->cena = 0;
        this->kupena_na_rasprodazba = false;
    };

    Game(char *ime, float cena, bool kupena_na_rasprodazba) {
        strcpy(this->ime, ime);
        this->cena = cena;
        this->kupena_na_rasprodazba = kupena_na_rasprodazba;
    };

    Game(const Game &g) {
        strcpy(this->ime, g.ime);
        this->cena = g.cena;
        this->kupena_na_rasprodazba = g.kupena_na_rasprodazba;
    };

    Game &operator=(const Game &g) {
        strcpy(this->ime, g.ime);
        this->cena = g.cena;
        this->kupena_na_rasprodazba = g.kupena_na_rasprodazba;

        return *this;
    };

    const char *getIme() const {
        return ime;
    }

    float getCena() const {
        return cena;
    }

    bool isKupenaNaRasprodazba() const {
        return kupena_na_rasprodazba;
    }

    void setIme(char *ime) {
        strcpy(this->ime, ime);
    };

    void setCena(float cena) {
        Game::cena = cena;
    }

    void setKupenaNaRasprodazba(bool kupenaNaRasprodazba) {
        kupena_na_rasprodazba = kupenaNaRasprodazba;
    }

    /*
        За класите Game и SubscriptionGame да се преоптоварат операторите за печатење (<<) и читање (>>).
        Да се дефинира и операторот == кој ќе споредува игри според нивното име.
    */

    friend ostream &operator<<(ostream &os, const Game &game) {
        os << game.ime << " " << game.cena << " " << game.kupena_na_rasprodazba << endl;

        return os;
    }

    friend istream &operator>>(istream &is, Game &game) {

        is >> game.ime >> game.cena >> game.kupena_na_rasprodazba;

        return is;
    }

    bool operator==(const Game &g) {

        if (strcmp(this->ime, g.ime) == 0) {
            return true;
        } else return false;
    }

};

class SubscriptionGame : public Game {

private:
    float pretplata;
    int mesec_kupuvanje;
    int godina_kupuvanje;

public:
    SubscriptionGame() : Game() {
        this->pretplata = 0;
        this->mesec_kupuvanje = 0;
        this->godina_kupuvanje = 0;
    }

    SubscriptionGame(char *ime, float cena, bool kupena_na_rasprodazba, float pretplata, int mesec_kupuvanje,
                     int godina_kupuvanje) : Game(ime, cena, kupena_na_rasprodazba) {
        this->pretplata = pretplata;
        this->mesec_kupuvanje = mesec_kupuvanje;
        this->godina_kupuvanje = godina_kupuvanje;
    }

    SubscriptionGame(const SubscriptionGame &s) : Game(s) {
        this->pretplata = s.pretplata;
        this->mesec_kupuvanje = s.mesec_kupuvanje;
        this->godina_kupuvanje = s.godina_kupuvanje;
    }

    SubscriptionGame &operator=(const SubscriptionGame &s) {
        Game::operator=(s);

        this->pretplata = s.pretplata;
        this->mesec_kupuvanje = s.mesec_kupuvanje;
        this->godina_kupuvanje = s.godina_kupuvanje;

        return *this;
    }

    friend ostream &operator<<(ostream &os, const SubscriptionGame &game) {


        os << dynamic_cast<const Game &>(game) << " " <<
           game.pretplata << " " <<
           game.mesec_kupuvanje << " " <<
           game.godina_kupuvanje << " " << endl;

        return os;
    }

    friend istream &operator<<(istream &is, const SubscriptionGame &game) {

        return is;
    }

    // operator==  bi trebalo da moze da se iskorist od base class, imeto samo tamu se zacucuca
    // za da se iskoristi meze ke treba da se upcastne so dynamic_cast<>

    /*
        За класите Game и SubscriptionGame да се преоптоварат операторите за печатење (<<) и читање (>>).
        Да се дефинира и операторот == кој ќе споредува игри според нивното име.
    */

};

class User {

private:
    char username[100];
    Game *kupeni_igri;
    int br_igri;

public:
    User() {
        strcpy(this->username, "nan");
        this->kupeni_igri = nullptr;
        this->br_igri = 0;
    }

    User(char *username) {
        strcpy(this->username, username);
        this->kupeni_igri = nullptr;
        this->br_igri = 0;
    }


    User(char *username, Game *kupeni_igri, int br_igri) {

        strcpy(this->username, username);

        this->kupeni_igri = new Game[br_igri];
        for (int i = 0; i < br_igri; i++) {
            this->kupeni_igri[i] = kupeni_igri[i];
        }
        this->br_igri = br_igri;
    }

    User(const User &u) {

        strcpy(this->username, u.username);

        this->kupeni_igri = new Game[u.br_igri];
        for (int i = 0; i < u.br_igri; i++) {
            this->kupeni_igri[i] = u.kupeni_igri[i];
        }

        this->br_igri = u.br_igri;
    }

    ~User() {
        delete[] kupeni_igri;
    }

    User &operator=(const User &u) {

        strcpy(this->username, u.username);

        delete[]kupeni_igri;
        this->kupeni_igri = new Game[u.br_igri];
        for (int i = 0; i < u.br_igri; i++) {
            this->kupeni_igri[i] = u.kupeni_igri[i];
        }

        this->br_igri = u.br_igri;

        return *this;
    }


    /*     Да се преоптовари операторот += кој ќе овозможи додавање на нова игра во колекцијата на игри.
         Притоа ако корисникот ја има веќе купено играта, потребно е да се креира исклучок од типот ExistingGame.
         Класата за имплементација на исклучоци потребно е има соодветен конструктор и метода message за печатење на порака на екран.
    */
    User &operator+=(const Game &g) {

        // treba da gi sporedime site igri so 'g', za da vidime dali se povtoruva

        for (int i = 0; i < this->br_igri; i++) {
            if(this->kupeni_igri[i]==g){
                throw ExistingGame();
            }
        }


        Game *pom = new Game[this->br_igri + 1];

        for (int i = 0; i < this->br_igri; i++) {
            pom[i] = this->kupeni_igri[i];
        }

        pom[this->br_igri] = g;
        this->br_igri++;

        delete[] this->kupeni_igri;
        this->kupeni_igri = pom;


        return *this;
    }


};


int main() {
    int test_case_num;

    cin >> test_case_num;

    // for Game
    char game_name[100];
    float game_price;
    bool game_on_sale;

    // for SubscritionGame
    float sub_game_monthly_fee;
    int sub_game_month, sub_game_year;

    // for User
    char username[100];
    int num_user_games;

    if (test_case_num == 1) {
        cout << "Testing class Game and operator<< for Game" << std::endl;
        cin.get();
        cin.getline(game_name, 100);
        //cin.get();
        cin >> game_price >> game_on_sale;

        Game g(game_name, game_price, game_on_sale);

        cout << g;
    } else if (test_case_num == 2) {
        cout << "Testing class SubscriptionGame and operator<< for SubscritionGame" << std::endl;
        cin.get();
        cin.getline(game_name, 100);

        cin >> game_price >> game_on_sale;

        cin >> sub_game_monthly_fee;
        cin >> sub_game_month >> sub_game_year;

        SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month,
                            sub_game_year);
        cout << sg;
    } else if (test_case_num == 3) {
        cout << "Testing operator>> for Game" << std::endl;
        Game g;

        cin >> g;

        cout << g;
    } else if (test_case_num == 4) {
        cout << "Testing operator>> for SubscriptionGame" << std::endl;
        SubscriptionGame sg;

        cin >> sg;

        cout << sg;
    } else if (test_case_num == 5) {
        cout << "Testing class User and operator+= for User" << std::endl;
        cin.get();
        cin.getline(username, 100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >> num_user_games;

        try {

            for (int i = 0; i < num_user_games; ++i) {

                cin >> game_type;

                Game *g;
                // 1 - Game, 2 - SubscriptionGame
                if (game_type == 1) {
                    cin.get();
                    cin.getline(game_name, 100);

                    cin >> game_price >> game_on_sale;
                    g = new Game(game_name, game_price, game_on_sale);
                } else if (game_type == 2) {
                    cin.get();
                    cin.getline(game_name, 100);

                    cin >> game_price >> game_on_sale;

                    cin >> sub_game_monthly_fee;
                    cin >> sub_game_month >> sub_game_year;
                    g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee,
                                             sub_game_month,
                                             sub_game_year);
                }

                //cout<<(*g);


                u += (*g);
            }
        } catch (ExistingGame &ex) {
            ex.message();
        }

        cout << u;

//    cout<<"\nUser: "<<u.get_username()<<"\n";

//    for (int i=0; i < u.get_games_number(); ++i){
//        Game * g;
//        SubscriptionGame * sg;
//        g = &(u.get_game(i));

//        sg = dynamic_cast<SubscriptionGame *> (g);

//        if (sg){
//          cout<<"- "<<(*sg);
//        }
//        else {
//          cout<<"- "<<(*g);
//        }
//        cout<<"\n";
//    }

    } else if (test_case_num == 6) {
        cout << "Testing exception ExistingGame for User" << std::endl;
        cin.get();
        cin.getline(username, 100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >> num_user_games;

        for (int i = 0; i < num_user_games; ++i) {

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1) {
                cin.get();
                cin.getline(game_name, 100);

                cin >> game_price >> game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            } else if (game_type == 2) {
                cin.get();
                cin.getline(game_name, 100);

                cin >> game_price >> game_on_sale;

                cin >> sub_game_monthly_fee;
                cin >> sub_game_month >> sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month,
                                         sub_game_year);
            }

            //cout<<(*g);

            try {
                u += (*g);
            }
            catch (ExistingGame &ex) {
                ex.message();
            }
        }

        cout << u;

//      for (int i=0; i < u.get_games_number(); ++i){
//          Game * g;
//          SubscriptionGame * sg;
//          g = &(u.get_game(i));

//          sg = dynamic_cast<SubscriptionGame *> (g);

//          if (sg){
//            cout<<"- "<<(*sg);
//          }
//          else {
//            cout<<"- "<<(*g);
//          }
//          cout<<"\n";
//      }
    } else if (test_case_num == 7) {
        cout << "Testing total_spent method() for User" << std::endl;
        cin.get();
        cin.getline(username, 100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >> num_user_games;

        for (int i = 0; i < num_user_games; ++i) {

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1) {
                cin.get();
                cin.getline(game_name, 100);

                cin >> game_price >> game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            } else if (game_type == 2) {
                cin.get();
                cin.getline(game_name, 100);

                cin >> game_price >> game_on_sale;

                cin >> sub_game_monthly_fee;
                cin >> sub_game_month >> sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month,
                                         sub_game_year);
            }

            //cout<<(*g);


            u += (*g);
        }

        cout << u;

        cout << "Total money spent: $" << u.total_spent() << endl;
    }
}
