#include "zamowienia_pracownik.h"
#include "ui_zamowienia_pracownik.h"

Zamowienia_pracownik::Zamowienia_pracownik(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Zamowienia_pracownik)
{
    ui->setupUi(this);
    ui->wszystkie->setChecked(true);
}

Zamowienia_pracownik::~Zamowienia_pracownik()
{
    delete ui;
}

void Zamowienia_pracownik::on_powrot_clicked()
{
    this->close();
}
