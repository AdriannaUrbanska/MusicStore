#ifndef ZAMOWIENIE_H
#define ZAMOWIENIE_H

#include <QDialog>
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

private slots:
    void on_powrot_clicked();

    void on_zamawiam_clicked();

private:
    Ui::Zamowienie *ui;

    Po_zamowieniu * p_z;
};

#endif // ZAMOWIENIE_H
