#include "moje_zamowienia.h"
#include "ui_moje_zamowienia.h"

Moje_zamowienia::Moje_zamowienia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Moje_zamowienia)
{
    ui->setupUi(this);
    QString login = "";

    setWindowTitle("Moje zamowienia - uzytkownik: " + login);
}

Moje_zamowienia::~Moje_zamowienia()
{
    delete ui;
}

void Moje_zamowienia::on_powrot_clicked()
{
    this->close();
}

void Moje_zamowienia::on_wyloguj_clicked()
{
    this->close();
    this->parentWidget()->close();

    if (QString::fromUtf8(this->parentWidget()->parentWidget()->metaObject()->className()) == "Nowy_uzytkownik")
        this->parentWidget()->parentWidget()->parentWidget()->show();
    else
        this->parentWidget()->parentWidget()->show();
}
