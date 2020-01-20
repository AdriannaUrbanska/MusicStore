#ifndef SKLEP_PRACOWNIK_H
#define SKLEP_PRACOWNIK_H

#include <QDialog>
#include "zamowienia_pracownik.h"
#include "produkt_pracownik.h"
#include "dodaj_produkt.h"

namespace Ui {
class Sklep_pracownik;
}

class Sklep_pracownik : public QDialog
{
    Q_OBJECT

public:
    explicit Sklep_pracownik(QWidget *parent = 0);
    ~Sklep_pracownik();
protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_wyloguj_clicked();

    void on_zamowienia_clicked();

    void on_produkt_info_clicked();

    void on_dodaj_clicked();

    void on_wybierz_clicked();

    void produkty();

    void on_szukaj_clicked();

    void openProdukt(const QModelIndex &);

private:
    Ui::Sklep_pracownik *ui;

    Zamowienia_pracownik * z_p;
    Produkt_pracownik * p_p;
    Dodaj_produkt * d_p;
};

#endif // SKLEP_PRACOWNIK_H
