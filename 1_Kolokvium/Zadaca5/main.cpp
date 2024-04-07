#include <iostream>
#include <cstring>
using namespace std;

class Gitara{

private:
    char tip[40];
    char seriski_broj[25];
    int godina_proizvodstvo;
    float nabavna_cena;

public:
    Gitara(){};     // so ovoj konstruktor se kreira objekt, mozno e da treba da se inicijaliziraat promenlivite

    Gitara (char *tip, char *seriski_broj, int godina_proizvodstvo, float nabavna_cena)
    {
        strcpy(this->tip,tip);
        strcpy(this->seriski_broj,seriski_broj);

        this->godina_proizvodstvo=godina_proizvodstvo;
        this->nabavna_cena=nabavna_cena;
    };

    ~Gitara(){};


    const char *getTip()
{
        return this->tip;
}
    const char *getSeriski(){
        return this->seriski_broj;
    }
    const int getGodina(){
        return this->godina_proizvodstvo;
    }
    const float getNabavna()
    {
        return this->nabavna_cena;
    }


    bool daliIsti (Gitara pom){
        if(strcmp(this->seriski_broj,pom.getSeriski()) == 0)        // this should work
        {
            return true;
        }else return false;
    }

    void pecati()
    {
        cout<<this->seriski_broj <<" "<< this->tip <<" "<< this->nabavna_cena << endl;
    }

};



int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, godina;
    float cena;
    char seriski[50],tip[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Gitara ======" << endl;
        cin>>tip;
        cin>>seriski;
        cin >> godina;
        cin >> cena;
        Gitara g(tip,seriski, godina,cena);
        cout<<g.getTip()<<endl;
        cout<<g.getSeriski()<<endl;
        cout<<g.getGodina()<<endl;
        cout<<g.getNabavna()<<endl;
    } else if(testCase == 2){
        cout << "===== Testiranje na klasata Magacin so metodot print() ======" << endl;
        Magacin kb("Magacin1","Lokacija1");
        kb.pecati(false);
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na klasata Magacin so metodot dodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2005);
        cin>>n;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;
            Gitara g(tip,seriski, godina,cena);
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
    }

    else if(testCase == 4) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2012);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(false);
        kb.prodadi(brisi);
        kb.pecati(false);
    }
    else if(testCase == 5) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() i pecati(true) ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        Magacin kb3;
        kb3=kb;
        kb3.pecati(true);
    }
    else if(testCase ==6)
    {
        cout << "===== Testiranje na klasata Magacin so metodot vrednost()======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            kb.dodadi(g);
        }
        cout<<kb.vrednost()<<endl;
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        cout<<kb.vrednost();
        Magacin kb3;
        kb3=kb;
    }
    return 0;
}
