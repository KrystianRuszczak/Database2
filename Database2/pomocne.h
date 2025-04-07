#ifndef  Pomocne_h
#define Pomocne_h

#include <iostream>
#include <functional>
#include <string>
#include <cstdlib>

//#include <windows.h>
//#include <conio.h>

#include <fstream>

using std::string;

using std::cout;
using std::cin;
using std::endl;
using std::function;

inline bool czy_kontynuowac()
{
    bool stop2 = true;
    do {
        cin.clear();
        switch (char kont; cin >> kont, kont)
        {
        case 'Y':
        case 'y':
            cout << "\n";
            stop2 = false;
            return true;
        case 'N':
        case 'n':
            stop2 = false;
            return false;
        default:
            cout << "Wprowadz prawidlowe dane: Y lub N\n";
            stop2 = true;
            break;
        }
    } while (stop2 == true);
}

inline void opcja(const function<void()>& funkcja)
{
    do
    {
        funkcja();
        cout << "\nCzy chcesz kontynuowac proces? [Y/N]\n";
    } while (czy_kontynuowac());
}

/*
inline void wczytywanie(int czas)
{
    string trzy_k = "...";
    for (int i = 0; i < 3; i++)
    {
        cout << "Wczytywanie";
        for (int i = 0; i < 3; i++)
        {
            Sleep(czas);
            cout << trzy_k[i];
        }
        Sleep(czas);
        system("cls");
    }
}
*/

inline void czy_cos_zrobic(const function<void()>& funkc, string pytanie)
{
    bool stop_BD = true;
    do
    {
        cout << pytanie;
        switch (char kont; cin >> kont, kont)
        {
        case 'Y':
        case 'y':
            stop_BD = false;
            system("cls");
            funkc();
            break;
        case 'N':
        case 'n':
            stop_BD = false;
            break;
        default:
            cout << "Wprowadz prawidlowe dane: Y lub N\n";
            stop_BD = true;
            break;
        }

    } while (stop_BD == true);
}

inline void czy_plik_istnieje(const string& file_name)
{
    std::ifstream sprawdzany_plik(file_name);

    if (!sprawdzany_plik.is_open())
    {
        cout << "Tworze nowy plik: ";
        std::ofstream nowy_plik(file_name);
        if (!nowy_plik.is_open())
        {
            cout << "Blad: Nie mozna otworzyc pliku " << file_name << " do zapisu.\n";
            perror("\nPowod");
            exit(1);
        }
        nowy_plik.close();
        return; // Nie ma co odczytywa�, wi�c ko�czymy funkcj�
    }
}

#endif // ! Pomocne_h