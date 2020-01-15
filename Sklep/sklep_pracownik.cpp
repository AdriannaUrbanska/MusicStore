#include "sklep_pracownik.h"
#include "ui_sklep_pracownik.h"
#include <QDate>

Sklep_pracownik::Sklep_pracownik(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sklep_pracownik)
{
    ui->setupUi(this);

    QDate date = QDate::currentDate();
    setWindowTitle("Sklep muzyczny " + date.toString("dd-MM-yyyy"));
}

Sklep_pracownik::~Sklep_pracownik()
{
    delete ui;
}

void Sklep_pracownik::on_wyloguj_clicked()
{
    this->close();
    this->parentWidget()->show();
}

void Sklep_pracownik::on_zamowienia_clicked()
{
    z_p = new Zamowienia_pracownik(this);
    z_p->show();
}

void Sklep_pracownik::on_produkt_info_clicked()
{
    p_p = new Produkt_pracownik(this);
    p_p->show();
}

void Sklep_pracownik::on_dodaj_clicked()
{
    d_p = new Dodaj_produkt(this);
    d_p->show();
}
