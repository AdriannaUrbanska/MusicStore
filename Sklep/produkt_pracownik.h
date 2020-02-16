#ifndef PRODUKT_PRACOWNIK_H
#define PRODUKT_PRACOWNIK_H

#include <QDialog>
#include "edytuj_produkt.h"

namespace Ui {
class Produkt_pracownik;
}
/**
 *  Klasa Produkt_pracownik okna wyświetlającego informacje o produkcie dla pracownika
 */
class Produkt_pracownik : public QDialog
{
    Q_OBJECT

public:
    explicit Produkt_pracownik(QWidget *parent = 0);
    ~Produkt_pracownik();

private slots:
    /**
     * Metoda realizowana po naciśnięciu przycisku 'Powrót'
     */
    void on_powrot_clicked();

    /**
     * Metoda realizowana po naciśnięciu przycisku 'Edytuj produkt'
     */
    void on_edytuj_clicked();

    /**
     * Metoda realizowana po naciśnięciu przycisku 'Usuń produkt'
     */
    void on_usun_clicked();

    /**
     * Metoda aktualizująca pola informacji o produkcie
     */
    void info();

private:
    Ui::Produkt_pracownik *ui;

    Edytuj_produkt * e_p;
};

#endif // PRODUKT_PRACOWNIK_H
