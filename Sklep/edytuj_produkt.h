#ifndef EDYTUJ_PRODUKT_H
#define EDYTUJ_PRODUKT_H

#include <QDialog>

namespace Ui {
class Edytuj_produkt;
}

class Edytuj_produkt : public QDialog
{
    Q_OBJECT

public:
    explicit Edytuj_produkt(QWidget *parent = 0);
    ~Edytuj_produkt();

private slots:
    void on_powrot_clicked();

    void on_zapisz_clicked();

private:
    Ui::Edytuj_produkt *ui;
};

#endif // EDYTUJ_PRODUKT_H
