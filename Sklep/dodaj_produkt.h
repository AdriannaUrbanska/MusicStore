#ifndef DODAJ_PRODUKT_H
#define DODAJ_PRODUKT_H

#include <QDialog>

namespace Ui {
class Dodaj_produkt;
}

class Dodaj_produkt : public QDialog
{
    Q_OBJECT

public:
    explicit Dodaj_produkt(QWidget *parent = 0);
    ~Dodaj_produkt();

private slots:
    void on_powrot_clicked();

    void on_dodaj_clicked();

private:
    Ui::Dodaj_produkt *ui;
};

#endif // DODAJ_PRODUKT_H
