#ifndef MOJE_ZAMOWIENIA_H
#define MOJE_ZAMOWIENIA_H

#include <QDialog>

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

private:
    Ui::Moje_zamowienia *ui;
};

#endif // MOJE_ZAMOWIENIA_H
