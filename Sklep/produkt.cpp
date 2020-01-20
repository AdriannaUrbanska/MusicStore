#include "produkt.h"
#include "ui_produkt.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QListWidget>

extern QSqlDatabase db;

Produkt::Produkt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Produkt)
{
    ui->setupUi(this);

    QString produkt = "";
    setWindowTitle("Produkt: " + produkt);
    ui->opis->setWordWrap(true);

    info();
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

void Produkt::info()
{
    QString produkt_ = this->parentWidget()->findChild<QListWidget*>("listWidget")->currentItem()->text();
    QString kategoria_{""};
    QString opis_{""};
    QString cena_{""};
    QString sztuki_{""};
    QString ocena_{""};

    QSqlQuery query(db);

    if(query.exec("SELECT * FROM produkty WHERE n LIKE '" + produkt_ + "'"))
    {
        while(query.next())
        {
            kategoria_ = query.value(1).toString();
            opis_ = query.value(2).toString();
            cena_ = query.value(3).toString() + "zł";
            sztuki_ = query.value(4).toString();
        }
    }
    else
        QMessageBox::warning(this, "Błąd", "Błąd połączenia!");

    if(opis_ == "") opis_ = "Brak opisu";
    if(cena_ == "0zł") cena_ = "Brak ceny";
    if(sztuki_ == "0") sztuki_ = "Brak dostępnych sztuk";
    if(ocena_ == "") ocena_ = "Brak ocen";

    ui->produkt->setText(produkt_);
    ui->kategoria->setText(kategoria_);
    ui->opis->setText(opis_);
    ui->cena->setText(cena_);
    ui->sztuki->setText(sztuki_);
    ui->ocena->setText(ocena_);
}
