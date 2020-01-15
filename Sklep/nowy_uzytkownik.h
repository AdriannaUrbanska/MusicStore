#ifndef NOWY_UZYTKOWNIK_H
#define NOWY_UZYTKOWNIK_H

#include <QDialog>
#include "sklep.h"

namespace Ui {
class Nowy_uzytkownik;
}

class Nowy_uzytkownik : public QDialog
{
    Q_OBJECT

public:
    explicit Nowy_uzytkownik(QWidget *parent = 0);
    ~Nowy_uzytkownik();

private slots:
    void on_powrot_clicked();

    void on_utworz_konto_clicked();

private:
    Ui::Nowy_uzytkownik *ui;

    Sklep *s;
};

#endif // NOWY_UZYTKOWNIK_H
