#include "produkt.h"
#include "ui_produkt.h"

Produkt::Produkt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Produkt)
{
    ui->setupUi(this);

    QString produkt = "";
    setWindowTitle("Produkt: " + produkt);

    QString produkt_ = "produkt";
    QString opis_ = "opis";
    QString kategoria_ = "kategoria";
    double cena_ = 1.2;
    int sztuki_ = 1;

    ui->produkt->setText(produkt_);
    ui->kategoria->setText(kategoria_);
    ui->opis->setText(opis_);
    ui->cena->setText(QString::number(cena_) + "zł");
    ui->sztuki->setText(QString::number(sztuki_));
}

Produkt::~Produkt()
{
    delete ui;
}

void Produkt::on_zamawiam_clicked()
{
    z = new Zamowienie(this);
    z->show();
}

void Produkt::on_powrot_clicked()
{
    this->close();
}
