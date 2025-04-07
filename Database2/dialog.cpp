#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include "DataBase.h"

Dialog::Dialog(Person* person, DataBase* db, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , ed_person(person)
    , dataBase(db)
{
    ui->setupUi(this);

    ui->name_d->setText(QString::fromStdString(ed_person->Get_imie()));
    ui->surname_d->setText(QString::fromStdString(ed_person->Get_nazw()));
    ui->id_spinBox_d->setValue(ed_person->Get_id());
    ui->age_spb_d->setValue(ed_person->Get_wiek());
    ui->street_d->setText(QString::fromStdString(ed_person->Get_adres().Get_ulica()));
    ui->town_d->setText(QString::fromStdString(ed_person->Get_adres().Get_miejscowosc()));
    ui->hn_sb_d->setValue(ed_person->Get_adres().Get_nrdomu());
    ui->country_d->setText(QString::fromStdString(ed_person->Get_adres().Get_kraj()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_OK_b_ed_clicked()
{
    QString e_name = ui->name_d->text();
    QString e_sur = ui->surname_d->text();
    int e_id = ui->id_spinBox_d->value();
    int e_ag = ui->age_spb_d->value();
    QString e_pla = ui->town_d->text();
    QString e_street = ui->street_d->text();
    int e_hnum = ui->hn_sb_d->value();
    QString e_cntr = ui->country_d->text();

    if (e_name.isEmpty() || e_sur.isEmpty() || e_pla.isEmpty() || e_street.isEmpty() || e_cntr.isEmpty() || e_id <= 0 || e_ag <= 0 || e_hnum <= 0)
    {
        QMessageBox::warning(this, "Błąd", "Wszystkie pola muszą być wypełnione!");
        return;
    }

    //Wyświetla komunikat jeśli zmieniono ID
    auto [zwrotna, bool_zapis] = dataBase->edytuj(ed_person->Get_id(), e_name.toStdString(), e_sur.toStdString(), e_id, e_ag, e_pla.toStdString(), e_street.toStdString(), e_hnum, e_cntr.toStdString());

    if (!zwrotna.empty() && zwrotna != "kontrolna")
    {
        QMessageBox::information(this, "Błędne ID", "Podane ID było już zajęte. ID zostało zmienione na: "+QString::fromStdString(zwrotna)+".");
        
    }

    if (bool_zapis)
    {
        QMessageBox::information(nullptr, "Zapisano dane", "Zapisywanie zakończone pomyślnie.");
    }
    else
    {
        QMessageBox::critical(nullptr, "Błąd", "Nie można otworzyć pliku do zapisu.");
    }

    //close();
    accept();
}


void Dialog::on_canc_b_ed_clicked()
{
    close();
}

