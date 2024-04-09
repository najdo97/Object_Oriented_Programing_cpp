// zadacata se bara da se reshi vo C

#include <stdio.h>

struct Vozenje {
    char ime[100];
    int traenje;
    float cena;
    int daliPopust; //  1-da , 0-ne
};

typedef struct Vozenje Vozenje;

struct ZabavenPark {
    char ime[100];
    char lokacija[100];
    struct Vozenje niza[100];
    int n;
};
typedef struct ZabavenPark ZabavenPark;


void pecati(struct ZabavenPark *park, int n) {

    int i = 0;

    for (; i < n; i++) {
        printf("%s %s \n", park[i].ime, park[i].lokacija);

        for (int j = 0; j < park[i].n; j++) {
            printf("%s %d %.2f \n", park[i].niza[j].ime, park[i].niza[j].traenje, park[i].niza[j].cena);
        }
    }
}

void najdobar_park(struct ZabavenPark *park, int n) {

    int max_popusti = 0, brojac, max_i = 0, max_traenje = 0, traenje;



    for (int i = 0; i < n; i++) {
        brojac = 0;
        for (int j = 0; j < park[i].n; j++) {
            if (park[i].niza[j].daliPopust == 1) {
                brojac++;
            }
        }
        if (brojac > max_popusti) {
            max_popusti = brojac;
            max_i = i;
        } else if (brojac == max_popusti) {

            for (int p = 0; p < n; p++) {

                traenje=0;
                for (int j = 0; j < park[p].n; j++) {
                    
                    traenje = traenje + park[p].niza[j].traenje;
                }
                if (max_traenje < traenje) {


                    max_traenje = traenje;
                    max_i = p;
                }
            }
        }
    }

    printf("Najdobar park: %s %s", park[max_i].ime, park[max_i].lokacija);
}


int main() {
    int i, j, n, broj;
    //kreiraj niza od maksimum 100 zabavni parkovi
    ZabavenPark ff[100];
    scanf("%d", &n);
    //citanje na podatocite
    for (i = 0; i < n; i++) {
        //ime na festivalot
        scanf("%s", ff[i].ime);
        //mesto
        scanf("%s", ff[i].lokacija);
        //broj na filmovi
        scanf("%d", &ff[i].n);

        for (j = 0; j < ff[i].n; j++) {
            scanf("%s", ff[i].niza[j].ime);            /* Ime na filmot */
            scanf("%d", &ff[i].niza[j].traenje);        /* Vremetraenje   */
            scanf("%f", &ff[i].niza[j].cena);    /* Cena */
            scanf("%d", &ff[i].niza[j].daliPopust);    /* Popust */

        }


    }
    pecati(ff, n);
    najdobar_park(ff, n);

    return 0;
}
