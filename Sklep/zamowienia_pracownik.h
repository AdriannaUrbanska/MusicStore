#ifndef ZAMOWIENIA_PRACOWNIK_H
#define ZAMOWIENIA_PRACOWNIK_H

#include <QDialog>
#include "zamowienie_pracownik_info.h"

namespace Ui {
class Zamowienia_pracownik;
}
/**
 *  Klasa Zamowienia_pracownik okna wyświetlania wszystkich zamówień dla pracownika
 */
class Zamowienia_pracownik : public QDialog
{
    Q_OBJECT

public:
    explicit Zamowienia_pracownik(QWidget *parent = 0);
    ~Zamowienia_pracownik();

    int i_w_trakcie;
    int i_zrealizowane;

private slots:
    /**
     * Metoda realizowana po naciśnięciu przycisku 'Powrót'
     */
    void on_powrot_clicked();

    /**
     * Metoda aktualizująca listę zamówień
     */
    void zamowienia();

    /**
     * Metoda realizowana po naciśnięciu przycisku 'Oznacz jako zrealizowane'
     */
    void on_oznacz_clicked();

    /**
     * Metoda realizowana po naciśnięciu przycisku 'Szczegóły zamówienia'
     */
    void on_szczegoly_clicked();

    /**
     * Metoda aktualizująca listę zamówień po zmianie zakładki tabeli zamówienia
     */
    void zmien(int);

    /**
     * Metoda realizowana po dwukrotnym kliknięciu na zamówienie z tabeli
     */
    void openInfo(const QModelIndex &);

private:
    Ui::Zamowienia_pracownik *ui;
    Zamowienie_pracownik_info *zpi;
};

#endif // ZAMOWIENIA_PRACOWNIK_H
