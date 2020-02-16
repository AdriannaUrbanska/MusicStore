#ifndef DODAJ_PRODUKT_H
#define DODAJ_PRODUKT_H

#include <QDialog>


namespace Ui {
class Dodaj_produkt;
}
/**
 *  Klasa Dodaj_produkt okna dodawania nowego produktu do bazy.
 */
class Dodaj_produkt : public QDialog
{
    Q_OBJECT

public:
    explicit Dodaj_produkt(QWidget *parent = 0);
    ~Dodaj_produkt();

private slots:
    /**
     * Metoda realizowana po naciśnięciu przycisku 'Powrót'
     */
    void on_powrot_clicked();

    /**
     * Metoda realizowana po naciśnięciu przycisku 'Dodaj produkt'
     */
    void on_dodaj_clicked();

private:
    Ui::Dodaj_produkt *ui;
};

#endif // DODAJ_PRODUKT_H
