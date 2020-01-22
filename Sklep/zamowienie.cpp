#include "zamowienie.h"
#include "ui_zamowienie.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

extern QSqlDatabase db;


Zamowienie::Zamowienie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Zamowienie)
{
    ui->setupUi(this);

    setWindowTitle("Zamówienie");

    QString produkt_ = this->parentWidget()->findChild<QLabel *>("produkt")->text();
    int len_ = this->parentWidget()->findChild<QLabel *>("cena")->text().length();
    cena_ = this->parentWidget()->findChild<QLabel *>("cena")->text().left(len_ - 2).toDouble();
    int sztuki_ = this->parentWidget()->findChild<QLabel *>("sztuki")->text().toInt();
    QString dostawa_ = ui->dostawa->currentText();

    QSqlQuery query(db);

    if(query.exec("SELECT opcja_dostawy, cena_dostawy, czas_oczekiwania FROM przesylka"))
    {
        while(query.next())
        {
            ui->dostawa->addItem(query.value(0).toString());
            v_cena.push_back(query.value(1).toString());
            v_czas.push_back(query.value(2).toString());
        }
    }
    else
        QMessageBox::warning(this, "Błąd", "Błąd połączenia!");

    ui->produkt->setText(produkt_);
    ui->cena->setText(QString::number(cena_) + "zł");

    ui->sztuki->setMinimum(1);
    ui->sztuki->setMaximum(sztuki_);

    ustaw();
    connect(ui->dostawa, SIGNAL(activated(int)), this, SLOT(ustaw(int)));
    connect(ui->sztuki, SIGNAL(valueChanged(int)), this, SLOT(ustaw(int)));
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

void Zamowienie::ustaw(int)
{
    int idx = ui->dostawa->currentIndex();

    ui->cena_dostawy->setText(v_cena[idx] + "zł");
    ui->czas->setText(v_czas[idx]);
    int n = ui->sztuki->text().toInt();
    ui->do_zaplaty->setText(QString::number(v_cena[idx].toDouble() + n * cena_) + "zł");
}

