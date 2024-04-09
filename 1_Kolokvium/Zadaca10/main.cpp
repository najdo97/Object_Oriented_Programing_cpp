#include <iostream>

using namespace std;

struct Igrac {
    char korisnickoIme[15];
    int nivo;
    int poeni;
};


struct KompjuterskaIgra {
    char ime[20];
    Igrac lista[30];
    int n;
};

void najdobarIgrac(KompjuterskaIgra *lista, int n) {
    int popularna_igra = 0, max_igraci = 0, max_poeni = 0, najdobar_igrac = 0, max_nivo = 0;

    for (int i = 0; i < n; i++) {
        if (max_igraci < lista[i].n) {
            max_igraci = lista[i].n;
            popularna_igra = i;
        }
    }


    max_poeni = lista[popularna_igra].lista[0].poeni;

    for (int i = 0; i < lista[popularna_igra].n; i++) {
        if (max_poeni < lista[popularna_igra].lista[i].poeni) {
            max_poeni = lista[popularna_igra].lista[i].poeni;
            najdobar_igrac = i;
        } else if (max_poeni == lista[popularna_igra].lista[i].poeni) {

            if (lista[popularna_igra].lista[najdobar_igrac].nivo < lista[popularna_igra].lista[i].nivo) {
                najdobar_igrac = i;
                //max_poeni=lista[popularna_igra].lista[i].poeni;
            }

        }

    }


    cout << "Najdobar igrac e igracot so korisnicko ime " << lista[popularna_igra].lista[najdobar_igrac].korisnickoIme << " koj ja igra igrata " << lista[popularna_igra].ime << endl;
}


int main() {
    int n, m;
    char ime[20];
    cin >> n;
    KompjuterskaIgra poleigri[100];
    for (int i = 0; i < n; i++) {
        KompjuterskaIgra nova;
        cin >> nova.ime >> nova.n;
        Igrac pole[30];
        for (int j = 0; j < nova.n; j++) {
            Igrac nov;
            cin >> nov.korisnickoIme >> nov.nivo >> nov.poeni;
            nova.lista[j] = nov;
        }
        poleigri[i] = nova;
    }

    najdobarIgrac(poleigri, n);
    return 0;
}