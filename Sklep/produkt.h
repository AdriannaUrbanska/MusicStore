#ifndef PRODUKT_H
#define PRODUKT_H

#include <QDialog>
#include "zamowienie.h"

namespace Ui {
class Produkt;
}
/**
 *  Klasa Produkt okna informacji o produkcie dla klienta
 */
class Produkt : public QDialog
{
    Q_OBJECT

public:
    explicit Produkt(QWidget *parent = 0);
    ~Produkt();

private slots:
    /**
     * Metoda realizowana po naciśnięciu przycisku 'Zamawiam'
     */
    void on_zamawiam_clicked();

    /**
     * Metoda realizowana po naciśnięciu przycisku 'Powrót'
     */
    void on_powrot_clicked();

    /**
     * Metoda aktualizująca pola informacji o produkcie
     */
    void info();

private:
    Ui::Produkt *ui;

    Zamowienie * z;
};

#endif // PRODUKT_H
