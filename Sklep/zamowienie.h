#ifndef ZAMOWIENIE_H
#define ZAMOWIENIE_H

#include <QDialog>
#include <vector>
#include <QString>
#include "po_zamowieniu.h"

namespace Ui {
class Zamowienie;
}

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
    void on_powrot_clicked();

    void on_zamawiam_clicked();

    void ustaw(int = 1);

private:
    Ui::Zamowienie *ui;

    Po_zamowieniu * p_z;
};

#endif // ZAMOWIENIE_H
