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
/**
 *  Klasa MainWindow okna logowania do sklepu
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:

    /**
     * Metoda realizowana po naciśnięciu przycisku 'Pokaż hasło'
     */
    void on_pokaz_haslo_clicked();

    /**
     * Metoda realizowana po naciśnięciu przycisku 'Zaloguj'
     */
    void on_zaloguj_clicked();

    /**
     * Metoda realizowana po naciśnięciu przycisku 'Utwórz konto klienta'
     */
    void on_konto_clicked();

private:
    Ui::MainWindow *ui;

    Sklep *s;
    Sklep_pracownik *s_p;
    Nowy_uzytkownik *n_u;
};

#endif // MAINWINDOW_H
