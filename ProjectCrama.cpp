#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <sstream>
using namespace std;

class Vinuri
{
protected:
    string nume;
    float pret;
    string tip;
    int an_productie;

public:
    Vinuri(string n, float p, string t, int a)
    {
        nume = n;
        pret = p;
        tip = t;
        an_productie = a;
    }
    friend class Lista;
    static bool compare(const Vinuri *a, const Vinuri *b)
    {
        return a->nume < b->nume;
    }
    virtual void afisare() = 0;
    ~Vinuri() {}
};

class Nespumante : public Vinuri
{
private:
    enum Zahar
    {
        sec,
        demisec,
        demidulce,
        dulce
    };
    string zahar;

public:
    Nespumante(string n, float p, string t, int a, string z) : Vinuri(n, p, t, a)
    {
        zahar = z;
    }

    string getZahar()
    {
        return zahar;
    }

    void afisare() override
    {
        cout << "Nume: " << nume << endl;
        cout << "Pret: " << pret << endl;
        cout << "Tip: " << tip << endl;
        cout << "An productie: " << an_productie << endl;
        cout << "Zahar(sec, demisec, demidulce, dulce): " << zahar << endl;
    }
    friend ostream &operator<<(ostream &iesire, Nespumante *nespumante);
};

ostream &operator<<(ostream &iesire, Nespumante *nespumante)
{
    iesire << "Nume: " << nespumante->nume << " ";
    iesire << "Pret: " << nespumante->pret << " ";
    iesire << "Tip: " << nespumante->tip << " ";
    iesire << "An productie: " << nespumante->an_productie << " ";
    iesire << "Zahar(sec, demisec, demidulce, dulce): " << nespumante->zahar << endl;
    return iesire;
}

class Spumante : public Vinuri
{
private:
    enum Perlaj
    {
        intens,
        scazut
    };
    string perlaj;

public:
    Spumante(string n, float p, string t, int a, string per) : Vinuri(n, p, t, a)
    {
        perlaj = per;
    }

    string getPerlaj()
    {
        return perlaj;
    }

    void afisare() override
    {
        cout << "Nume: " << nume << endl;
        cout << "Pret: " << pret << endl;
        cout << "Tip: " << tip << endl;
        cout << "An productie: " << an_productie << endl;
        cout << "Perlaj(intens, scazut): " << perlaj << endl;
    }
    friend ostream &operator<<(ostream &iesire, Spumante *spumante);
};

ostream &operator<<(ostream &iesire, Spumante *spumante)
{
    iesire << "Nume: " << spumante->nume << " ";
    iesire << "Pret: " << spumante->pret << " ";
    iesire << "Tip: " << spumante->tip << " ";
    iesire << "An productie: " << spumante->an_productie << " ";
    iesire << "Perlaj(intens, scazut): " << spumante->perlaj << endl;
    return iesire;
}

class Lista
{
private:
    list<Vinuri *> vinuri;
    list<Vinuri *>::iterator it;

public:
    string nume;
    float pret;
    string tip;
    int an_productie;

    string zahar;

    string perlaj;

    int TipOptiune;

    void inserare()
    {
        ifstream fin("inserare.txt");
        while (!fin.is_open())
        {
            cout << "Fisierul nu s-a deschis!" << endl;
            return;
        }

        ofstream fout("afisare.txt");
        while (!fout.is_open())
        {
            fin.close();
            cout << "Fisierul nu s-a deschis!" << endl;
            return;
        }

        string line;
        while (getline(fin, line))
        {
            istringstream iss(line);
            while (iss >> TipOptiune >> nume >> pret >> tip >> an_productie >> zahar >> perlaj)
            {
                if (TipOptiune == 1)
                {
                    fout << nume << " " << pret << " " << tip << " " << an_productie << " " << zahar << endl;
                    vinuri.push_back(new Nespumante(nume, pret, tip, an_productie, zahar));
                }
                if (TipOptiune == 2)
                {
                    fout << nume << " " << pret << " " << tip << " " << an_productie << " " << perlaj << endl;
                    vinuri.push_back(new Spumante(nume, pret, tip, an_productie, perlaj));
                }
            }
        }
        cout << "Datele au fost salvate!" << endl;
        fin.close();
        fout.close();
    }

