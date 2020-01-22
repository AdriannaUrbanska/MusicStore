#ifndef ZAMOWIENIA_PRACOWNIK_H
#define ZAMOWIENIA_PRACOWNIK_H

#include <QDialog>

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
private:
    Ui::Zamowienia_pracownik *ui;
};

#endif // ZAMOWIENIA_PRACOWNIK_H
