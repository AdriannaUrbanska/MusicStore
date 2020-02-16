#ifndef SKLEP_PRACOWNIK_H
#define SKLEP_PRACOWNIK_H

#include <QDialog>
#include "zamowienia_pracownik.h"
#include "produkt_pracownik.h"
#include "dodaj_produkt.h"

namespace Ui {
class Sklep_pracownik;
}

/**
 *  Klasa Sklep_pracownik okna głownego sklepu dla pracownika
 */
class Sklep_pracownik : public QDialog
{
    Q_OBJECT

public:
    explicit Sklep_pracownik(QWidget *parent = 0);
    ~Sklep_pracownik();
protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    /**
     * Metoda realizowana po naciśnięciu przycisku 'Wyloguj'
     */
    void on_wyloguj_clicked();

    /**
     * Metoda realizowana po naciśnięciu przycisku 'Zamówienia'
     */
    void on_zamowienia_clicked();

    /**
     * Metoda realizowana po naciśnięciu przycisku 'Informacje o produkcie'
     */
    void on_produkt_info_clicked();

    /**
     * Metoda realizowana po naciśnięciu przycisku 'Dodaj nowy produkt'
     */
    void on_dodaj_clicked();

    /**
     * Metoda realizowana po naciśnięciu przycisku 'Wybierz'
     */
    void on_wybierz_clicked();

    /**
     * Metoda aktualizująca listę produktów
     */
    void produkty();

    /**
     * Metoda realizowana po naciśnięciu przycisku 'Szukaj'
     */
    void on_szukaj_clicked();

    /**
     * Metoda realizowana dwukrotnym kliknięciu na produkt z listy
     */
    void openProdukt(const QModelIndex &);

private:
    Ui::Sklep_pracownik *ui;

    Zamowienia_pracownik * z_p;
    Produkt_pracownik * p_p;
    Dodaj_produkt * d_p;
};

#endif // SKLEP_PRACOWNIK_H
