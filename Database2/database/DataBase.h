#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <cstdlib>

#include <iosfwd>
#include <limits>

#include <sstream>
//sleep
//#include <windows.h>
//#include <conio.h>

//Przyjmowanie funkcji jako argument
#include <functional>

//Wiele zwraca
#include <tuple>

//pliki dodatkowe
#include "pomocne.h"
#include "json.hpp"

//KLASY
#include "Adress.h"
#include "Person.h"

using std::string;
using std::stringstream;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

using std::find_if;

using std::tuple;           //U�YWANE PRZY "ODCZYT"

//nowe funkcje
using std::back_inserter;   //ODCZYT
using std::copy;            //WYSWIETL, ZAPIS, ODCZYT
using std::remove_if;       //USUN
using std::pair;            //id_sprawdz
using std::to_string;

using std::ofstream;
using std::ios;
using std::ifstream;
using std::fstream;
using std::istream;
using std::ostream;
using std::ostream_iterator;    //Zapis
using std::istream_iterator;    //odczyt

using std::transform;

using std::sort;
using std::map;

//Przyjmowanie funkcji jako argument
using std::function;

using BD = vector<Person>;

using json = nlohmann::json;

class DataBase
{
public:
    // Funkcja dodaje nowy rekord (osob�) do bazy danych i sprawdza jej ID za pomoc� funkcji id_sprawdz() (opisana ni�ej); po dodaniu rekordu do "b_osoby", zmiany s� zapisywane do pliku .json
    //Poni�ej opis
    /*
    // Parametry:
    // - im: imi� osoby
    // - nazw: nazwisko osoby
    // - id: ID osoby (unikalny parametr dla ka�dego rekordu w bazie danych)
    // - wiek: wiek osoby
    // - miejsc: miejscowo�c zamieszkania
    // - ul: ulica
    // - nd: numer domu
    // - kraj: kraj
    // Zwraca pod zmienn� typu bool "zapisujemy":
    // - true, je�li zapis do pliku zako�czy� si� powodzeniem
    // - false, w innym wypadku
    */
    tuple <bool, bool, int> wprowadz(const string& im, const string& nazw, int id, int wiek, const string& miejsc, const string& ul, int nd, const string& kraj);
    
    // Funkcja sprawdza, czy ID osoby jest unikalne w skali ca�ej bazy danych, je�li nie przypisuje osobie nowe ID, ustawione jako najmniejsze dost�pne
    // Dodatkowo, ID zostaje zmienione je�li jest mniejsze od 0
    // Je�li istniej� dwa rekordy o ID np. 6 oraz 8 i je�li r�wnocze�nie funkcja wykryje powtarzaj�ce si� ID, to nowo nadane ID b�dzie r�wna�o si� przerwie w kolejno�ci - w tym wypadku 7
    // Parametry:
    // - w_person: osoba, kt�rej ID funkcja weryfikuje
    // Zwraca kolejno (pair):
    // - bool: true, je�li ID zosta�o zmienione na nowe, false w przeciwnym wypadku
    // - int: ko�cowe ID przypisane do osoby
    pair<bool, int> id_sprawdz(Person& w_person);

    // Funkcja usuwa osob� z bazy na podstawie podanego ID
    // Po usuni�ciu nastepuje aktualizacja bazy danych, poprzez zapis zmian do pliku .json
    // Parametry:
    // - kogo_u: numer ID osoby usuwanej
    void usun(int kogo_u);

    // Funkcja wyszukuje osob� o podanym ID w bazie danych
    // Wykorzystywana g��wnie przy GUI, do wy�wietlenia szczeg��w osoby przed jej usuni�ciem (lub edycj�)
    // Parametry:
    // - usuw_id: ID poszukiwanej osoby
    // Zwraca:
    // - BD (wektor obiekt�w typu "Person"), zawieraj�cy znalezion� osob�
    BD znajdz_usuwanego(int usuw_id);

    // Funkcja zmienia wszystkie znaki w podanym ci�gu znak�w string na ma�e litery
    // Wykorzystywana przy funkcji "wyszukaj_podfunkcja"
    // Parametry:
    // - s: ci�g znak�w string, kt�rego litery maja zosta� zmienione na ma�e
    // Zwraca:
    // - string, w kt�rym wszystkie litery s� w wersji ma�ej.
    string pomniejsz(const string& s);

