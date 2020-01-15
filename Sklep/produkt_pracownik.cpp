#include "produkt_pracownik.h"
#include "ui_produkt_pracownik.h"
#include <QMessageBox>
#include <QAbstractButton>
#include <QDebug>

Produkt_pracownik::Produkt_pracownik(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Produkt_pracownik)
{
    ui->setupUi(this);

    QString produkt_ = "produkt";
    QString opis_ = "opis";
    QString kategoria_ = "kategoria";
    double cena_ = 1.00;
    int sztuki_ = 1;

    ui->produkt->setText(produkt_);
    ui->kategoria->setText(kategoria_);
    ui->opis->setText(opis_);
    ui->cena->setText(QString::number(cena_));
    ui->sztuki->setText(QString::number(sztuki_));
}

Produkt_pracownik::~Produkt_pracownik()
{
    delete ui;
}

void Produkt_pracownik::on_powrot_clicked()
{
    this->close();
}

void Produkt_pracownik::on_edytuj_clicked()
{
    e_p = new Edytuj_produkt(this);
    e_p->show();
}

void Produkt_pracownik::on_usun_clicked()
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, "Usuń produkt", "Jesteś pewien, że chcesz usunąć ten produkt?", QMessageBox::Yes | QMessageBox::No);

    if (button == QMessageBox::Yes)
    {
        QMessageBox::information(this, "Usuń produkt", "Produkt został usunięty!");
        this->close();
    }
}
