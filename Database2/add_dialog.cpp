#include "add_dialog.h"
#include "ui_add_dialog.h"
#include <QMessageBox>
#include "DataBase.h"

Add_dialog::Add_dialog(DataBase* db, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Add_dialog)
    , dataBase(db)
{
    ui->setupUi(this);
}

Add_dialog::~Add_dialog()
{
    delete ui;
}

void Add_dialog::on_dodaj_button_clicked()
{
    QString w_imie = ui->name->text();
    QString w_nazwisko = ui->surname->text();
    int w_id = ui->spinBox_ID->value();
    int w_wiek = ui->spinBox__age->value();
    QString w_miejsc = ui->town->text();
    QString w_ulica = ui->alley->text();
    int w_numd = ui->spinBox_hnum->value();
    QString w_kraj = ui->country->text();

    // W wypadku gdyby pola były puste
    if (w_imie.isEmpty() || w_nazwisko.isEmpty() || w_miejsc.isEmpty() || w_ulica.isEmpty() || w_kraj.isEmpty() || w_id <= 0 || w_wiek <= 0 || w_numd <= 0)
    {
        QMessageBox::warning(this, "Błąd", "Wszystkie pola muszą być wypełnione!");
        return;
    }

    auto [zapis_danych, bool_nowe_id, int_nowe_id] = dataBase->wprowadz(w_imie.toStdString(), w_nazwisko.toStdString(), w_id, w_wiek, w_miejsc.toStdString(), w_ulica.toStdString(), w_numd, w_kraj.toStdString());

    if(zapis_danych)
    {
        QMessageBox::information(nullptr, "Zapisano dane", "Zapisywanie zakończone pomyślnie.");
    }
    else
    {
        QMessageBox::critical(nullptr, "Błąd", "Nie można otworzyć pliku do zapisu.");
    }

    if (bool_nowe_id)
    {
        QMessageBox::information(nullptr, "Błędne ID", "Podane ID było już zajęte. ID zostało zmienione na: " + QString::number(int_nowe_id) + ".");
    }

    //Czyścimy pola po dodaniu osoby
    ui->name->clear();
    ui->surname->clear();
    ui->town->clear();
    ui->alley->clear();
    ui->country->clear();
    ui->spinBox_ID->setValue(0);
    ui->spinBox__age->setValue(0);
    ui->spinBox_hnum->setValue(0);
}


void Add_dialog::on_anuluj_d_clicked()
{
    ui->name->clear();
    ui->surname->clear();
    ui->spinBox_ID->setValue(0);
    ui->spinBox__age->setValue(0);
    ui->town->clear();
    ui->alley->clear();
    ui->spinBox_hnum->setValue(0);
    ui->country->clear();
}


void Add_dialog::on_cancel_add_button_clicked()
{
    close();
}

