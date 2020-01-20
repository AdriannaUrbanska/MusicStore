#ifndef PRODUKT_H
#define PRODUKT_H

#include <QDialog>
#include "zamowienie.h"

namespace Ui {
class Produkt;
}

class Produkt : public QDialog
{
    Q_OBJECT

public:
    explicit Produkt(QWidget *parent = 0);
    ~Produkt();

private slots:
    void on_zamawiam_clicked();

    void on_powrot_clicked();

    void info();

private:
    Ui::Produkt *ui;

    Zamowienie * z;
};

#endif // PRODUKT_H
