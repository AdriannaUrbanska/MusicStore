#ifndef MOJE_ZAMOWIENIA_H
#define MOJE_ZAMOWIENIA_H

#include <QDialog>
#include "ocena.h"
#include "zamowienie_info.h"

namespace Ui {
class Moje_zamowienia;
}

class Moje_zamowienia : public QDialog
{
    Q_OBJECT

public:
    explicit Moje_zamowienia(QWidget *parent = 0);
    ~Moje_zamowienia();

private slots:
    void on_powrot_clicked();
    void zamowienia();

    void on_anuluj_clicked();

    void on_ocena_clicked();

    void on_info_clicked();

private:
    Ui::Moje_zamowienia *ui;
    Ocena *o;
    Zamowienie_info *zi;
};

#endif // MOJE_ZAMOWIENIA_H
