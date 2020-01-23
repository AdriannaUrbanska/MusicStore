#ifndef ZAMOWIENIE_INFO_H
#define ZAMOWIENIE_INFO_H

#include <QDialog>

namespace Ui {
class Zamowienie_info;
}

class Zamowienie_info : public QDialog
{
    Q_OBJECT

public:
    explicit Zamowienie_info(QWidget *parent = 0);
    ~Zamowienie_info();

private slots:

    void on_powrot_clicked();

    void info();

private:
    Ui::Zamowienie_info *ui;
};

#endif // ZAMOWIENIE_INFO_H
