#ifndef ADD_DIALOG_H
#define ADD_DIALOG_H

#include <QDialog>
#include <DataBase.h>

namespace Ui {
class Add_dialog;
}

class Add_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Add_dialog(DataBase* db, QWidget *parent = nullptr);
    ~Add_dialog();

private slots:
    void on_dodaj_button_clicked();

    void on_anuluj_d_clicked();

    void on_cancel_add_button_clicked();

private:
    Ui::Add_dialog *ui;
    DataBase *dataBase;
};

#endif // ADD_DIALOG_H
