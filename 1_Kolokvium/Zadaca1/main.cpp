#include <iostream>
#include <cstring>
using namespace std;


enum tip{pop,rap,rok};

class Pesna{

private:
    char *name;
    int length;
    tip tip_pesna;

public:
    Pesna(){};

    Pesna(char * ime,int dolzina, int vid){

        name=new char[strlen(ime)+1];
        strcpy(name,ime);

        length=dolzina;
        tip_pesna=(tip)vid;
    }

    // todo - nekako destruktorov pravi problem na kompajlerot
    /*
     ~Pesna()
        {
            delete[]name;
        };
    */

    void pecati(){
        cout<<"\""<<this->name<<"\""<<"-"<<this->length<<"min"<<endl;
    };

    int getLength(){
        return this->length;
    }
    tip getTip()
    {
        return this->tip_pesna;
    }
};

class CD{

private:
    Pesna niza_pesni[10];
    int br_pesni;
    int max_vremetraenje;

public:

    CD(){};

    CD(Pesna *niza_pesni, int br_pesni, int max_vremetraenje){

        for(int i=0; i<br_pesni && i<10;i++)
        {
            this->niza_pesni[i]=niza_pesni[i];
        }
        this->br_pesni=br_pesni;
        this->max_vremetraenje=max_vremetraenje;
    }
    CD(int max_vremetraenje){

        for(int i=0;i<10;i++)
        {
            this->niza_pesni[i]=Pesna();
        }
        this->br_pesni=0;
        this->max_vremetraenje=max_vremetraenje;
    }

//izmena
    ~CD(){};


    void dodadiPesna(Pesna p){

        int current_Length=0;

        for(int i=0; i<this->br_pesni;i++)
        {
            current_Length  =   current_Length  +   this->niza_pesni[i].getLength();
        }

        if( (current_Length+p.getLength()   <   this->max_vremetraenje)    &&  (this->br_pesni<10) )
        {
            this->niza_pesni[br_pesni]=p;
            this->br_pesni++;
        }

    }

    void pecatiPesniPoTip(tip t){

        for(int i=0;i<10;i++)
        {
            if(this->niza_pesni[i].getTip() == t)
            {
                this->niza_pesni[i].pecati();
            }
        }
    }

    int getBroj(){

        return this->br_pesni;
    }

    Pesna getPesna(int i)
    {
        return this->niza_pesni[i];
    }


};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, minuti, kojtip;
    char ime[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
        p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<n; i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<omileno.getBroj(); i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }

    return 0;
}