#include <iostream>
#include <cstring>

using namespace std;


struct Laptop {

    char proizvoditel[100];
    float monitor_size;
    bool isTouch;
    int cena;

    Laptop() {

        strcpy(this->proizvoditel, "NaN");
        this->monitor_size = 0.0;
        this->isTouch = false;
        this->cena = 0;

    };

    Laptop(char *proizvoditel, float monitor_size, bool isTouch, int cena) {

        strcpy(this->proizvoditel, proizvoditel);
        this->monitor_size = monitor_size;
        this->isTouch = isTouch;
        this->cena = cena;

    };

    Laptop(const Laptop &l) {

        strcpy(this->proizvoditel, l.proizvoditel);
        this->monitor_size = l.monitor_size;
        this->isTouch = l.isTouch;
        this->cena = l.cena;

    };

    Laptop &operator=(const Laptop &l) {

        strcpy(this->proizvoditel, l.proizvoditel);
        this->monitor_size = l.monitor_size;
        this->isTouch = l.isTouch;
        this->cena = l.cena;
        return *this;
    };

};

struct ITStore {
    char store_name[100];
    char store_location[100];
    Laptop dostapni_laptopi[100];
    int br_laptopi;

    ITStore() {

        strcpy(this->store_name, "NaN");
        strcpy(this->store_location, "NaN");
        for (int i = 0; i < 100; i++) {
            this->dostapni_laptopi[i] = Laptop();
        }
        this->br_laptopi = 0;
    };

    ITStore(char *store_name, char *store_location, Laptop *dostapni_laptopi, int br_laptopi) {

        strcpy(this->store_name, store_name);
        strcpy(this->store_location, store_location);

        this->br_laptopi = br_laptopi;

        for (int i = 0; i < br_laptopi; i++) {
            this->dostapni_laptopi[i] = dostapni_laptopi[i];
        }
    };


    ITStore(const ITStore &s) {

        strcpy(this->store_name, s.store_name);
        strcpy(this->store_location, s.store_location);

        this->br_laptopi = s.br_laptopi;

        for (int i = 0; i < s.br_laptopi; i++) {
            this->dostapni_laptopi[i] = s.dostapni_laptopi[i];
        }
    };

    ITStore &operator=(const ITStore &s) {

        strcpy(this->store_name, s.store_name);
        strcpy(this->store_location, s.store_location);

        this->br_laptopi = s.br_laptopi;

        for (int i = 0; i < s.br_laptopi; i++) {
            this->dostapni_laptopi[i] = s.dostapni_laptopi[i];
        }

        return *this;
    };

};

void print(ITStore prodavnica) {

    cout << prodavnica.store_name << " " << prodavnica.store_location << endl;

    for (int i = 0; i < prodavnica.br_laptopi; i++) {
        cout << prodavnica.dostapni_laptopi[i].proizvoditel << " " << prodavnica.dostapni_laptopi[i].monitor_size << " "
             << prodavnica.dostapni_laptopi[i].cena << endl;
    }
}

void najeftina_ponuda(ITStore *niza_prodavnici, int num) {

    char cheapest_store[100] = "NaN";
    char cheapest_store_location[100] = "NaN";
    int cheapest_price = 9999999;

    for (int j = 0; j < num; j++) {

        for (int i = 0; i < niza_prodavnici[j].br_laptopi; i++) {
            if ((niza_prodavnici[j].dostapni_laptopi[i].isTouch == true) &&
                (cheapest_price > niza_prodavnici[j].dostapni_laptopi[i].cena)) {

                strcpy(cheapest_store, niza_prodavnici[j].store_name);
                strcpy(cheapest_store_location, niza_prodavnici[j].store_location);

                cheapest_price = niza_prodavnici[j].dostapni_laptopi[i].cena;

            }
        }
    }

    cout << "Najeftina ponuda ima prodavnicata: \n" << cheapest_store << " " << cheapest_store_location << endl;
    cout << "Najniskata cena iznesuva: " << cheapest_price << endl;


}

int main() {
    ITStore s[100];
    int n;
    cin >> n; //broj na IT prodavnici

    char store_name[100];
    char store_location[100];
    int br_laptopi;

    char proizvoditel[100];
    float monitor_size;
    bool isTouch;
    int cena;

    ITStore *lista_prodavnici = new ITStore[n];


    // Programata pagja koa ke se vnese vorata prodavnica

    for (int i = 0; i < n; i++) {

        cin >> store_name;

        cin >> store_location;  // ovdeka pagja vtoriot pat

        cin >> br_laptopi;

        ITStore pom_prodavnica;

        strcpy(pom_prodavnica.store_name, store_name);
        strcpy(pom_prodavnica.store_location, store_location);
        pom_prodavnica.br_laptopi = br_laptopi;

        for (int j = 0; j < br_laptopi; j++) {
            cin >> proizvoditel;
            cin >> monitor_size;
            cin >> isTouch;
            cin >> cena;
            Laptop pom = Laptop(proizvoditel, monitor_size, isTouch, cena);
            //  cout<<"test"<<endl;
            pom_prodavnica.dostapni_laptopi[j] = pom;

        }


        lista_prodavnici[i] = pom_prodavnica;
    }

    //pecatenje na site prodavnici

    for (int i = 0; i < n; i++) {
        print(lista_prodavnici[i]);
    }


    //povik na glavnata metoda
    najeftina_ponuda(lista_prodavnici, n);

    return 0;
}