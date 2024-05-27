#include<iostream>
#include <cstring>

using namespace std;

struct Player {
    char korisnickoIme[15];
    int nivo;
    int poeni;

};

struct ComputerGame {
    char ime[20];
    Player lista[30];
    int n;


};

void bestPlayer(ComputerGame *array, int n) {


    int most_players = 0, idx = 0, idx_best = 0;
    for (int i = 0; i < n; i++) {
        if (most_players < array[i].n) {
            most_players = array[i].n;
            idx = i;
        }

    }


    for (int i = 0; i < array[idx].n; i++) {

        if (array[idx].lista[idx_best].poeni < array[idx].lista[i].poeni) {

            idx_best = i;
        }
    }

    for (int i = 0; i < array[idx].n; i++) {
        if (array[idx].lista[idx_best].poeni == array[idx].lista[i].poeni) {

            if (array[idx].lista[idx_best].nivo < array[idx].lista[i].nivo) {
                idx_best = i;
            }
        }
    }

    cout << "Najdobar igrac e igracot so korisnicko ime " << array[idx].lista[idx_best].korisnickoIme << " koj ja igra igrata " << array[idx].ime << endl;
}


int main() {
    int n, m;
    char ime[20];
    cin >> n;
    //create an array of max 100 computer games;
    ComputerGame poleigri[100];
    for (int i = 0; i < n; i++) {
        ComputerGame nova;
        cin >> nova.ime >> nova.n;
        Player pole[30];
        for (int j = 0; j < nova.n; j++) {
            Player nov;
            cin >> nov.korisnickoIme >> nov.nivo >> nov.poeni;
            nova.lista[j] = nov;
        }
        poleigri[i] = nova;
    }

    bestPlayer(poleigri, n);
    return 0;
}
