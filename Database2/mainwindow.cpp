#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DataBase.h"
#include <QMessageBox>
#include "dialog.h"
#include "add_dialog.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dataBase(new DataBase())
{
    ui->setupUi(this);

    odczyt_bledy();

    CheckBoxGroup = new QButtonGroup(this);  // Inicjalizacja grupy przycisków

    ui->stackedWidget->setCurrentIndex(0);  // Ustawia pierwszą stronę (indeks 0)

    ui->return1->hide(); // return1 ukryty na początku

    connect(ui->delete_spinBox, SIGNAL(valueChanged(int)), this, SLOT(on_delete_spinBox_valueChanged(int))); //zmiana wartości w Spinbox - tabela wyswietla coś innego

    connect(ui->endprog, &QPushButton::clicked, this, &QApplication::quit); //przycisk do kończenia programu

    // Checkboxy do grupy
    CheckBoxGroup->addButton(ui->show_checkBox);

    //tylko jeden checkbox może być zaznaczony
    CheckBoxGroup->setExclusive(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dataBase;

}

//Wywoływanie funkcji odczyt z obsługą kodów błędów
void MainWindow::odczyt_bledy()
{
    auto [blad, kod, wiadomosc] = dataBase->odczyt("Baza_danych.json"); // wczytywanie danych z bd

    if(blad)
    {
        if(kod == 2)
        {
            QMessageBox::information(nullptr, "Pusty plik", "Plik jest pusty. Inicjalizacja pustej bazy danych.");
        }
        //else
        //{
        //    QMessageBox::information(nullptr, "Wczytano dane", "Wczytywanie zakończone pomyślnie.");
        //}
    }
    else
    {
        switch (kod)
        {
        case 1:
            QMessageBox::critical(nullptr, "Blad", "Nie mozna otworzyc pliku do odczytu.");
            break;
        case 3:
            QMessageBox::warning(nullptr, "Brak danych", "Nie znaleziono użytecznych danych w pliku.");
            break;
        case 4:
             QMessageBox::critical(nullptr, "Błąd", QString("Błąd podczas wczytywania pliku JSON: ")+QString::fromStdString(wiadomosc)+".");
            break;
        }
    }
}

void MainWindow::on_change_page_clicked()
{
    if (ui->show_checkBox->isChecked()) {
        ui->stackedWidget->setCurrentIndex(1); // Strona 2
        DaneDoTabeli();
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(0); // Strona 1
    }
}

void MainWindow::on_stackedWidget_currentChanged(int arg1)
{
    if (arg1 == 0) {
        ui->return1->hide();
    } else {
        ui->return1->show();
    }
}

void MainWindow::on_return1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::DaneDoTabeli_bezbledow()
{
    //dataBase->odczyt("Baza_danych.json");

    const auto& osoby = dataBase->Get_osoby();

    ui->show_table->clearContents(); // stare dane z tabeli usuwane
    ui->show_table->setRowCount(static_cast<int>(osoby.size())); //Tyle rzędów ile osób w bazie

    for (int i = 0; i < osoby.size(); ++i)
    {
        const Person& osoba = osoby[i];

        ui->show_table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(osoba.Get_imie())));
        ui->show_table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(osoba.Get_nazw())));
        ui->show_table->setItem(i, 2, new QTableWidgetItem(QString::number(osoba.Get_id())));
        ui->show_table->setItem(i, 3, new QTableWidgetItem(QString::number(osoba.Get_wiek())));
        ui->show_table->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(osoba.Get_adres().Get_miejscowosc())));
        ui->show_table->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(osoba.Get_adres().Get_ulica())));
        ui->show_table->setItem(i, 6, new QTableWidgetItem(QString::number(osoba.Get_adres().Get_nrdomu())));
        ui->show_table->setItem(i, 7, new QTableWidgetItem(QString::fromStdString(osoba.Get_adres().Get_kraj())));
    }
}

void MainWindow::DaneDoTabeli()
{
    odczyt_bledy();

    const auto& osoby = dataBase->Get_osoby();

    ui->show_table->clearContents(); // stare dane z tabeli usuwane
    ui->show_table->setRowCount(static_cast<int>(osoby.size())); //Tyle rzędów ile osób w bazie

    for (int i = 0; i < osoby.size(); ++i)
    {
        const Person& osoba = osoby[i];

        ui->show_table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(osoba.Get_imie())));
        ui->show_table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(osoba.Get_nazw())));
        ui->show_table->setItem(i, 2, new QTableWidgetItem(QString::number(osoba.Get_id())));
        ui->show_table->setItem(i, 3, new QTableWidgetItem(QString::number(osoba.Get_wiek())));
        ui->show_table->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(osoba.Get_adres().Get_miejscowosc())));
        ui->show_table->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(osoba.Get_adres().Get_ulica())));
        ui->show_table->setItem(i, 6, new QTableWidgetItem(QString::number(osoba.Get_adres().Get_nrdomu())));
        ui->show_table->setItem(i, 7, new QTableWidgetItem(QString::fromStdString(osoba.Get_adres().Get_kraj())));
    }

}

