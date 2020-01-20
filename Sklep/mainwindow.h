#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sklep_pracownik.h"
#include "nowy_uzytkownik.h"

class Sklep;
class Nowy_uzytkownik;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:

    void on_pokaz_haslo_clicked();

    void on_zaloguj_clicked();

    void on_konto_clicked();

private:
    Ui::MainWindow *ui;

    Sklep *s;
    Sklep_pracownik *s_p;
    Nowy_uzytkownik *n_u;
};

#endif // MAINWINDOW_H
