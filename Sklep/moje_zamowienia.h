#ifndef MOJE_ZAMOWIENIA_H
#define MOJE_ZAMOWIENIA_H

#include <QDialog>
#include "ocena.h"
#include "zamowienie_info.h"

namespace Ui {
class Moje_zamowienia;
}
/**
 *  Moje_zamowienia okna listy zamówień klienta
 */
class Moje_zamowienia : public QDialog
{
    Q_OBJECT

public:
    explicit Moje_zamowienia(QWidget *parent = 0);
    ~Moje_zamowienia();
    int i_w_trakcie;
    int i_zrealizowane;

private slots:
    /**
     * Metoda realizowana po naciśnięciu przycisku 'Powrót'
     */
    void on_powrot_clicked();

    /**
     * Metoda aktualizująca listy zamówień w trakcie oraz zrealizowanych
     */
    void zamowienia();

    /**
     * Metoda realizowana po naciśnięciu przycisku 'Anuluj zamówienie'
     */
    void on_anuluj_clicked();

    /**
     * Metoda realizowana po naciśnięciu przycisku 'Oceń zamówienie'
     */
    void on_ocena_clicked();

    /**
     * Metoda realizowana po naciśnięciu przycisku 'Więcej informacji o zamówieniu'
     */
    void on_info_clicked();

    /**
     * Metoda realizowana po zmianie zakładki tabeli zamówienia
     */
    void zmien(int);

    /**
     * Metoda po dwukrotnym naciśnięciu wiersza z zamówieniem
     */
    void openInfo(const QModelIndex &);

private:
    Ui::Moje_zamowienia *ui;
    Ocena *o;
    Zamowienie_info *zi;
};

#endif // MOJE_ZAMOWIENIA_H
