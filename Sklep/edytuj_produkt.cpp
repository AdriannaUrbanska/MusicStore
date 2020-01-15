#include "edytuj_produkt.h"
#include "ui_edytuj_produkt.h"
#include <QMessageBox>

Edytuj_produkt::Edytuj_produkt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Edytuj_produkt)
{
    ui->setupUi(this);

    QString produkt_ = "produkt";
    QString opis_ = "opis";
    double cena_ = 1.00;
    int sztuki_ = 1;

    ui->kategoria->addItem("Kategoria1");
    ui->kategoria->addItem("Kategoria2");

    ui->produkt->setText(produkt_);
    ui->kategoria->setCurrentIndex(0);
    ui->opis->setText(opis_);
    ui->cena->setValue(cena_);
    ui->sztuki->setValue(sztuki_);
}

Edytuj_produkt::~Edytuj_produkt()
{
    delete ui;
}

void Edytuj_produkt::on_powrot_clicked()
{
    this->close();
}

void Edytuj_produkt::on_zapisz_clicked()
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, "Zapisz zmiany", "Jesteś pewien, że chcesz zapisać zmiany?", QMessageBox::Yes | QMessageBox::No);

    if (button == QMessageBox::Yes)
    {
        QMessageBox::information(this, "Zapisz zmiany", "Zmiany zostały zapisane!");
        this->close();
    }
}
