#include <iostream>
#include "Adress.h"
#include <string>

using std::string;
using std::cout;
using std::cin;
using std::endl;


using std::istream;
using std::ostream;


void Adress::Set_ulica(string ulica)
{
	a_ulica = ulica;
}

void Adress::Set_nrdomu(int nrdomu)
{
	a_nrdomu = nrdomu;
}

void Adress::Set_kraj(string kraj)
{
	a_kraj = kraj;
}

void Adress::Set_miejscowosc(string miejscowosc)
{
    a_miejscowosc = miejscowosc;
}

string Adress::Get_ulica() const
{
	return a_ulica;
}

int Adress::Get_nrdomu() const
{
	return a_nrdomu;
}

string Adress::Get_kraj() const
{
	return a_kraj;
}

string Adress::Get_miejscowosc() const
{
    return a_miejscowosc;
}

//Streamy
ostream& operator << (ostream& aos, const Adress& o_aa)
{
	
    aos << o_aa.Get_miejscowosc() << " " << o_aa.Get_ulica() << " " << o_aa.Get_nrdomu() << " " << o_aa.Get_kraj() << " ";
	
	return aos;
}

istream& operator >> (istream& ais, Adress& i_aa)
{
    string town;
	string alley;
	string country;
	int housenum;

    ais >> town;

	ais >> alley;

	ais >> housenum;

	ais >> country;

	//ais >> alley >> housenum >> country;
    i_aa.Set_miejscowosc(town);
	i_aa.Set_ulica(alley);
	i_aa.Set_nrdomu(housenum);
	i_aa.Set_kraj(country);

	return ais;
}
