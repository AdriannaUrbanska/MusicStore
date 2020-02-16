#ifndef ZAMOWIENIE_H
#define ZAMOWIENIE_H

#include <QDialog>
#include <vector>
#include <QString>
#include "po_zamowieniu.h"

namespace Ui {
class Zamowienie;
}
/**
 *  Klasa Zamowienie okna zamawiania konkretnego produktu przez klienta
 */
class Zamowienie : public QDialog
{
    Q_OBJECT

public:
    explicit Zamowienie(QWidget *parent = 0);
    ~Zamowienie();
    std::vector <QString> v_cena;
    std::vector <QString> v_czas;
    double cena_;

private slots:
    /**
     * Metoda realizowana po naciśnięciu przycisku 'Powrót'
     */
    void on_powrot_clicked();

    /**
     * Metoda realizowana po naciśnięciu przycisku 'Zamawiam'
     */
    void on_zamawiam_clicked();

    /**
     * Metoda aktualizująca pola informacji o produkcie
     */
    void ustaw(int = 1);

private:
    Ui::Zamowienie *ui;

    Po_zamowieniu * p_z;
};

#endif // ZAMOWIENIE_H
