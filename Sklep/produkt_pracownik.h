#ifndef PRODUKT_PRACOWNIK_H
#define PRODUKT_PRACOWNIK_H

#include <QDialog>
#include "edytuj_produkt.h"

namespace Ui {
class Produkt_pracownik;
}

class Produkt_pracownik : public QDialog
{
    Q_OBJECT

public:
    explicit Produkt_pracownik(QWidget *parent = 0);
    ~Produkt_pracownik();

private slots:
    void on_powrot_clicked();

    void on_edytuj_clicked();

    void on_usun_clicked();

private:
    Ui::Produkt_pracownik *ui;

    Edytuj_produkt * e_p;
};

#endif // PRODUKT_PRACOWNIK_H
