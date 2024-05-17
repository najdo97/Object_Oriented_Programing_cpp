#include <iostream>
#include <cstring>

using namespace std;

class ExistingGame {

public:

    ExistingGame() {};

    void message() {
        cout << "The game is already in the collection" << endl;
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

    virtual float getCena() const {
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

        if (game.isKupenaNaRasprodazba() == true) {
            os << "Game: " << game.ime << ", regular price: $" << game.cena << ", bought on sale";
        } else os << "Game: " << game.ime << ", regular price: $" << game.cena;

        return os;
    }

    friend istream &operator>>(istream &is, Game &game) {

        is.get();
        is.getline(game.ime, 100);

        is >> game.cena >> game.kupena_na_rasprodazba;

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
        os << dynamic_cast<const Game &>(game) << ", monthly fee: $" << game.pretplata << ", purchased: "
           << game.mesec_kupuvanje << "-" << game.godina_kupuvanje;

        return os;
    }

    friend istream &operator>>(istream &is, SubscriptionGame &game) {


        char *ime = new char[100];
        is.get();
        is.getline(ime, 100);
        dynamic_cast<Game *>(&game)->setIme(ime);


        int cena;
        is >> cena;
        game.setCena(cena);

        bool isRasprodazba;
        is >> isRasprodazba;
        game.setKupenaNaRasprodazba(isRasprodazba);

        is >> game.pretplata;
        is >> game.mesec_kupuvanje;
        is >> game.godina_kupuvanje;


        return is;
    }

    float getPretplata() const {
        return pretplata;
    }

    void setPretplata(float pretplata) {
        SubscriptionGame::pretplata = pretplata;
    }

    int getMesecKupuvanje() const {
        return mesec_kupuvanje;
    }

    void setMesecKupuvanje(int mesecKupuvanje) {
        mesec_kupuvanje = mesecKupuvanje;
    }

    int getGodinaKupuvanje() const {
        return godina_kupuvanje;
    }

    void setGodinaKupuvanje(int godinaKupuvanje) {
        godina_kupuvanje = godinaKupuvanje;
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

    //koga se dodava nekoj objekt od klasata Game ama kreiran preku konstruktorot SubscriptionGame
//mora da se iskoristi operator= od subscription game za da se zacuva celiot objekt

//        if (dynamic_cast<SubscriptionGame *>(&this->kupeni_igri[this->br_igri]) == nullptr) {
//            cout << "problem1" << endl;
//            pom[this->br_igri] = g;
//            cout << "problem2" << endl;
//        } else {
//            cout << "problem3" << endl;
//            dynamic_cast<SubscriptionGame *>(&pom[this->br_igri])->operator=(*(dynamic_cast<SubscriptionGame *>(&this->kupeni_igri[this->br_igri])));
//            cout << "problem4" << endl;
//        }


    User &operator+=(Game &g) {

        for (int i = 0; i < this->br_igri; i++) {
            if (this->kupeni_igri[i] == g) {
                throw ExistingGame();
            }
        }
        Game *pom = new Game[this->br_igri + 1];

        for (int i = 0; i < this->br_igri; i++) {
            pom[i] = this->kupeni_igri[i];
        }

        if (dynamic_cast<SubscriptionGame *>(&g) == nullptr) {
            cout << "problem1" << endl;
            pom[this->br_igri] = g;
            cout << "problem2" << endl;
        } else {
            cout << "problem3" << endl;
            dynamic_cast<SubscriptionGame *>(&pom[this->br_igri])->operator=(*(dynamic_cast<SubscriptionGame *>(&g)));
            cout << "problem4" << endl;
        }
        this->br_igri++;

        delete[] this->kupeni_igri;
        this->kupeni_igri = pom;

        return *this;
    }

    int total_spent() {

        int vkupno = 0, pom;

        for (int i = 0; i < this->br_igri; i++) {

            if (this->kupeni_igri[i].isKupenaNaRasprodazba() == true) {
                vkupno = vkupno + (this->kupeni_igri[i].getCena() - ((this->kupeni_igri[i].getCena() / 100) * 30));
            } else vkupno = vkupno + this->kupeni_igri[i].getCena();


            //    -- &this->kupeni_igri[i] --  toa sho se naogja na adresava , probaj da najdesh i da mi vratish
            //    pokazuvac kon objekt od SubscriptonGame klasata

            if (dynamic_cast<SubscriptionGame *>(&this->kupeni_igri[i]) == nullptr) {
                // Ako vleze tuka, igrata e bez subscriptopn, vekje e presmetana cenata na igrata vo 'vkupno' vo prethodniot if
            } else {

                for (int j = dynamic_cast<SubscriptionGame *>(&this->kupeni_igri[i])->getGodinaKupuvanje();
                     j <= 2018; j++) {

                    for (int p = dynamic_cast<SubscriptionGame *>(&this->kupeni_igri[i])->getMesecKupuvanje();
                         p <= 12; p++) {

                        if (j == 2018 && p == 5) {
                            break;
                        }
                        vkupno = vkupno + dynamic_cast<SubscriptionGame *>(&this->kupeni_igri[i])->getPretplata();
                    }
                }
            }
        }
        return vkupno;
    }

    friend ostream &operator<<(ostream &os, const User &user) {

        os << "\nUser: " << user.username << endl;

        for (int i = 0; i < user.br_igri; i++) {

            if (dynamic_cast<SubscriptionGame *>(&user.kupeni_igri[i]) == nullptr) {
                os << "- tukaa" << user.kupeni_igri[i] << endl;
            } else os << "- " << dynamic_cast<SubscriptionGame *>(&user.kupeni_igri[i]) << endl;
        }
        return os;
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
