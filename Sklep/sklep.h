#ifndef SKLEP_H
#define SKLEP_H

#include <QDialog>
#include "produkt.h"
#include "moje_zamowienia.h"
#include "mainwindow.h"

class Nowy_uzytkownik;

namespace Ui {
class Sklep;
}

class Sklep : public QDialog
{
    Q_OBJECT

public:
    explicit Sklep(QWidget *parent = 0);
    ~Sklep();
protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_m_zamowienia_clicked();

    void on_produkt_info_clicked();

    void on_wyloguj_clicked();

    void produkty();

    void on_wybierz_clicked();

    void on_szukaj_clicked();

    void openProdukt(const QModelIndex &);

private:
    Ui::Sklep *ui;

    Produkt * p;
    Moje_zamowienia * m_z;
};

#endif // SKLEP_H
