#include "zamowienie.h"
#include "ui_zamowienie.h"

Zamowienie::Zamowienie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Zamowienie)
{
    ui->setupUi(this);

    setWindowTitle("Zamówienie");

    QString produkt_ = "produkt";
    double cena_ = 1.2;
    int sztuki_ = ui->sztuki->value();
    QString dostawa_ = ui->dostawa->currentText();
    QString platnosc_ = ui->platnosc->currentText();
    double cena_dostawy_ = 1.2;
    QString czas_ = "czas";
    double do_zaplaty_ = cena_ + cena_dostawy_;

    ui->produkt->setText(produkt_);
    ui->cena->setText(QString::number(cena_));
    ui->cena_dostawy->setText(QString::number(cena_dostawy_));
    ui->czas->setText(czas_);
    ui->do_zaplaty->setText(QString::number(do_zaplaty_));
}

Zamowienie::~Zamowienie()
{
    delete ui;
}

void Zamowienie::on_powrot_clicked()
{
    this->close();
}

void Zamowienie::on_zamawiam_clicked()
{
    p_z = new Po_zamowieniu(this);
    p_z->show();
}
