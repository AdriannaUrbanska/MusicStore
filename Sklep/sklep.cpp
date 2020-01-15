#include "sklep.h"
#include "ui_sklep.h"
#include <QListWidget>
#include <QDate>
#include "nowy_uzytkownik.h"
#include <QDebug>

Sklep::Sklep(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sklep)
{
    ui->setupUi(this);
    ui->listWidget->addItem("Fortepian YAMAHA");
    ui->listWidget->addItem("Fortepian ROLAND");

    QDate date = QDate::currentDate();
    setWindowTitle("Sklep muzyczny " + date.toString("dd-MM-yyyy"));
}

Sklep::~Sklep()
{
    delete ui;
}

void Sklep::on_m_zamowienia_clicked()
{
    m_z = new Moje_zamowienia(this);
    m_z->show();
}

void Sklep::on_produkt_info_clicked()
{
    p = new Produkt(this);
    p->show();
}

void Sklep::on_wyloguj_clicked()
{
    this->close();

    if (QString::fromUtf8(this->parentWidget()->metaObject()->className()) == "Nowy_uzytkownik")
        this->parentWidget()->parentWidget()->show();
    else
        this->parentWidget()->show();
}
