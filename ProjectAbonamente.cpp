#include <iostream>
#include <fstream>
#include <list>
#include <cstring>
using namespace std;

class Abonament
{
protected:
    string dataCreare;
    string nume;
    string cnp;
    float pret;

public:
    Abonament(string _dataCreare, string _nume, string _cnp, float _pret)
    {
        dataCreare = _dataCreare;
        nume = _nume;
        cnp = _cnp;
        pret = _pret;
    }

    friend class SalaSport;
    virtual void afisare() = 0;
    virtual string getType() = 0;
    virtual ~Abonament() {}
};

class AbonamentSilver : public Abonament
{
public:
    string intervalOrar;

    AbonamentSilver(string _dataCreare, string _nume, string _cnp, float _pret, string _intervalOrar) : Abonament(_dataCreare, _nume, _cnp, _pret)
    {
        intervalOrar = _intervalOrar;
    }

    void afisare() override
    {
        cout << "Abonament Silver - " << nume << " (" << cnp << ")\n";
        cout << "Data creare: " << dataCreare << endl;
        cout << "Pret: " << pret << " RON\n";
        cout << "Interval orar: " << intervalOrar << "\n";
    }
    string getType()
    {
        return "Silver";
    }
};

class AbonamentPremium : public Abonament
{
public:
    int oreAerobic;

    AbonamentPremium(string _dataCreare, string _nume, string _cnp, float _pret, int _oreAerobic) : Abonament(_dataCreare, _nume, _cnp, _pret)
    {
        oreAerobic = _oreAerobic;
    }

    void afisare() override
    {
        cout << "Abonament Premium - " << nume << " (" << cnp << ")\n";
        cout << "Data creare: " << dataCreare << endl;
        cout << "Pret: " << pret << " RON\n";
        cout << "Ore aerobic ramase: " << oreAerobic << "\n";
    }
    string getType()
    {
        return "Premium";
    }
};

class SalaSport
{
private:
    list<Abonament *> abonamente;

public:
    void inregistrareAbonament()
    {
        int tip;
        cout << "Selectati tipul de abonament (1 - Silver, 2 - Premium): ";
        cin >> tip;

        string dataCreare, nume, cnp;
        float pret;
        int oreAerobic;
        string intervalOrar;

        cout << "Data creare: ";
        cin >> dataCreare;

        cout << "Nume: ";
        cin >> nume;

        cout << "CNP: ";
        cin >> cnp;

        cout << "Pret: ";
        cin >> pret;

        if (tip == 1)
        {
            cout << "Interval orar (8-14, 12-16, 14-18): ";
            cin >> intervalOrar;
            abonamente.push_back(new AbonamentSilver(dataCreare, nume, cnp, pret, intervalOrar));
        }
        else if (tip == 2)
        {
            oreAerobic = 6; // Un abonament Premium are initial 6 ore de aerobic
            abonamente.push_back(new AbonamentPremium(dataCreare, nume, cnp, pret, oreAerobic));
        }
        else
        {
            cout << "Tip de abonament invalid.\n";
        }
    }

    void afisareAbonamente()
    {
        for (const auto &abonament : abonamente)
        {
            abonament->afisare();
            cout << "-----------------------\n";
        }
    }

    void cautareDupaNume()
    {
        string numeCautat;
        cout << "Introduceti numele pentru cautare: ";
        cin >> numeCautat;

        for (const auto &abonament : abonamente)
        {
            if (abonament->nume == numeCautat)
            {
                abonament->afisare();
                return;
            }
        }

        cout << "Numele " << numeCautat << " nu a fost gasit.\n";
    }

    void stergereDupaNume()
    {
        string numeCautat;
        cout << "Introduceti numele pentru cautare: ";
        cin >> numeCautat;

        for (auto it = abonamente.begin(); it != abonamente.end(); it++)
        {
            if ((*it)->nume == numeCautat)
            {
                delete *it;
                it = abonamente.erase(it);

                cout << "Abonamentul a fost sters cu succes.\n";
                return;
            }
        }
        cout << "Nu s-a gasit niciun abonament cu numele specificat.\n";
    }

    void afisareSilverIntervalOrar1216()
    {
        for (const auto &abonament : abonamente)
        {
            if (dynamic_cast<AbonamentSilver *>(abonament)->intervalOrar == "12-16")
            {
                dynamic_cast<AbonamentSilver *>(abonament)->afisare();
                cout << "-----------------------\n";
            }
        }
    }

    void contorizareOraAerobic()
    {
        string nume;
        cout << "Introduceti numele abonamentului Premium pentru contorizare ora aerobic: ";
        cin >> nume;

        for (const auto abonament : abonamente)
        {
            if (dynamic_cast<AbonamentPremium *>(abonament)->nume == nume)
            {
                if (dynamic_cast<AbonamentPremium *>(abonament)->oreAerobic > 0)
                {
                    dynamic_cast<AbonamentPremium *>(abonament)->oreAerobic--;
                    cout << "Ora aerobic contorizata. Ore ramase: " << dynamic_cast<AbonamentPremium *>(abonament)->oreAerobic << "\n";
                }
                else
                {
                    cout << "Abonamentul " << nume << " nu mai are ore de aerobic disponibile.\n";
                }
                return;
            }
        }
        cout << "Abonamentul " << nume << " nu a fost gasit sau nu este de tip Premium.\n";
    }

    void bilantVanzari()
    {
        int totalSilver = 0, totalPremium = 0;
        float sumaTotala = 0.0;

        for (const auto &abonament : abonamente)
        {
            if (abonament->getType() == "Silver")
            {
                totalSilver++;
            }
            else if (abonament->getType() == "Premium")
            {
                totalPremium++;
            }
            sumaTotala += abonament->pret;
        }

        ofstream fout("bilant.txt");
        fout << "Numar total abonamente Silver: " << totalSilver << "\n";
        fout << "Numar total abonamente Premium: " << totalPremium << "\n";
        fout << "Suma totala incasata: " << sumaTotala << " RON\n";
        fout.close();

        cout << "Bilantul a fost scris in fisierul 'bilant.txt'.\n";
    }
};

int main()
{
    SalaSport sala;

    int optiune;
    do
    {
        cout << "\nMeniu:\n";
        cout << "0. Iesire\n";
        cout << "1. Inregistrare abonament\n";
        cout << "2. Afisare abonamente inregistrate\n";
        cout << "3. Cautare abonament dupa nume\n";
        cout << "4. Afisare abonamente Silver cu interval orar 12-16\n";
        cout << "5. Contorizare ora aerobic abonament Premium\n";
        cout << "6. Bilant vanzari\n";
        cout << "7. Stergere dupa nume\n";
        cout << "Alegeti o optiune: ";
        cin >> optiune;

        switch (optiune)
        {
        case 1:
            sala.inregistrareAbonament();
            break;
        case 2:
            sala.afisareAbonamente();
            break;
        case 3:
            sala.cautareDupaNume();
            break;
        case 4:
            sala.afisareSilverIntervalOrar1216();
            break;
        case 5:
            sala.contorizareOraAerobic();
            break;
        case 6:
            sala.bilantVanzari();
            break;
        case 7:
            sala.stergereDupaNume();
            break;
        case 0:
            cout << "La revedere!\n";
            break;
        default:
            cout << "Optiune invalida. Va rugam selectati o optiune valida.\n";
            break;
        }
    } while (optiune != 0);
    return 0;
}