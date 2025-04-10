#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "DataBase.h"

#include <QMainWindow>
#include <QButtonGroup>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_change_page_clicked();

    void on_return1_clicked();

    void on_stackedWidget_currentChanged(int arg1);

    void DaneDoTabeli_bezbledow();

    void DaneDoTabeli();

    void on_search_button_clicked();

    void wyniki_do_tab(const BD& wyniki);

    void on_delete_Button_clicked();

    void on_Anuluj_search_clicked();

    void on_edit_button_clicked();

    void odczyt_bledy();

    void on_select_folder_clicked();

    void on_imp_pushButton_clicked();

    void on_delete_all_clicked();

    void on_sortuj_clicked();

    void on_add_record_button_clicked();

private:
    Ui::MainWindow *ui;
    DataBase *dataBase;
    QButtonGroup *CheckBoxGroup;  // Grupa checkboxów
};
#endif // MAINWINDOW_H
