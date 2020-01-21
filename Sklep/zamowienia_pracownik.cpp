#include "zamowienia_pracownik.h"
#include "ui_zamowienia_pracownik.h"

Zamowienia_pracownik::Zamowienia_pracownik(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Zamowienia_pracownik)
{
    ui->setupUi(this);
    ui->wszystkie->setChecked(true);

    ui->tableWidget->setColumnWidth(0,30);
    ui->tableWidget->setColumnWidth(1,60);
    ui->tableWidget->setColumnWidth(2,60);
    ui->tableWidget->setColumnWidth(3,150);
    ui->tableWidget->setColumnWidth(4,60);
    ui->tableWidget->setColumnWidth(5,150);
}

Zamowienia_pracownik::~Zamowienia_pracownik()
{
    delete ui;
}

void Zamowienia_pracownik::on_powrot_clicked()
{
    this->close();
}
