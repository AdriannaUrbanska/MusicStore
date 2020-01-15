#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sklep.h"
#include "sklep_pracownik.h"
#include "nowy_uzytkownik.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pokaz_haslo_clicked();

    void on_zaloguj_clicked();

    void connection();

    void on_konto_clicked();

private:
    Ui::MainWindow *ui;

    Sklep *s;
    Sklep_pracownik *s_p;
    Nowy_uzytkownik *n_u;
};

#endif // MAINWINDOW_H
