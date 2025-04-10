#ifndef  Adress_h
#define Adress_h

#include <iostream>

using std::string;
using std::istream;
using std::ostream;

class Adress
{
public:
    //Setters

    //Metoda ustawia nazw� ulicy
    void Set_ulica(string ulica);

    //Metoda ustawia numer domu
    void Set_nrdomu(int nrdomu);

    //Metoda ustawia nazw� kraju
    void Set_kraj(string kraj);

    //Metoda ustawia nazw� miejscowo�ci
    void Set_miejscowosc(string miejscowosc);

    //Getters

    //Metoda zwraca nazw� ulicy
    string Get_ulica() const;

    //Metoda zwraca numer domu
    int Get_nrdomu() const;

    //Metoda zwraca nazw� kraju
    string Get_kraj() const;

    //Metoda zwraca nazw� miejscowo�ci
    string Get_miejscowosc() const;

    friend ostream& operator << (ostream& aos, const Adress& o_aa);
    friend istream& operator >> (istream& ais, Adress& i_aa);

private:
    string a_ulica;
    int a_nrdomu;
    string a_kraj;
    string a_miejscowosc;
};

#endif // ! Adress_h
