#include<iostream>
#include <cstring>

using namespace std;

struct Voz {

    char relacija[50];
    double br_km;
    int br_patnici;

};

struct ZeleznickaStanica {
    char grad[20];
    Voz niza_vozovi[30];
    int br_vozovi;

};

void najkratkaRelacija(ZeleznickaStanica *zs, int n, char *grad) {

    double min;
    int min_i = 0.0, min_j = 0.0;


    for (int i = 0; i < n; i++) {
        if (strcmp(zs[i].grad, grad) == 0) {
            min = zs[i].niza_vozovi[0].br_km;

            for (int j = 0; j < zs[i].br_vozovi; j++) {
                if (min >= zs[i].niza_vozovi[j].br_km) {

                    min = zs[i].niza_vozovi[j].br_km;
                    min_i = i;
                    min_j = j;

                }
            }
        }
    }
    cout << "Najkratka relacija: " << zs[min_i].niza_vozovi[min_j].relacija << " ("<< zs[min_i].niza_vozovi[min_j].br_km << " km)" << endl;
    /*
        for (int i = 0; i < n; i++) {
        if (strcmp(zs[i].grad, grad) == 0) {
            }
        }
    */
}

int main() {

    int n;
    cin >> n; //se cita brojot na zelezlnichki stanici

    ZeleznickaStanica zStanica[100];
    for (int i = 0; i < n; i++) {
        cin >> zStanica[i].grad >> zStanica[i].br_vozovi;

        for (int j = 0; j < zStanica[i].br_vozovi; j++) {
            cin >> zStanica[i].niza_vozovi[j].relacija >> zStanica[i].niza_vozovi[j].br_km
                >> zStanica[i].niza_vozovi[j].br_patnici;
        }
    }

    char grad[25];
    cin >> grad;

    najkratkaRelacija(zStanica, n, grad);
    return 0;
}