    void afisareVinuri()
    {
        for (it = vinuri.begin(); it != vinuri.end(); ++it)
        {
            Nespumante *n = dynamic_cast<Nespumante *>(*it);
            if (n)
                cout << n;
            else
            {
                Spumante *s = dynamic_cast<Spumante *>(*it);
                cout << s; // Testare cu supraincarcare de operatori
            }
        }
    }

    void cautare()
    {
        string perlajUtilizator;
        cout << "Introduceti vinul spumant dupa perlaj: ";
        cin >> perlajUtilizator;

        try
        {
            for (char c : perlajUtilizator) 
                if (!isalpha(c))           
                {
                    cout << "Eroare la string!" << endl;
                    throw perlajUtilizator;
                }

            for (it = vinuri.begin(); it != vinuri.end(); it++)
            {
                Spumante *spumante = dynamic_cast<Spumante *>(*it); 
                if (spumante && spumante->getPerlaj() == perlajUtilizator)
                {
                    spumante->afisare();
                    return;
                }
            }
            cout << "Nu s-a gasit vinul cu acest perlaj!" << endl;
        }
        catch (string)
        {
            cout << "Eroare!" << '\n';
        }
    }

    void vanzare()
    {
        string numeUtilizator;
        int anUtilizator;

        cout << "Introduceti numele vinului: ";
        cin >> numeUtilizator;

        cout << "Introduceti anul: ";
        cin >> anUtilizator;

        for (it = vinuri.begin(); it != vinuri.end(); ++it)
        {
            if ((*it)->an_productie == anUtilizator && (*it)->nume == numeUtilizator)
            {
                delete *it;
                it = vinuri.erase(it);

                cout << "S-a vandut vinul!" << endl;
                return;
            }
        }
        cout << "Nu s-a gasit niciun vin cu numele si anul de productie!" << endl;
    }

    void modificare()
    {
        float pretUtilizator;
        string numeUtilizator;

        cout << "Introduceti numele vinului: ";
        cin >> numeUtilizator;

        cout << "Introduceti noul pret: ";
        cin >> pretUtilizator;

        for (it = vinuri.begin(); it != vinuri.end(); ++it)
        {
            if ((*it)->nume == numeUtilizator)
            {
                (*it)->pret = pretUtilizator;
                cout << "Pretul a fost modificat!" << endl;
                return;
            }
        }
        cout << "Nu s-a gasit niciun vin cu acest nume!" << endl;
    }

    void sortare()
    {
        vinuri.sort(Vinuri::compare);
        for (it = vinuri.begin(); it != vinuri.end(); ++it)
            (*it)->afisare(); 
    }

    void profit()
    {
        float brut, net;
        for (it = vinuri.begin(); it != vinuri.end(); ++it)
        {
            brut = brut + (*it)->pret;
        }
        net = (float)(brut - 0.25 * brut);
        cout << "Profilu brut este: " << brut << endl;
        cout << "Profilu net este: " << net << endl;
    }
};

int main()
{
    Lista vinuri;
    int opt, opt1;

    do
    {
        cout << "0.Iesire" << endl;
        cout << "1.Inserare si afisare" << endl;
        cout << "2.Cautare dupa perlaj" << endl;
        cout << "3.Vanzare dupa nume si an" << endl;
        cout << "4.Modificare pret" << endl;
        cout << "5.Afisare profit net si brut" << endl;
        cout << "6.Sortare dupa nume" << endl;
        cout << "Introduceti optiunea: ";
        cin >> opt;
        switch (opt)
        {
        case 0:
            exit(0);
            break;

        case 1:
            cout << "1-Inserare, 2-Afisare:";
            cin >> opt1;
            if (opt1 == 1)
                vinuri.inserare();
            if (opt1 == 2)
                vinuri.afisareVinuri();
            break;

        case 2:
            vinuri.cautare();
            break;

        case 3:
            vinuri.vanzare();
            break;

        case 4:
            vinuri.modificare();
            break;

        case 5:
            vinuri.profit();
            break;

        case 6:
            vinuri.sortare();
            break;

        default:
            cout << "Optiune invalida!" << endl;
            break;
        }
    } while (opt != 0);

    return 0;
}