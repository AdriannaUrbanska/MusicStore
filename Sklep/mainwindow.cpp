#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <iostream>
#include <QStringList>
#include <QString>
#include <stdlib.h>
#include <QSqlQuery>
#include <QDebug>
#include <QDate>
#include <libssh/libssh.h>

QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pokaz_haslo->setChecked(false);
   // ui->haslo->setEchoMode(QLineEdit::Password);
    ui->login->setEchoMode(QLineEdit::Normal);


    QDate date = QDate::currentDate();
    setWindowTitle("Sklep muzyczny " + date.toString("dd-MM-yyyy"));

    ui->radioKlient->setChecked(true);

    //connection();
}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

void MainWindow::on_pokaz_haslo_clicked()
{
    if(ui->pokaz_haslo->isChecked())
        ui->haslo->setEchoMode(QLineEdit::Normal);
    else
        ui->haslo->setEchoMode(QLineEdit::Password);
}

void MainWindow::on_zaloguj_clicked()
{
    QString login_ = ui->login->text();
    QString haslo_ = ui->haslo->text();
    bool poprawnosc = false;

//    QSqlQuery query(db);

    if(ui->radioKlient->isChecked())
    {
        s = new Sklep(this);
        this->close();
        s->show();

//    if(query.exec("SELECT login, haslo from klient"))
//    {
//        while(query.next())
//        {
//            if(username == query.value(0).toString() &&
//                    password == query.value(1).toString())
//            {
//                poprawnosc = true;
//                break;
//            }
//        }

//        if(poprawnosc)
//        {



//        }
//        else
//          QMessageBox::warning(this, "Logowanie", "Login lub hasło jest błędne!");
//

//    }
//    else
//        qDebug() <<"error";
    }
    else
    {
        s_p = new Sklep_pracownik(this);
        this->close();
        s_p->show();
    }

}

void MainWindow::connection()
{
    db.setConnectOptions();
    db.setHostName("localhost");
    db.setDatabaseName("project");
    db.setUserName("urbanska");
    db.setPassword("project");
    db.setPort(5432);
    bool ok = db.open();

    if(ok)
        QMessageBox::information(this, "Connection", "Connection OK");
    else
        QMessageBox::warning(this, "Connection", "ERROR");

//        QSqlQuery query(db);

//        if(query.exec("SELECT * from kurs1.kurs_opis"))
//        {
//            while(query.next())
//            {
//                qDebug()<<query.value(0).toString()<< " " << query.value(1).toString();
//            }

//        }
//        else
//            qDebug() <<"error";
}

void MainWindow::on_konto_clicked()
{
    n_u = new Nowy_uzytkownik(this);
    this->close();
    n_u->show();
}
