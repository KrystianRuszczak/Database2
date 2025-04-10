#include "Person.h"
#include <iostream>
#include <vector>


using std::string;
using std::cout;
using std::cin;
using std::endl;


//Setters
void Person::Set_imie(string imie)
{
	p_imie = imie;
}

void Person::Set_nazw(string nazw)
{
	p_nazw = nazw;
}

void Person::Set_id(int id)
{
	p_id = id;
}

void Person::Set_wiek(int wiek)
{
	p_wiek = wiek;
}

void Person::Set_adres(Adress adres)
{
	p_adres = adres;
}

//Getters
string Person::Get_imie() const
{
	return p_imie;
}

string Person::Get_nazw() const
{
	return p_nazw;
}

int Person::Get_id() const
{
	return p_id;
}

int Person::Get_wiek() const
{
	return p_wiek;
}

Adress Person::Get_adres() const
{
	return p_adres;
}

//Streamers

std::istream& operator >> (std::istream& pis, Person& i_pp)
{
	string name;
	string surname;
	int index;
	int age;
	Adress adress;

	pis >> name >> surname >> index >> age >> adress;
	
	i_pp.Set_imie(name);
	i_pp.Set_nazw(surname);
	i_pp.Set_id(index);
	i_pp.Set_wiek(age);
	i_pp.Set_adres(adress);

	return pis;
}

std::ostream& operator << (std::ostream& pos, const Person& o_pp)
{
	pos << o_pp.Get_imie() << " " << o_pp.Get_nazw() << " " << o_pp.Get_id() << " " << o_pp.Get_wiek() << " " << o_pp.Get_adres();
	return pos;
}
