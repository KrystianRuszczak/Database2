#include "DataBase.h"

Person* DataBase::persona_do_edycji(int selected_id)
{
    for (auto& osoba : b_osoby) {
        if (osoba.Get_id() == selected_id) {
            return &osoba;  // Zwraca wskaŸnik do osoby
        }
    }
    return nullptr;  // Jesli nic nie znalaz³
}

pair<string, bool> DataBase::edytuj(int id, const string& nowe_imie, const string& nowe_nazwisko, int nowe_ID, int nowy_wiek, const string& nowa_miejscowosc, const string& nowa_ulica, int nowy_NrDomu, const string& nowy_kraj)
{
    auto iterator = find_if(b_osoby.begin(), b_osoby.end(), [&id](const Person& osoba) {
        return osoba.Get_id() == id;
    });

    if (iterator != b_osoby.end())
    {
        string wiadomosc_zwrotna;
        bool czy_zapis = true;

        iterator->Set_imie(nowe_imie);
        iterator->Set_nazw(nowe_nazwisko);
        iterator->Set_wiek(nowy_wiek);

        Adress nowy_adres;
        nowy_adres.Set_miejscowosc(nowa_miejscowosc);
        nowy_adres.Set_ulica(nowa_ulica);
        nowy_adres.Set_nrdomu(nowy_NrDomu);
        nowy_adres.Set_kraj(nowy_kraj);
        iterator->Set_adres(nowy_adres);

        // Sprawdza czy u¿ytkownik zmieni³ numer id
        if (nowe_ID != iterator->Get_id())
        {
            iterator->Set_id(nowe_ID);
            auto [zmieniono, nowe_ID] = id_sprawdz(*iterator);

            if (zmieniono)
            {
                wiadomosc_zwrotna = to_string(nowe_ID);
            }
        }

        czy_zapis = zapis("Baza_danych.json");

        return {wiadomosc_zwrotna, czy_zapis};
    }
}

// Funkcja sprawdza unikalnoœæ ID i aktualizuje je jesli trzeba
pair<bool, int> DataBase::id_sprawdz(Person& w_person)
{
    int poszukiwane_id{ 1 };
    bool zmieniono{ false };

    for (const auto& id : b_osoby)
    {
        if ( (w_person.Get_id() == id.Get_id() && &w_person != &id) || w_person.Get_id() <= 0)   //jesli powtarza sie lub <= 0, zmieniamy i szukamy czy nie ma luki
        {
            zmieniono = true;

            while (true)
            {
                bool dziura = true;
                for (const auto& kolejny : b_osoby)
                {
                    if (kolejny.Get_id() == poszukiwane_id)  // Jesli jakas osoba ma id rowne szukanemu id to dajemy znaæ poprzez "dziura" ¿e luki nie ma i szukamy dalej
                    {
                        dziura = false; // Luka jest znaleziona wiêc operacje pomijane
                        poszukiwane_id++;
                        break;
                    }
                }
                if (dziura) // znaleziono brak wiêc ustawia id na ów brak
                {
                    w_person.Set_id(poszukiwane_id);
                    break;
                }
            }
        }
    }
    return {zmieniono, w_person.Get_id()};
}

tuple <bool, bool, int> DataBase::wprowadz(const string& im, const string& nazw, int id, int wiek, const string& miejsc, const string& ul, int nd, const string& kraj)
{
    Adress nadr;
    nadr.Set_miejscowosc(miejsc);
    nadr.Set_ulica(ul);
    nadr.Set_nrdomu(nd);
    nadr.Set_kraj(kraj);

    Person nosoba;
    nosoba.Set_imie(im);
    nosoba.Set_nazw(nazw);
    nosoba.Set_id(id);
    nosoba.Set_wiek(wiek);
    nosoba.Set_adres(nadr);

    bool bool_z_id = false;
    int int_z_id{0};
    std::tie(bool_z_id, int_z_id) = id_sprawdz(nosoba);

    b_osoby.push_back(nosoba);

    bool zapisujemy = true;
    zapisujemy = zapis("Baza_danych.json");

    return {zapisujemy, bool_z_id, int_z_id};
}

// Funkcja wykorzystywana przy wyszukiwaniu usuwanej osoby
BD DataBase::znajdz_usuwanego(int usuw_id)
{
    BD znaleziony_u;

    for (const auto& osoba_u : b_osoby)
    {
        if (usuw_id == osoba_u.Get_id())
        {
            znaleziony_u.push_back(osoba_u);
        }
    }

    return znaleziony_u; // Zwraca znalezion¹ osobe
}

void DataBase::usun(int kogo_u)
{
    auto znajdz = remove_if(b_osoby.begin(), b_osoby.end(),
        [&kogo_u](const Person& persona) {
            return persona.Get_id() == kogo_u; // Porównuje numery id
        });

    if (znajdz != b_osoby.end())
    {
        b_osoby.erase(znajdz, b_osoby.end());
        zapis("Baza_danych.json");
    }

}

