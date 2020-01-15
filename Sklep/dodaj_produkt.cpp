#include "dodaj_produkt.h"
#include "ui_dodaj_produkt.h"
#include <QMessageBox>

Dodaj_produkt::Dodaj_produkt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dodaj_produkt)
{
    ui->setupUi(this);
}

Dodaj_produkt::~Dodaj_produkt()
{
    delete ui;
}

void Dodaj_produkt::on_powrot_clicked()
{
    this->close();
}

void Dodaj_produkt::on_dodaj_clicked()
{
    QString produkt_ = ui->produkt->text();
    QString opis_ = ui->opis->text();
    QString kategoria_ = ui->kategoria->currentText();
    double cena_ = ui->cena->value();
    int sztuki_ = ui->sztuk->value();

    QMessageBox::information(this, "Dodaj produkt", "Produkt został dodany!");
    this->close();
}
