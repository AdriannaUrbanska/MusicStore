#ifndef ZAMOWIENIA_PRACOWNIK_H
#define ZAMOWIENIA_PRACOWNIK_H

#include <QDialog>
#include "zamowienie_pracownik_info.h"

namespace Ui {
class Zamowienia_pracownik;
}

class Zamowienia_pracownik : public QDialog
{
    Q_OBJECT

public:
    explicit Zamowienia_pracownik(QWidget *parent = 0);
    ~Zamowienia_pracownik();

private slots:
    void on_powrot_clicked();

    void zamowienia();
    void on_oznacz_clicked();

    void on_szczegoly_clicked();

private:
    Ui::Zamowienia_pracownik *ui;
    Zamowienie_pracownik_info *zpi;
};

#endif // ZAMOWIENIA_PRACOWNIK_H