string DataBase::pomniejsz(const string& s)
{
    string zmniejsz = s;
    transform(zmniejsz.begin(), zmniejsz.end(), zmniejsz.begin(), ::tolower);
    return zmniejsz;
}

BD DataBase::wyszukaj_podfunkcja(char dana, const string& szukane)
{
    bool ok = true;
    int sz_wart{};

    string low_szukane = pomniejsz(szukane);

    try {
        sz_wart = stoi(szukane);
    } catch (const std::invalid_argument& e) {
        ok = false;  // Jeœli konwersja siê nie powiedzie, to ok ustawia na false
    }

    BD wyniki;

    switch (dana)
    {
    case 'I':
        for (const auto& szukany : b_osoby)
        {
            if (low_szukane == pomniejsz(szukany.Get_imie()))
            {
                wyniki.push_back(szukany);
            }
        }
        break;
    case 'N':
        for (const auto& szukany : b_osoby)
        {
            if (low_szukane == pomniejsz(szukany.Get_nazw()))
            {
                wyniki.push_back(szukany);
            }
        }
        break;

    case 'D':
        if (ok)
        {
            for (const auto& szukany : b_osoby)
            {
                if ( sz_wart == szukany.Get_id())
                {
                    wyniki.push_back(szukany);
                }
            }
        }
        break;
    case 'W':
        if (ok)
        {
            for (const auto& szukany : b_osoby)
            {
                if (sz_wart == szukany.Get_wiek())
                {
                    wyniki.push_back(szukany);
                }
            }
        }
        break;
    case 'J':
        for (const auto& szukany : b_osoby)
        {
            if (low_szukane == pomniejsz(szukany.Get_adres().Get_miejscowosc()))
            {
                wyniki.push_back(szukany);
            }
        }
        break;
    case 'U':
        for (const auto& szukany : b_osoby)
        {
            if (low_szukane == pomniejsz(szukany.Get_adres().Get_ulica()))
            {
                wyniki.push_back(szukany);
            }
        }
        break;
    case 'M':
        if (ok)
        {
            for (const auto& szukany : b_osoby)
            {
                if (sz_wart == szukany.Get_adres().Get_nrdomu())
                {
                    wyniki.push_back(szukany);
                }
            }
        }
        break;
    case 'K':
        for (const auto& szukany : b_osoby)
        {
            if (low_szukane == pomniejsz(szukany.Get_adres().Get_kraj()))
            {
                wyniki.push_back(szukany);
            }
        }
        break;
    default:
        break;
    }

    return wyniki;

}

// ZAPIS I ODCZYT

// Funkcja s³u¿y odczytywaniu danych z pliku, dodatkowo wysy³a kody blêdów jesli zajdzie potrzeba
tuple<bool, int, string> DataBase::odczyt(const string& file_name)
{
    b_osoby.clear();

    czy_plik_istnieje(file_name);    //funkcja z pliku pomocne.h

    fstream plik(file_name, std::ios::in);

    bool blad = true;
    int kod_bledu = 0;

    if (!plik.is_open())
    {
        return {false, 1, ""};
    }

    try {
        json json_dane;

        // czy plik jest pusty
        if (plik.peek() == std::ifstream::traits_type::eof()) {
            kod_bledu = 2;
            blad = true;
            json_dane = json::array();  // Inicjalizuje pust¹ tablicê json
        }
        else {
            plik >> json_dane;  // Odczytuje dane z pliku json
        }

        plik.close();

        //Sprawdza czy s¹ dane
        if (json_dane.empty()) {
            kod_bledu = 3;
            blad = false;
        }

        // przetwarzanie danych, dodawanie ich do bazy
        for (const auto& osoba_dana : json_dane) {
            Person person;
            person.Set_imie(osoba_dana["imie"]);
            person.Set_nazw(osoba_dana["nazwisko"]);
            person.Set_id(osoba_dana["id"]);
            person.Set_wiek(osoba_dana["wiek"]);

            Adress adres;
            adres.Set_miejscowosc(osoba_dana["adres"]["miejscowosc"]);
            adres.Set_ulica(osoba_dana["adres"]["ulica"]);
            adres.Set_nrdomu(osoba_dana["adres"]["numer_domu"]);
            adres.Set_kraj(osoba_dana["adres"]["kraj"]);

            person.Set_adres(adres);

            b_osoby.push_back(person);
        }

        return {blad, kod_bledu, ""};

    }
    catch (const json::exception& e) {
        // obsluga bledow z odczytem lub niepoprawnym formatem json
        //exit(1); // zakoñczenie programu w przypadku b³êdu
        return {false, 4, e.what()};
    }
}

