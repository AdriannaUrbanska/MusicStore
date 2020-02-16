#ifndef EDYTUJ_PRODUKT_H
#define EDYTUJ_PRODUKT_H

#include <QDialog>

namespace Ui {
class Edytuj_produkt;
}
/**
 *  Klasa Edytuj_produkt okna edytowania produktu.
 */
class Edytuj_produkt : public QDialog
{
    Q_OBJECT

public:
    explicit Edytuj_produkt(QWidget *parent = 0);
    ~Edytuj_produkt();

private slots:
    /**
     * Metoda realizowana po naciśnięciu przycisku 'Powrót'
     */
    void on_powrot_clicked();

    /**
     * Metoda realizowana po naciśnięciu przycisku 'Zapisz produkt'
     */
    void on_zapisz_clicked();

private:
    Ui::Edytuj_produkt *ui;
};

#endif // EDYTUJ_PRODUKT_H
