#ifndef PO_ZAMOWIENIU_H
#define PO_ZAMOWIENIU_H

#include <QDialog>

namespace Ui {
class Po_zamowieniu;
}

class Po_zamowieniu : public QDialog
{
    Q_OBJECT

public:
    explicit Po_zamowieniu(QWidget *parent = 0);
    ~Po_zamowieniu();

private slots:
    void on_powrot_clicked();

    void on_m_zamowienia_clicked();

private:
    Ui::Po_zamowieniu *ui;
};

#endif // PO_ZAMOWIENIU_H
