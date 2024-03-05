#include <iostream>
#include <cstring>
using namespace std;

class Locuinte
{
protected:
    string Localitate;
    string Strada;

public:
    Locuinte(string _localitate, string _strada)
    {
        Localitate = _localitate;
        Strada = _strada;
    }
};

class Case : public Locuinte
{
protected:
    string tip;
    int suprafata;
    int numar_camere;
    Case *prim;
    Case *urm;

public:
    Case(string _localitate, string _strada, string _tip, int _suprafata, int _numar_camere) : Locuinte(_localitate, _strada)
    {
        prim = NULL;
        urm = NULL;
        tip = _tip;
        suprafata = _suprafata;
        numar_camere = _numar_camere;
    }

    void adaugare();
    void afisare();
    void cautare();
    void stergere();
};

void Case ::adaugare()
{
    string localitate;
    string strada;
    string tip;
    int suprafata;
    int numar_camere;

    cout << "----------Case----------" << endl;
    cout << "Dati localitatea: ";
    cin >> localitate;
    cout << "Dati strada: ";
    cin >> strada;
    cout << "Dati tipul: ";
    cin >> tip;
    cout << "Dati suprafata: ";
    cin >> suprafata;
    cout << "Dati numarul de camere: ";
    cin >> numar_camere;
    Case *p = new Case(localitate, strada, tip, suprafata, numar_camere);
    p->urm = prim;
    prim = p;
}

void Case ::afisare()
{
    Case *p = prim;
    while (p != NULL)
    {
        cout << "----------Case----------" << endl;
        cout << "Localitatea: " << p->Localitate << endl;
        cout << "Strada: " << p->Strada << endl;
        cout << "Tipul: " << p->tip << endl;
        cout << "Suprafata: " << p->suprafata << endl;
        cout << "Numarul de camere: " << p->numar_camere << endl;
        cout << "-----------------------" << endl;
        p = p->urm;
    }
}

void Case ::cautare()
{
    int poz, i = 0;
    cout << "Dati pozitia elementului: ";
    cin >> poz;

    while (prim != NULL && i < poz)
    {
        prim = prim->urm;
        i++;
    }

    if (i == poz)
        afisare();
}

void Case ::stergere()
{
    Case *p = prim;
    prim = prim->urm;
    delete p;
}

class Apartament : public Case
{
private:
    int etaj;
    Apartament *prim;
    Apartament *urm;

public:
    Apartament(string _localitate, string _strada, string _tip, int _suprafata, int _numar_camere, int _etaj) : Case(_localitate, _strada, _tip, _suprafata, _numar_camere)
    {
        prim = NULL;
        urm = NULL;
        etaj = _etaj;
    }

    void adaugare();
    void afisare();
    void cautare();
    void stergere();
};

void Apartament ::adaugare()
{
    string localitate;
    string strada;
    string tip;
    int suprafata;
    int numar_camere;
    int etaj;

    cout << "----------Apartament----------" << endl;
    cout << "Dati localitatea: ";
    cin >> localitate;
    cout << "Dati strada: ";
    cin >> strada;
    cout << "Dati tipul: ";
    cin >> tip;
    cout << "Dati suprafata: ";
    cin >> suprafata;
    cout << "Dati numarul de camere: ";
    cin >> numar_camere;
    cout << "Dati etajul: ";
    cin >> etaj;
    Apartament *q = new Apartament(localitate, strada, tip, suprafata, numar_camere, etaj);
    q->urm = prim;
    prim = q;
}

void Apartament ::afisare()
{
    Apartament *q = prim;
    while (q != NULL)
    {
        cout << "----------Apartament----------" << endl;
        cout << "Localitatea: " << q->Localitate << endl;
        cout << "Strada: " << q->Strada << endl;
        cout << "Tipul: " << q->tip << endl;
        cout << "Suprafata: " << q->suprafata << endl;
        cout << "Numarul de camere: " << q->numar_camere << endl;
        cout << "Etajul: " << q->etaj << endl;
        cout << "-----------------------" << endl;
        q = q->urm;
    }
}

void Apartament ::cautare()
{
    int poz, i = 0;
    cout << "Dati pozitia elementului: ";
    cin >> poz;

    while (prim != NULL && i < poz)
    {
        prim = prim->urm;
        i++;
    }

    if (i == poz)
        afisare();
}

void Apartament ::stergere()
{
    Apartament *q = prim;
    prim = prim->urm;
    delete q;
}

int main()
{
    int opt;
    int poz;
    Case *p = new Case(" ", " ", " ", 0, 0);
    Apartament *q = new Apartament(" ", " ", " ", 0, 0, 0);

    while (true)
    {
        cout << "1. Adaugarea unei Case/Apartament." << endl;
        cout << "2. Afisarea unei Case/Apartament." << endl;
        cout << "3. Stergerea unei Case/Apartament." << endl;
        cout << "4. Cautarea unei Case/Apartament." << endl;
        cout << "5. Iesire." << endl;
        cout << "Optiunea dvs este: ";
        cin >> opt;
        switch (opt)
        {
        case 1:
            p->adaugare();
            // q->adaugare();
            break;

        case 2:
            p->afisare();
            // q->afisare();
            break;

        case 3:
            p->stergere();
            p->afisare();
            // q->stergere();
            // q->afisare();
            break;

        case 4:
            p->cautare();
            // q->cautare();
            break;

        case 5:
            exit(0);
            break;
        }
    }
    return 0;
}