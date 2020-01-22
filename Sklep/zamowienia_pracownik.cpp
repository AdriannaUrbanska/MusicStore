#include "zamowienia_pracownik.h"
#include "ui_zamowienia_pracownik.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>

extern QSqlDatabase db;

Zamowienia_pracownik::Zamowienia_pracownik(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Zamowienia_pracownik)
{
    ui->setupUi(this);

    ui->tab_w_trakcie->setColumnWidth(0,40);
    ui->tab_w_trakcie->setColumnWidth(1,100);
    ui->tab_w_trakcie->setColumnWidth(2,100);
    ui->tab_w_trakcie->setColumnWidth(3,60);
    ui->tab_w_trakcie->setColumnWidth(4,100);
    ui->tab_w_trakcie->setColumnWidth(5,150);

    ui->tab_zrealizowane->setColumnWidth(0,40);
    ui->tab_zrealizowane->setColumnWidth(1,100);
    ui->tab_zrealizowane->setColumnWidth(2,100);
    ui->tab_zrealizowane->setColumnWidth(3,60);
    ui->tab_zrealizowane->setColumnWidth(4,100);
    ui->tab_zrealizowane->setColumnWidth(5,150);

    zamowienia();
}

Zamowienia_pracownik::~Zamowienia_pracownik()
{
    delete ui;
}

void Zamowienia_pracownik::on_powrot_clicked()
{
    this->close();
}

void Zamowienia_pracownik::zamowienia()
{
    int i_w_trakcie = 0;
    int i_zrealizowane = 0;

    QSqlQuery query(db);

    if(query.exec("SELECT * FROM wszystkie_zamowienia()"))
    {
        while(query.next())
        {
            if(query.value(5).toString() == "W trakcie realizacji")
            {
                ui->tab_w_trakcie->insertRow(i_w_trakcie);
                ui->tab_w_trakcie->setItem(i_w_trakcie,0,new QTableWidgetItem(query.value(0).toString()));
                ui->tab_w_trakcie->setItem(i_w_trakcie,1,new QTableWidgetItem(query.value(1).toString()));
                ui->tab_w_trakcie->setItem(i_w_trakcie,2,new QTableWidgetItem(query.value(2).toString()));
                ui->tab_w_trakcie->setItem(i_w_trakcie,3,new QTableWidgetItem(query.value(3).toString()));
                ui->tab_w_trakcie->setItem(i_w_trakcie,4,new QTableWidgetItem(query.value(4).toString()));
                ui->tab_w_trakcie->setItem(i_w_trakcie,5,new QTableWidgetItem(query.value(5).toString()));
                i_w_trakcie++;
            }
            else
            {
                ui->tab_zrealizowane->insertRow(i_zrealizowane);
                ui->tab_zrealizowane->setItem(i_zrealizowane,0,new QTableWidgetItem(query.value(0).toString()));
                ui->tab_zrealizowane->setItem(i_zrealizowane,1,new QTableWidgetItem(query.value(1).toString()));
                ui->tab_zrealizowane->setItem(i_zrealizowane,2,new QTableWidgetItem(query.value(2).toString()));
                ui->tab_zrealizowane->setItem(i_zrealizowane,3,new QTableWidgetItem(query.value(3).toString()));
                ui->tab_zrealizowane->setItem(i_zrealizowane,4,new QTableWidgetItem(query.value(4).toString()));
                ui->tab_zrealizowane->setItem(i_zrealizowane,5,new QTableWidgetItem(query.value(5).toString()));
                i_zrealizowane++;
            }
        }
    }
    else
        QMessageBox::warning(this, "Błąd", "Błąd połączenia!");
}