void MainWindow::wyniki_do_tab(const BD& wyniki) {

    ui->show_table->clearContents();
    ui->show_table->setRowCount(wyniki.size());  // ustawia liczbę wierszy na liczbę wyników

    int row = 0;
    for (const auto& osoba : wyniki) {

        ui->show_table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(osoba.Get_imie())));
        ui->show_table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(osoba.Get_nazw())));
        ui->show_table->setItem(row, 2, new QTableWidgetItem(QString::number(osoba.Get_id())));
        ui->show_table->setItem(row, 3, new QTableWidgetItem(QString::number(osoba.Get_wiek())));
        ui->show_table->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(osoba.Get_adres().Get_miejscowosc())));
        ui->show_table->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(osoba.Get_adres().Get_ulica())));
        ui->show_table->setItem(row, 6, new QTableWidgetItem(QString::number(osoba.Get_adres().Get_nrdomu())));
        ui->show_table->setItem(row, 7, new QTableWidgetItem(QString::fromStdString(osoba.Get_adres().Get_kraj())));
        row++;
    }
}

void MainWindow::on_search_button_clicked()
{
    QString wybrany_typ = ui->search_by->currentText();

    QString szukane = ui->look_for->text();

    string szukane_str = szukane.toStdString();

    BD poszukuj;

    if (wybrany_typ == "Imię") {
        poszukuj = dataBase->wyszukaj_podfunkcja('I', szukane_str);
    } else if (wybrany_typ == "Nazwisko") {
        poszukuj = dataBase->wyszukaj_podfunkcja('N', szukane_str);
    } else if (wybrany_typ == "Numer ID") {
        poszukuj = dataBase->wyszukaj_podfunkcja('D', szukane_str);
    } else if (wybrany_typ == "Wiek") {
        poszukuj = dataBase->wyszukaj_podfunkcja('W', szukane_str);
    } else if (wybrany_typ == "Miejscowość") {
        poszukuj = dataBase->wyszukaj_podfunkcja('J', szukane_str);
    } else if (wybrany_typ == "Ulica") {
        poszukuj = dataBase->wyszukaj_podfunkcja('U', szukane_str);
    } else if (wybrany_typ == "Numer domu") {
        poszukuj = dataBase->wyszukaj_podfunkcja('M', szukane_str);
    } else if (wybrany_typ == "Kraj") {
        poszukuj = dataBase->wyszukaj_podfunkcja('K', szukane_str);
    }
    wyniki_do_tab(poszukuj);
}

void MainWindow::on_Anuluj_search_clicked()
{
    ui->look_for->clear();
    DaneDoTabeli();
}

void MainWindow::on_delete_Button_clicked()
{
    int u_id = ui->delete_spinBox->value();
    dataBase->usun(u_id);
    ui->delete_spinBox->setValue(0);
    DaneDoTabeli();
}

void MainWindow::on_edit_button_clicked()
{
    int val = ui->delete_spinBox->value();
    if(val == 0)
    {
        return;
    }

    Person* persontoedit = dataBase->persona_do_edycji(val);

    if (persontoedit == nullptr) {
        QMessageBox::warning(this, "Błąd", "Nie znaleziono osoby o tym ID.");
        return;
    }

    Dialog dialog(persontoedit, dataBase, this);

    dialog.exec();

    ui->delete_spinBox->setValue(0);

    DaneDoTabeli();
}

void MainWindow::on_select_folder_clicked()
{
    QString sciezka_pliku = QFileDialog::getSaveFileName(
        this,
        tr("Zapisz plik"),
        "BazaDanych_eksportowana",
        tr("Pliki JSON (*.json);;Pliki CSV (*.csv);;Wszystkie pliki (*)"));  // Domyślny katalog

    if (sciezka_pliku.isEmpty())
    {
        return;
    }

    if(sciezka_pliku.endsWith(".json", Qt::CaseInsensitive))
    {
        dataBase->exp_data_format(sciezka_pliku.toStdString(), "json");
    }
    else if(sciezka_pliku.endsWith(".csv", Qt::CaseInsensitive))
    {
        dataBase->exp_data_format(sciezka_pliku.toStdString(), "csv");
    }
    else
    {
        QMessageBox::warning(this, tr("Nieobsługiwany format"), tr("Nieznany format pliku."));
    }


}

