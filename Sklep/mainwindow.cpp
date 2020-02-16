#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QString>
#include <QSqlQuery>
#include <QDebug>
#include <QDate>

extern QSqlDatabase db;
extern void close();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pokaz_haslo->setChecked(false);
    ui->haslo->setEchoMode(QLineEdit::Password);
    ui->login->setEchoMode(QLineEdit::Normal);

    QDate date = QDate::currentDate();
    setWindowTitle("Sklep muzyczny " + date.toString("dd-MM-yyyy"));

    ui->radioKlient->setChecked(true);
}

MainWindow::~MainWindow()
{
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

    QSqlQuery query(db);

    if(ui->radioKlient->isChecked())
    {
        if(query.exec("SELECT * FROM sklep.uzytkownicy_K"))
        {
            while(query.next())
            {
                if(login_ == query.value(0).toString() &&
                        haslo_ == query.value(1).toString())
                {
                    poprawnosc = true;
                    break;
                }
            }

            if(poprawnosc)
            {
                s = new Sklep(this);
                this->hide();
                s->show();
            }
            else
              QMessageBox::warning(this, "Logowanie", "Login lub hasło jest błędne!");
        }
        else
            QMessageBox::warning(this, "Błąd", "Błąd połączenia!");
    }
    else
    {
        if(query.exec("SELECT * FROM sklep.uzytkownicy_P"))
        {
            while(query.next())
            {
                if(login_ == query.value(0).toString() &&
                        haslo_ == query.value(1).toString())
                {
                    poprawnosc = true;
                    break;
                }
            }

            if(poprawnosc)
            {
                s_p = new Sklep_pracownik(this);
                this->hide();
                s_p->show();
            }
            else
              QMessageBox::warning(this, "Logowanie", "Login lub hasło jest błędne!");
        }
        else
            QMessageBox::warning(this, "Błąd", "Błąd połączenia!");
    }
}


void MainWindow::on_konto_clicked()
{
    n_u = new Nowy_uzytkownik(this);
    this->hide();
    n_u->show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug()<<"CLOSE";
    db.close();
}
