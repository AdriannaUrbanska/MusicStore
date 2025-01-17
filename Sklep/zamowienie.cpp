#include "zamowienie.h"
#include "ui_zamowienie.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDate>
#include <QDebug>

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

    if(query.exec("SELECT opcja_dostawy, cena_dostawy, czas_oczekiwania FROM sklep.przesylka"))
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
    QSqlQuery query(db);
    QString id_;
    QString login_ = parentWidget()->parentWidget()->findChild<QLabel*>("login")->text();
    QString id_przesylka_ = QString::number(ui->dostawa->currentIndex()+1);
    QString liczba_sztuk_ = QString::number(ui->sztuki->value());
    int len_ = ui->do_zaplaty->text().length();
    QString do_zaplaty_ = ui->do_zaplaty->text().left(len_ - 2);
    QString data_zamowienia_ = QDate::currentDate().toString("dd-MM-yyyy");
    QString produkt_ = ui->produkt->text();

    if(query.exec("SELECT * FROM sklep.id_zamowienie_next"))
    {
        while(query.next())
        {
            id_ = query.value(0).toString();
        }
    }
    else
        QMessageBox::warning(this, "Błąd", "Błąd połączenia!1");

    if(id_ == "")
        id_ = '1';

    if(query.exec("INSERT INTO sklep.zamowienie(id_zamowienie, login, id_przesylka, liczba_sztuk, do_zaplaty, data_zamowienia) VALUES(" +
                   id_ + ", '" + login_ + "', " + id_przesylka_ + ", "
                   + liczba_sztuk_ + ", " + do_zaplaty_ + ", '" + data_zamowienia_ + "')"))
    {
        if(query.exec("INSERT INTO sklep.produkt_zamowienie VALUES(" + id_ + ", '" + produkt_ + "')"))
        {
            QMessageBox::information(this, "Zamówienie", "Zamówienie zostało przyjęte!");
            p_z = new Po_zamowieniu(this);
            p_z->show();
        }
        else
            QMessageBox::warning(this, "Błąd", "Błąd połączenia!2");
    }
    else
        QMessageBox::warning(this, "Błąd", "Błąd połączenia!3");


    if(!query.exec("SELECT * FROM sklep.sztuki('" + produkt_ + "', " + liczba_sztuk_ + ")"))
    {
        QMessageBox::warning(this, "Błąd", "Błąd połączenia!4");
    }
}

void Zamowienie::ustaw(int)
{
    int idx = ui->dostawa->currentIndex();

    ui->cena_dostawy->setText(v_cena[idx] + "zł");
    ui->czas->setText(v_czas[idx]);
    int n = ui->sztuki->text().toInt();
    ui->do_zaplaty->setText(QString::number(v_cena[idx].toDouble() + n * cena_) + "zł");
}

