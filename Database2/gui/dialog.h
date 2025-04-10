#ifndef DIALOG_H
#define DIALOG_H
#include "DataBase.h"

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(Person* person, DataBase* db, QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_OK_b_ed_clicked();

    void on_canc_b_ed_clicked();

private:
    Ui::Dialog *ui;
    DataBase *dataBase;
    Person* ed_person;

signals:
    void accepted();
};

#endif // DIALOG_H
