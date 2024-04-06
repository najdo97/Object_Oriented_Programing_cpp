
#include<iostream>
#include<cstring>
using namespace std;

class Patnik {

private:
    char ime[100];
    int tip_vagon;
    bool velosiped;

public:
    Patnik(){};

    Patnik(char *ime, int tip_vagon, bool velosiped)
    {
        strcpy(this->ime,ime);
        this->tip_vagon=tip_vagon;
        this->velosiped=velosiped;
    };

    Patnik(const Patnik& patnik)
    {
        strcpy(this->ime,patnik.ime);
        this->tip_vagon=patnik.tip_vagon;
        this->velosiped=patnik.velosiped;
    };

    ~Patnik(){};

    bool getVelosiped() const {
        return velosiped;
    }
    int getKlasa() const {
        return tip_vagon;
    }
    const char  *getIme()  {
        return ime;
    }

    friend std::ostream &operator<<(std::ostream &os, const Patnik &patnik)
    {
       os << patnik.ime <<" "<< patnik.tip_vagon<<" "<< patnik.velosiped;
       return os;
    }
};


class Voz{


    //Потоа да се креира клaса Voz во која се чува: крајна дестинација (низа од максимум 100 знаци), динамички алоцирана
    // низа од објекти од класата Patnik, како и број на елементи во низата (цел број), број на дозволени велосипеди (цел број).
private:
    char destinacija[100];
    Patnik *patnici;
    int br_patnici;
    int max_velosipedi;

public:
    Voz(){};

    Voz(char *destinacija, int brVelosipedi)
    {
        strcpy(this->destinacija,destinacija);
        this->max_velosipedi=brVelosipedi;

        this->patnici= nullptr;
        this->br_patnici=0;
    }

    Voz(char *destinacija, Patnik *patnici, int brPatnici, int brVelosipedi)
    {
     strcpy(this->destinacija,destinacija);

     this->patnici=new Patnik[this->br_patnici];
     for(int i=0 ; i <br_patnici; i++){
         this->patnici[i]= Patnik(patnici[i]);  // todo - copy constructor treba
     }
     this->br_patnici=brPatnici;
     this->max_velosipedi=brVelosipedi;
    }
    ~Voz()
    {
        delete[] patnici;
    };

//Оператор += – за додавање нов патник во воз. Патник со велосипед ќе може да се качи во воз само ако возот го дозволува тоа.

    Voz& operator+=(const Patnik& patnik){

        Patnik *pom=new Patnik[this->br_patnici+1];
        for(int i=0;i<this->br_patnici;i++)
        {
            pom[i]=Patnik(this->patnici[i]);
        }
        pom[this->br_patnici]=patnik;
        this->br_patnici++;

        delete [] this->patnici;
        this->patnici=new Patnik[this->br_patnici];
        for(int i=0;i<this->br_patnici;i++)
        {
            this->patnici[i]=Patnik(pom[i]);
        }

        delete [] pom;

    return *this;
    }

//Оператор << - за печатење на крајната дестинација до која вози и листата на патници

//Logikata ne mi e jasna, vo kaceni patnici treba samo kacenite da se kacat a ne site patnici!

    friend std::ostream& operator<<(std::ostream& os, const Voz& voz){
        Patnik *kaceni_patnici=new Patnik[voz.br_patnici];

        for(int i =0; i<voz.br_patnici && voz.patnici[i].getKlasa()==1;i++){
            if(voz.patnici[i].getVelosiped()==true){
                if(i>voz.max_velosipedi){
                    continue;
                }else kaceni_patnici[i]= Patnik(voz.patnici[i]);
            }else kaceni_patnici[i]= Patnik(voz.patnici[i]);

        }

        for(int i =0; i<voz.br_patnici && voz.patnici[i].getKlasa()==2;i++){
            if(voz.patnici[i].getVelosiped()==true){
                if(i>voz.max_velosipedi){
                    continue;
                }else kaceni_patnici[i]= Patnik(voz.patnici[i]);
            }else kaceni_patnici[i]= Patnik(voz.patnici[i]);
        }




        os << voz.destinacija<< endl;

        for(int i= 0 ; i<voz.br_patnici;i++)
        {
            os << kaceni_patnici[i].getIme()<< endl;
            os << kaceni_patnici[i].getKlasa()<< endl;
            os << kaceni_patnici[i].getVelosiped()<< endl;

        }
        return os;
    }

//Функција со потпис: patniciNemaMesto().
    void patniciNemaMesto(){

        Patnik *kaceni_patnici=new Patnik[this->br_patnici];

        int ostaveni_prva=0, ostaveni_vtora=0;

        for(int i =0; i<this->br_patnici && this->patnici[i].getKlasa()==1;i++){
            if(this->patnici[i].getVelosiped()==true){
                if(i>this->max_velosipedi){
                    ostaveni_prva++;
                    continue;
                    }
                }
            kaceni_patnici[i]= Patnik(this->patnici[i]);
        }

        for(int i =0; i<this->br_patnici && this->patnici[i].getKlasa()==2;i++){
            if(this->patnici[i].getVelosiped()==true){
                if(i>this->max_velosipedi){
                ostaveni_vtora++;
                    continue;
                }
            }
            kaceni_patnici[i]= Patnik(this->patnici[i]);
        }

        cout<< "Brojot na patnici od 1-va klasa koi ostanale bez mesto e: " <<ostaveni_prva << endl;

        cout<< "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: " <<ostaveni_prva << endl;
    }



// Со оваа функција се пресметува вкупниот број на патници (од 1-ва класа и 2-ра класа) за кои нема место да влезат во возот со велосипед.
// Притоа треба да се внимава дека во пресметувањето на вкупниот број патници со велосипеди кои ќе влезат во возот
// прво треба да се земат предвид патниците од 1-ва класа, а потоа се дозволува да влегуваат патниците од 2-ра класа се додека не се достигне
// максималниот број на дозволени велосипеди во возот.
// На крај се печати бројот на патници со велосипеди кои остануваат (не влегуваат во возот) од 1-ва класа, а потоа од 2-ра класа.

};


int main()
{
    Patnik p;
    char ime[100], destinacija[100];
    int n;
    bool velosiped;
    int klasa;
    int maxv;
    cin >> destinacija >> maxv;
    cin >> n;
    Voz v(destinacija, maxv);
    //cout<<v<<endl;
    for (int i = 0; i < n; i++){
        cin >> ime >> klasa >> velosiped;
        Patnik p(ime, klasa, velosiped);
        //cout<<p<<endl;
        v += p;
    }
    cout << v;
    v.patniciNemaMesto();

    return 0;
}
