#include "moje_zamowienia.h"
#include "ui_moje_zamowienia.h"
#include <QTableWidgetItem>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>

extern QSqlDatabase db;

Moje_zamowienia::Moje_zamowienia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Moje_zamowienia)
{
    ui->setupUi(this);
    QString login_ = this->parentWidget()->findChild<QLabel*>("login")->text();

    setWindowTitle("Moje zamowienia - uzytkownik: " + login_);
    ui->tableWidget->setColumnWidth(0,150);
    ui->tableWidget->setColumnWidth(1,80);
    ui->tableWidget->setColumnWidth(2,120);
    ui->tableWidget->setColumnWidth(3,170);

    zamowienia();
}

void Moje_zamowienia::zamowienia()
{
    QString login_ = this->parentWidget()->findChild<QLabel*>("login")->text();
    ui->login->setText(login_);

    int i = 0;
    QSqlQuery query(db);

    if(query.exec("SELECT * FROM wyszukaj_zamowienia('" + login_ + "')"))
    {
        while(query.next())
        {
            ui->tableWidget->insertRow(i);

            ui->tableWidget->setItem(i,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(query.value(3).toString()));
            i++;
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