bool DataBase::zapis(const string& file_name)
{
    fstream plik(file_name, std::ios::out);

    if (!plik.is_open()) //jeœli nie mo¿na otworzyæ pliku
    {
        return false;
    }

    json json_dane;

    // iteracja po rekordach i zapisywanie do obiektu json
    for (const auto& osoba : b_osoby)
    {
        json osoba_dana;
        osoba_dana["imie"] = osoba.Get_imie();
        osoba_dana["nazwisko"] = osoba.Get_nazw();
        osoba_dana["id"] = osoba.Get_id();
        osoba_dana["wiek"] = osoba.Get_wiek();

        json adres_dana;
        adres_dana["miejscowosc"] = osoba.Get_adres().Get_miejscowosc();
        adres_dana["ulica"] = osoba.Get_adres().Get_ulica();
        adres_dana["numer_domu"] = osoba.Get_adres().Get_nrdomu();
        adres_dana["kraj"] = osoba.Get_adres().Get_kraj();

        osoba_dana["adres"] = adres_dana;

        // dodaje dane osoby do obiektu json
        json_dane.push_back(osoba_dana);
    }

    // zapisuje dane JSON do pliku
    plik << json_dane.dump(4);  // robi wciêcia dla lepszego formatowania

    plik.close();
    return true;
}


void DataBase::wyczysc()
{
        b_osoby.clear();
        zapis("Baza_danych.json");
}

void DataBase::imp_data_json(string sciezka, bool usun_zastap)
{
    json importowane;
    //czy_plik_istnieje(sciezka);
    ifstream plik(sciezka);

    try {
        json json_dane;

        // czy plik jest pusty
        if (plik.peek() == std::ifstream::traits_type::eof()) {
            //kod_bledu = 2;
            //blad = true;
            json_dane = json::array();  // Inicjalizuje pust¹ tablicê json
        }
        else {
            plik >> importowane;
        }

        plik.close();

        if (!usun_zastap)
        {
            b_osoby.clear();
        }

        //Sprawdza czy s¹ dane
        if (json_dane.empty()) {
            //kod_bledu = 3;
            //blad = false;
        }

        // przetwarzanie danych, dodawanie ich do bazy
        for (const auto& osoba_dana : importowane) {
            Person person;
            person.Set_imie(osoba_dana["imie"]);
            person.Set_nazw(osoba_dana["nazwisko"]);
            person.Set_id(osoba_dana["id"]);
            person.Set_wiek(osoba_dana["wiek"]);

            Adress adres;
            adres.Set_miejscowosc(osoba_dana["adres"]["miejscowosc"]);
            adres.Set_ulica(osoba_dana["adres"]["ulica"]);
            adres.Set_nrdomu(osoba_dana["adres"]["numer_domu"]);
            adres.Set_kraj(osoba_dana["adres"]["kraj"]);

            person.Set_adres(adres);

            if (usun_zastap)
            {
                id_sprawdz(person);
            }

            b_osoby.push_back(person);
            zapis("Baza_danych.json");
        }
    }
    catch (const json::exception& e) {
        // obsluga bledow z odczytem lub niepoprawnym formatem json
        //exit(1); // zakoñczenie programu w przypadku b³êdu
        //return { false, 4, e.what() };
    }
}

void DataBase::imp_data_csv(string path, bool delete_replace)
{
    ifstream file(path);
    string line;
    getline(file, line);

    while (getline(file, line))
    {
        stringstream strstr(line);
        string name, surname, id, age, place, alley, house_num, country;

        getline(strstr, name, ',');
        getline(strstr, surname, ',');
        getline(strstr, id, ',');
        getline(strstr, age, ',');
        getline(strstr, place, ',');
        getline(strstr, alley, ',');
        getline(strstr, house_num, ',');
        getline(strstr, country, ',');

        Person person;

        person.Set_imie(name);
        person.Set_nazw(surname);
        person.Set_id(stoi(id));
        person.Set_wiek(stoi(age));

        Adress address;
        address.Set_miejscowosc(place);
        address.Set_ulica(alley);
        address.Set_nrdomu(stoi(house_num));
        address.Set_kraj(country);

        person.Set_adres(address);

        if (delete_replace)
        {
            id_sprawdz(person);
        }

        b_osoby.push_back(person);
    }
    zapis("Baza_danych.json");
    file.close();
}

void DataBase::imp_data_format(const string& format, string path, bool delete_replace)
{
    if (!delete_replace)
    {
        b_osoby.clear();
    }

    if(format == "json")
    {
        imp_data_json(path, delete_replace);
    }
    else if(format == "csv")
    {
        imp_data_csv(path, delete_replace);
    }
}