void MainWindow::on_imp_pushButton_clicked()
{
    QMessageBox impo_dial;
    impo_dial.setIcon(QMessageBox::Question);
    impo_dial.setWindowTitle(tr("Importowanie danych"));
    impo_dial.setText(tr("Czy importowane dane mają zostać zintegrowane z istniejącą bazą czy mają ją zastąpić?"));

    QPushButton *zintegrujButton = impo_dial.addButton(tr("Zintegruj"), QMessageBox::YesRole);
    QPushButton *zastapButton = impo_dial.addButton(tr("Zastąp"), QMessageBox::NoRole);
    QPushButton *anulujButton = impo_dial.addButton(tr("Anuluj"), QMessageBox::RejectRole);

    impo_dial.exec();

    if (impo_dial.clickedButton() == zintegrujButton) {
        QString pliczek = QFileDialog::getOpenFileName(
            this,
            tr("Wybierz plik"),
            "",
            tr("Pliki JSON (*.json);;Pliki CSV (*.csv);;Wszystkie pliki (*)")
            );
        if (!pliczek.isEmpty())
        {
            if(pliczek.endsWith(".json", Qt::CaseInsensitive))
            {
                dataBase->imp_data_format("json", pliczek.toStdString(), true);
            }
            else if(pliczek.endsWith(".csv", Qt::CaseInsensitive))
            {
                dataBase->imp_data_format("csv", pliczek.toStdString(), true);
            }
            DaneDoTabeli();
        }
    }
    else if(impo_dial.clickedButton() == zastapButton)
    {
        QString plikk = QFileDialog::getOpenFileName(
            this,
            tr("Wybierz plik"),
            "",
            tr("Pliki JSON (*.json);;Pliki CSV (*.csv);;Wszystkie pliki (*)")
            );
        if (!plikk.isEmpty())
        {
            if(plikk.endsWith(".json", Qt::CaseInsensitive))
            {
                dataBase->imp_data_format("json", plikk.toStdString(), false);
            }
            else if(plikk.endsWith(".csv", Qt::CaseInsensitive))
            {
                dataBase->imp_data_format("csv", plikk.toStdString(), false);
            }
            DaneDoTabeli();
        }
    }
}


void MainWindow::on_delete_all_clicked()
{
    QMessageBox potw_usu;
    potw_usu.setIcon(QMessageBox::Question);
    potw_usu.setWindowTitle(tr("Potwierdź usunięcie danych"));
    potw_usu.setText(tr("Czy na pewno chcesz usunąć wszystkie dane z bazy?"));

    QPushButton *takButton = potw_usu.addButton(tr("Tak"), QMessageBox::YesRole);
    QPushButton *anulujButton = potw_usu.addButton(tr("Anuluj"), QMessageBox::NoRole);

    potw_usu.exec();

    // Sprawdzenie decyzji użytkownika
    if (potw_usu.clickedButton() == takButton) {
        // Jeśli użytkownik potwierdził, usuwamy dane
        dataBase->wyczysc();
        DaneDoTabeli_bezbledow();

        QMessageBox::information(this, tr("Operacja zakończona"), tr("Wszystkie dane zostały usunięte."));
    }

}


void MainWindow::on_sortuj_clicked()
{
    //int co_sort, bool najw_m
    QString wybrany_typ = ui->sort_comboBox->currentText();
    QString najw_najm = ui->sort_najw_najm_comboBox->currentText();

    bool jak = true;

    if(najw_najm == "największego/Z-A")
    {
        jak = false;
    }

    if (wybrany_typ == "Imię") {
        dataBase->sortowanie(1, jak);
    } else if (wybrany_typ == "Nazwisko") {
        dataBase->sortowanie(2, jak);
    } else if (wybrany_typ == "Numer ID") {
        dataBase->sortowanie(3, jak);
    } else if (wybrany_typ == "Wiek") {
        dataBase->sortowanie(4, jak);
    } else if (wybrany_typ == "Miejscowość") {
        dataBase->sortowanie(5, jak);
    } else if (wybrany_typ == "Ulica") {
        dataBase->sortowanie(6, jak);
    } else if (wybrany_typ == "Numer domu") {
        dataBase->sortowanie(7, jak);
    } else if (wybrany_typ == "Kraj") {
        dataBase->sortowanie(8, jak);
    }

    //dataBase -> sortowanie();
    DaneDoTabeli_bezbledow();
}


void MainWindow::on_add_record_button_clicked()
{
    Add_dialog add_dialog(dataBase, this);

    add_dialog.exec();

    DaneDoTabeli();
}

