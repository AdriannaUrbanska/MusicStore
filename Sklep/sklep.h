#ifndef SKLEP_H
#define SKLEP_H

#include <QDialog>
#include "produkt.h"
#include "moje_zamowienia.h"
#include "mainwindow.h"
#include "sklep_info.h"

class Nowy_uzytkownik;

namespace Ui {
class Sklep;
}
/**
 *  Klasa Sklep okna głównego sklepu dla klienta
 */
class Sklep : public QDialog
{
    Q_OBJECT

public:
    explicit Sklep(QWidget *parent = 0);
    QString login_;
    ~Sklep();
protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    /**
     * Metoda realizowana po naciśnięciu przycisku 'Moje zamówienia'
     */
    void on_m_zamowienia_clicked();

    /**
     * Metoda realizowana po naciśnięciu przycisku 'Informacje o produkcie'
     */
    void on_produkt_info_clicked();

    /**
     * Metoda realizowana po naciśnięciu przycisku 'Wyloguj'
     */
    void on_wyloguj_clicked();

    /**
     * Metoda aktualizująca listę produktów
     */
    void produkty();

    /**
     * Metoda realizowana po naciśnięciu przycisku 'Wybierz'
     */
    void on_wybierz_clicked();

    /**
     * Metoda realizowana po naciśnięciu przycisku 'Szukaj'
     */
    void on_szukaj_clicked();

    /**
     * Metoda realizowana po dwukrotnym kliknięciu na produkt z listy
     */
    void openProdukt(const QModelIndex &);

    /**
     * Metoda realizowana po naciśnięciu przycisku 'Informacje o sklepie'
     */
    void on_sklep_info_clicked();

private:
    Ui::Sklep *ui;

    Produkt * p;
    Moje_zamowienia * m_z;
    Sklep_info *si;
};

#endif // SKLEP_H
