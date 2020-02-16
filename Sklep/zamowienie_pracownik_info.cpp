#include "zamowienie_pracownik_info.h"
#include "ui_zamowienie_pracownik_info.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QTableWidget>

extern QSqlDatabase db;

Zamowienie_pracownik_info::Zamowienie_pracownik_info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Zamowienie_pracownik_info)
{
    ui->setupUi(this);
    setWindowTitle("Informacje o zamówieniu");
    ui->opis->setWordWrap(true);

    info();
}

Zamowienie_pracownik_info::~Zamowienie_pracownik_info()
{
    delete ui;
}

void Zamowienie_pracownik_info::on_powrot_clicked()
{
    this->close();
}

void Zamowienie_pracownik_info::info()
{
    QString id_ = "";
    QString login_ = "";

    int tab_idx = parentWidget()->findChild<QTabWidget*>("tab")->currentIndex();
    int idx;

    if(tab_idx == 0)
    {
        idx = parentWidget()->findChild<QTableWidget*>("tab_w_trakcie")->currentRow();
        id_ = this->parentWidget()->findChild<QTableWidget*>("tab_w_trakcie")->item(idx,0)->text();
        login_ = this->parentWidget()->findChild<QTableWidget*>("tab_w_trakcie")->item(idx,1)->text();
    }
    else
    {
        idx = parentWidget()->findChild<QTableWidget*>("tab_zrealizowane")->currentRow();
        id_ = this->parentWidget()->findChild<QTableWidget*>("tab_zrealizowane")->item(idx,0)->text();
        login_ = this->parentWidget()->findChild<QTableWidget*>("tab_zrealizowane")->item(idx,1)->text();
    }


    QString produkt_ = "";
    QString kategoria_ = "";
    QString opis_ = "";
    QString cena_ = "";
    QString sztuki_ = "";
    QString przesylka_ = "";
    QString cena_przesylki_ = "";
    QString do_zaplaty_ = "";
    QString data_ = "";
    QString status_ = "";

    QSqlQuery query(db);

    if(query.exec("SELECT * FROM sklep.wyszukaj_zamowienia('" + login_ + "', " + id_ + ")"))
    {
        while(query.next())
        {
            produkt_ = query.value(2).toString();
            kategoria_ = query.value(3).toString();
            opis_ = query.value(4).toString();
            cena_ = query.value(5).toString();
            sztuki_ = query.value(6).toString();
            przesylka_ = query.value(7).toString();
            cena_przesylki_ = query.value(8).toString();
            do_zaplaty_ = query.value(9).toString();
            data_ = query.value(10).toString();
            status_ = query.value(11).toString();
        }
    }
    else
        QMessageBox::warning(this, "Błąd", "Błąd połączenia!");

    if(opis_ == "")
        opis_ = "Brak opisu";

    ui->id->setText(id_);
    ui->login->setText(login_);
    ui->produkt->setText(produkt_);
    ui->kategoria->setText(kategoria_);
    ui->opis->setText(opis_);
    ui->cena->setText(cena_ + "zł");
    ui->sztuki->setText(sztuki_);
    ui->przesylka->setText(przesylka_);
    ui->cena_przesylki->setText(cena_przesylki_ + "zł");
    ui->do_zaplaty->setText(do_zaplaty_ + "zł");
    ui->data_zamowienia->setText(data_);
    ui->status->setText(status_);
}
