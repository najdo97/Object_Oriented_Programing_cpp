#include <iostream>
#include <cstring>

using namespace std;


class SMS {
private:
    float osnovna_cena;
    char target_broj[12];

    static float danok;
public:


    float getOsnovnaCena() const {
        return osnovna_cena;
    }

    const char *getTargetBroj() const {
        return target_broj;
    }

    SMS() {
        this->osnovna_cena = 0.0;
        strcpy(this->target_broj, "000");
    }

    SMS(char *target_broj, float osnovna_cena) {
        this->osnovna_cena = osnovna_cena;
        strcpy(this->target_broj, target_broj);
    }

    SMS(const SMS &sms) {
        this->osnovna_cena = sms.osnovna_cena;
        strcpy(this->target_broj, sms.target_broj);
    }

    SMS &operator=(const SMS &sms) {
        this->osnovna_cena = sms.osnovna_cena;
        strcpy(this->target_broj, sms.target_broj);

        return *this;
    }

    virtual float SMS_cena() {};

    friend ostream &operator<<(ostream &os, const SMS &sms) {
        os << "ne treba da se ispecati ova" << endl;
        return os;
    }
};

class RegularSMS : public SMS {

private:
    char *text;
    bool isRoamingUsed;

    static float stranstvo_danok;
public:

    static void set_rProcent(float stranstvoDanok) {
        stranstvo_danok = stranstvoDanok;
    }

    RegularSMS() : SMS() {
        this->text = nullptr;
        this->isRoamingUsed = false;
    }

    RegularSMS(char *target_broj, float osnovna_cena, char *text, bool isRoamingUsed) : SMS(target_broj, osnovna_cena) {
        this->text = new char[strlen(text) + 1];
        strcpy(this->text, text);

        this->isRoamingUsed = isRoamingUsed;
    }

    RegularSMS(const RegularSMS &r) : SMS(r) {
        this->text = new char[strlen(r.text) + 1];
        strcpy(this->text, r.text);

        this->isRoamingUsed = r.isRoamingUsed;
    }

    RegularSMS &operator=(const RegularSMS &r) {
        SMS::operator=(r);

        delete[]this->text;
        this->text = new char[strlen(r.text) + 1];
        strcpy(this->text, r.text);

        this->isRoamingUsed = r.isRoamingUsed;

        return *this;
    }


    float SMS_cena() {
        float nova_cena = 0.0;
        int br_poraki = 0;

        br_poraki = (int) strlen(this->text) / 160;

        if (br_poraki == 0) {
            if (this->isRoamingUsed == true) {
                nova_cena = this->getOsnovnaCena() + (this->getOsnovnaCena() * 3);
            } else {
                nova_cena = this->getOsnovnaCena() + (this->getOsnovnaCena() * 0.18);
            }
        } else {
            for (int i = 0; i < br_poraki; i++) {
                if (this->isRoamingUsed == true) {
                    nova_cena = this->getOsnovnaCena() + (this->getOsnovnaCena() * 3);
                } else {
                    nova_cena = this->getOsnovnaCena() + (this->getOsnovnaCena() * 0.18);
                }
            }
        }

        return nova_cena;
    }

    friend ostream &operator<<(ostream &os, RegularSMS &sms) {

        os << sms.getTargetBroj() << " " << sms.SMS_cena() << endl;
        return os;
    }


};

class SpecialSMS : public SMS {

private:
    bool isHumanitarna;

    static float specijalen_danok;
public:

    static void set_sProcent(float specijalenDanok) {
        specijalen_danok = specijalenDanok;
    }

    SpecialSMS() : SMS() {
        this->isHumanitarna = false;
    }

    SpecialSMS(char *target_broj, float osnovna_cena, bool isHumanitarna) : SMS(target_broj, osnovna_cena) {
        this->isHumanitarna = isHumanitarna;
    }

    SpecialSMS(const SpecialSMS &s) : SMS(s) {
        this->isHumanitarna = s.isHumanitarna;
    }

    SpecialSMS &operator=(const SpecialSMS &s) {
        SMS::operator=(s);
        this->isHumanitarna = s.isHumanitarna;

        return *this;
    }

    float SMS_cena() {
        float nova_cena = 0.0;

        if (this->isHumanitarna == true) {
            return this->getOsnovnaCena();
        } else {
            nova_cena = this->getOsnovnaCena() + (this->getOsnovnaCena() * 1.5);
        }
        return nova_cena;
    }


    friend ostream &operator<<(ostream &os, SpecialSMS &sms) {

        os << sms.getTargetBroj() << " " << sms.SMS_cena() << endl;
        return os;
    }
};

void vkupno_SMS(SMS **poraka, int n) {
    int regular_brojac = 0, special_brojac = 0;
    float regular_vkupno = 0.0, special_vkupno = 0.0;

    for (int i = 0; i < n; i++) {
        if (dynamic_cast<RegularSMS *>(poraka[i]) != nullptr) {
            regular_vkupno += dynamic_cast<RegularSMS *>(poraka[i])->SMS_cena();
            regular_brojac++;
        }
        if (dynamic_cast<SpecialSMS *>(poraka[i]) != nullptr) {
            special_vkupno += dynamic_cast<SpecialSMS *>(poraka[i])->SMS_cena();
            special_brojac++;
        }
    }

    cout << "Vkupno ima " << regular_brojac << " regularni SMS poraki i nivnata cena e: " << regular_vkupno << endl;

    cout << "Vkupno ima " << special_brojac << " specijalni SMS poraki i nivnata cena e: " << special_vkupno << endl;

}

float SMS::danok = 0.18;
float RegularSMS::stranstvo_danok = 3;
float SpecialSMS::specijalen_danok = 1.5;

int main() {

    char tel[20], msg[1000];
    float cena;
    float price;
    int p;
    bool roam, hum;
    SMS **sms;
    int n;
    int tip;

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "====== Testing RegularSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++) {
            cin >> tel;
            cin >> cena;
            cin.get();
            cin.getline(msg, 1000);
            cin >> roam;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new RegularSMS(tel, cena, msg, roam);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i < n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 2) {
        cout << "====== Testing SpecialSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++) {
            cin >> tel;
            cin >> cena;
            cin >> hum;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new SpecialSMS(tel, cena, hum);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i < n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 3) {
        cout << "====== Testing method vkupno_SMS() ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++) {

            cin >> tip;
            cin >> tel;
            cin >> cena;
            if (tip == 1) {

                cin.get();
                cin.getline(msg, 1000);
                cin >> roam;

                sms[i] = new RegularSMS(tel, cena, msg, roam);

            } else {
                cin >> hum;

                sms[i] = new SpecialSMS(tel, cena, hum);
            }
        }

        vkupno_SMS(sms, n);
        for (int i = 0; i < n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 4) {
        cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        sms1 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        cin >> p;
        RegularSMS::set_rProcent(p);
        sms2 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms2;

        delete sms1, sms2;
    }
    if (testCase == 5) {
        cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin >> hum;
        sms1 = new SpecialSMS(tel, cena, hum);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin >> hum;
        cin >> p;
        SpecialSMS::set_sProcent(p);
        sms2 = new SpecialSMS(tel, cena, hum);
        cout << *sms2;

        delete sms1, sms2;
    }

    return 0;
}