void DataBase::exp_dane(const string& sciezka)
{
    json eksport;

    // iteracja po rekordach i zapisywanie do obiektu json
    for (const auto& osoba : b_osoby)
    {
        json osoba_dane;
        osoba_dane["imie"] = osoba.Get_imie();
        osoba_dane["nazwisko"] = osoba.Get_nazw();
        osoba_dane["id"] = osoba.Get_id();
        osoba_dane["wiek"] = osoba.Get_wiek();

        json adres_dane;
        adres_dane["miejscowosc"] = osoba.Get_adres().Get_miejscowosc();
        adres_dane["ulica"] = osoba.Get_adres().Get_ulica();
        adres_dane["numer_domu"] = osoba.Get_adres().Get_nrdomu();
        adres_dane["kraj"] = osoba.Get_adres().Get_kraj();

        osoba_dane["adres"] = adres_dane;

        // dodaje dane osoby do obiektu json
        eksport.push_back(osoba_dane);
    }

    // zapisuje dane JSON do pliku
    ofstream plik(sciezka);
    plik << eksport.dump(4);  // robi wciêcia dla lepszego formatowania
    //if (!plik.is_open())
    //{
    //    throw std::runtime_error("Nie mo¿na otworzyæ pliku do zapisu: " + sciezka);
    //}
    plik.close();
}

void DataBase::exp_data_csv(const string& path)
{
    ofstream file(path);
    file << "Imiê,Nazwisko,NumerID,Wiek,Miejscowoœæ,Ulica,Numer domu,Kraj\n";

    for(const auto& osoba : b_osoby)
    {
        file << osoba.Get_imie() << ","
             << osoba.Get_nazw() << ","
             << osoba.Get_id() << ","
             << osoba.Get_wiek() << ","
             << osoba.Get_adres().Get_miejscowosc() << ","
             << osoba.Get_adres().Get_ulica() << ","
             << osoba.Get_adres().Get_nrdomu() << ","
             << osoba.Get_adres().Get_kraj() << "\n";
    }
    file.close();
}

void DataBase::exp_data_format(const string& path, const string& format)
{
    if(format == "json")
    {
        exp_dane(path);
    }
    else if(format == "csv")
    {
        exp_data_csv(path);
    }
}

void DataBase::sortowanie(int co_sort, bool najw_m)    // najw_m == true - sortuje od najmniejszego do najwiêkszego
{

    map<int, function<string(const Person&)>> typ_string = {
        {1, &Person::Get_imie},
        {2, &Person::Get_nazw},
    };

    map<int, function<int(const Person&)>> typ_int = {
        {3, &Person::Get_id},
        {4, &Person::Get_wiek},
    };

    map<int, function<string(const Adress&)>> typ_adres = {
        {5, &Adress::Get_miejscowosc},
        {6, &Adress::Get_ulica},
        {8, &Adress::Get_kraj},
    };

    map<int, function<int(const Adress&)>> typ_adres_int = {
        {7, &Adress::Get_nrdomu},
    };

    if (typ_string.find(co_sort) != typ_string.end()) {
        auto typ = typ_string[co_sort];
        sort(b_osoby.begin(), b_osoby.end(), [typ, najw_m](const Person& os_a, const Person& os_b) {
            return najw_m ? typ(os_a) < typ(os_b) : typ(os_a) > typ(os_b);
        });
    }
    else if (typ_int.find(co_sort) != typ_int.end()) {
        auto typ = typ_int[co_sort];
        sort(b_osoby.begin(), b_osoby.end(), [typ, najw_m](const Person& os_a, const Person& os_b) {
            return najw_m ? typ(os_a) < typ(os_b) : typ(os_a) > typ(os_b);
        });
    }
    else if (typ_adres.find(co_sort) != typ_adres.end()) {
        auto typ = typ_adres[co_sort];
        sort(b_osoby.begin(), b_osoby.end(), [typ, najw_m](const Person& os_a, const Person& os_b) {
            const Adress& adres_a = os_a.Get_adres();
            const Adress& adres_b = os_b.Get_adres();
            return najw_m ? typ(adres_a) < typ(adres_b) : typ(adres_a) > typ(adres_b);
        });
    }
    else if (typ_adres_int.find(co_sort) != typ_adres_int.end()) {
        auto typ = typ_adres_int[co_sort];
        sort(b_osoby.begin(), b_osoby.end(), [typ, najw_m](const Person& os_a, const Person& os_b) {
            const Adress& adres_a = os_a.Get_adres();
            const Adress& adres_b = os_b.Get_adres();
            return najw_m ? typ(adres_a) < typ(adres_b) : typ(adres_a) > typ(adres_b);
        });
    }

    zapis("Baza_danych.json");
}

void DataBase::sort_i_zapis(int co_sort, bool najw_m, bool czy_zapis)
{
    if(czy_zapis)
    {
        sortowanie( co_sort, najw_m);
        zapis("Baza_danych.json");
    }
}
