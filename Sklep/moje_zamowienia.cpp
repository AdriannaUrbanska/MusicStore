#include "moje_zamowienia.h"
#include "ui_moje_zamowienia.h"
#include <QTableWidgetItem>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QAbstractItemView>

extern QSqlDatabase db;

Moje_zamowienia::Moje_zamowienia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Moje_zamowienia)
{
    ui->setupUi(this);
    this->setWindowTitle("Moje zamówienia");
    QString login_ = this->parentWidget()->findChild<QLabel*>("login")->text();

    setWindowTitle("Moje zamowienia - uzytkownik: " + login_);
    ui->tab_zrealizowane->setColumnWidth(0,150);
    ui->tab_zrealizowane->setColumnWidth(1,80);
    ui->tab_zrealizowane->setColumnWidth(2,120);
    ui->tab_zrealizowane->setColumnWidth(3,160);

    ui->tab_w_trakcie->setColumnWidth(0,150);
    ui->tab_w_trakcie->setColumnWidth(1,80);
    ui->tab_w_trakcie->setColumnWidth(2,120);
    ui->tab_w_trakcie->setColumnWidth(3,160);

    zamowienia();

    ui->tab->setCurrentIndex(0);
    ui->tab_zrealizowane->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tab_zrealizowane->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tab_zrealizowane->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tab_zrealizowane->selectRow(0);

    ui->tab_w_trakcie->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tab_w_trakcie->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tab_w_trakcie->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tab_w_trakcie->selectRow(0);
}

void Moje_zamowienia::zamowienia()
{
    QString login_ = this->parentWidget()->findChild<QLabel*>("login")->text();
    ui->login->setText(login_);

    int i_w_trakcie = 0;
    int i_zrealizowane = 0;
    QSqlQuery query(db);

    if(query.exec("SELECT * FROM wyszukaj_zamowienia('" + login_ + "')"))
    {
        while(query.next())
        {
            if(query.value(3).toString() == "W trakcie realizacji")
            {
                ui->tab_w_trakcie->insertRow(i_w_trakcie);
                ui->tab_w_trakcie->setItem(i_w_trakcie,0,new QTableWidgetItem(query.value(0).toString()));
                ui->tab_w_trakcie->setItem(i_w_trakcie,1,new QTableWidgetItem(query.value(1).toString()));
                ui->tab_w_trakcie->setItem(i_w_trakcie,2,new QTableWidgetItem(query.value(2).toString()));
                ui->tab_w_trakcie->setItem(i_w_trakcie,3,new QTableWidgetItem(query.value(3).toString()));
                i_w_trakcie++;
            }
            else
            {
                ui->tab_zrealizowane->insertRow(i_zrealizowane);
                ui->tab_zrealizowane->setItem(i_zrealizowane,0,new QTableWidgetItem(query.value(0).toString()));
                ui->tab_zrealizowane->setItem(i_zrealizowane,1,new QTableWidgetItem(query.value(1).toString()));
                ui->tab_zrealizowane->setItem(i_zrealizowane,2,new QTableWidgetItem(query.value(2).toString()));
                ui->tab_zrealizowane->setItem(i_zrealizowane,3,new QTableWidgetItem(query.value(3).toString()));
                i_zrealizowane++;
            }
        }
    }
    else
        QMessageBox::warning(this, "Błąd", "Błąd połączenia!");
}

Moje_zamowienia::~Moje_zamowienia()
{
    delete ui;
}

void Moje_zamowienia::on_powrot_clicked()
{
    this->close();
}

void Moje_zamowienia::on_anuluj_clicked()
{

}

void Moje_zamowienia::on_ocena_clicked()
{
    o = new Ocena(this);
    o->show();
}