    // Funkcja umo�liwia wyszukiwanie os�b w bazie danych na podstawie r�nych kryteri�w
    // Parametry:
    // - dana: znak wskazuj�cy, wed�ug jakiego kryterium ma odbywa� si� wyszukiwanie, gddzie:
    // 'I' - imi�,
    // 'N' - nazwisko,
    // 'D' - numer ID,
    // 'W' - wiek,
    // 'J' - miejscowo��,
    // 'U' - ulica,
    // 'M' - numer domu,
    // 'K' - kraj.
    // - szukane: ci�g tekstowy lub liczba, zale�nie od parametru wyszukiwania, np. imi� "Jan" lub wiek "44" 
    // Zwraca:
    // - BD (wektor obiekt�w typu 'Person") zawieraj�cy osoby, kt�re pasuj� do fraz wyszukiwania
    BD wyszukaj_podfunkcja(char dana, const string& szukane);

    // Funkcja odczytuje dane z pliku '.json' i �aduje je do bazy danych - "b_osoby"
    // Parametry:
    // - file_name: nazwa pliku, z kt�rego odczytuje dane
    // Zwraca 3-elementowe "tuple":
    // - typ bool - okre�la, czy operacja zako�czy�a si� sukcesem (true - wy�wietlane okienko typu 'information'), (false - okienko typu 'warning', 'critical')
    // - typ int - kod b��du, gdzie:
    // 0 - sukces
    // 1 - b��d podczas otwierania pliku
    // 2 - plik jest pusty
    // 3-  dane w pliku s� puste/nieu�yteczne
    // 4 - b��d podczas przetwarzania danych JSON
    // - string - komunikat o b��dzie, je�li wyst�pi�
    tuple<bool, int, string> odczyt(const string& file_name);

    // Funkcja zapisuje dane z bazy danych do pliku
    // Parametry:
    // - file_name: nzwa pliku, do kt�rego zapisujemy dane
    // Zwraca bool:
    // -true - je�li zapis zako�czy� si� sukcesem
    // - false -w przeciwnym wpyadku
    bool zapis(const string& file_name);

    // Modyfikuje dane istniej�cej osoby w bazie danych na podstawie podanych parametr�w
    // Parametry:
    // - id: ID osoby, kt�rej dane chcemy edytowa�
    // - pozosta�e parametry symbolizuj� odpowiednio nowe, zmienione dane: nowe imi� osoby, nowe nazwisko nowe ID, nowy wie, now� miejscowo��, now� ulica, nowy numer domu, nowy kraj
    // Zwraca kolejno (pair):
    // - string: zawiera poprawione ID (dzi�ki funkcji id_sprawdz), je�li ID zosta�o zmienione przez uzytkownika i kolidowa�o ono z innym, ju� istniej�cym w bazie danych
    // - bool: true, je�li zmiany zosta�y zapisane do pliku, w przeciwnym wypadku false
    pair<string, bool> edytuj(int id, const string& nowe_imie, const string& nowe_nazwisko, int nowe_ID, int nowy_wiek, const string& nowa_miejscowosc, const string& nowa_ulica, int nowy_NrDomu, const string& nowy_kraj);
    
    // Znajduje i zwraca wska�nik do obiektu Person o podanym ID
    // Parametr: selected_id - numer ID osoby, kt�r� chcemy znale��
    // Zwraca: 
    // - wska�nik do obiektu klasy Person, je�li osoba o podanym ID istnieje w bazie danych
    // - nullptr, je�li osoba nie istnieje
    Person* persona_do_edycji(int selected_id);

    void wyczysc();

    void exp_dane(const string& sciezka);

    void imp_data_json(string sciezka, bool usun_zastap);

    void exp_data_format(const string& path,const string& format);

    void exp_data_csv(const string& path);

    void imp_data_csv(string path, bool delete_replace);

    void imp_data_format(const string& format, string path, bool delete_replace);

    void sortowanie(int co_sort, bool najw_m);

    void sort_i_zapis(int co_sort, bool najw_m, bool czy_zapis);

    //Gettery
    const BD& Get_osoby() const { return b_osoby; }

private:
    BD b_osoby;
};
