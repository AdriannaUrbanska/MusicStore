#include "sklep_info.h"
#include "ui_sklep_info.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QRadioButton>
#include <QSqlQuery>
#include <QMessageBox>

extern QSqlDatabase db;

Sklep_info::Sklep_info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sklep_info)
{
    ui->setupUi(this);
    ui->opis->setWordWrap(true);
    setWindowTitle("Informacje o sklepie");

    ustaw();
}

Sklep_info::~Sklep_info()
{
    delete ui;
}

void Sklep_info::on_powrot_clicked()
{
    this->close();
}

void Sklep_info::ustaw()
{
    QSqlQuery query(db);

    QString id_adres_ = "";
    QString nazwa_ = "";
    QString opis_ = "";
    QString email_ = "";
    QString telefon_ = "";
    QString ulica_ = "";
    QString budynek_ = "";
    QString mieszkanie_ = "";
    QString miasto_ = "";
    QString kod_ = "";
    QString kraj_ = "";

    if(query.exec("SELECT * FROM sklep.sklep_info WHERE id_sklep = 1"))
    {
        while(query.next())
        {
            id_adres_ = query.value(1).toString();
            nazwa_ = query.value(2).toString();
            telefon_ = query.value(3).toString();
            email_ = query.value(4).toString();
            opis_ = query.value(5).toString();
        }
    }
    else
        QMessageBox::warning(this, "Błąd", "Błąd połączenia!");

    if(query.exec("SELECT * FROM sklep.adres WHERE id_adres = " + id_adres_))
    {
        while(query.next())
        {
            ulica_ = query.value(1).toString();
            budynek_ = query.value(2).toString();
            mieszkanie_ = query.value(3).toString();
            kod_ = query.value(4).toString();
            miasto_ = query.value(5).toString();
            kraj_ = query.value(6).toString();
        }
    }
    else
        QMessageBox::warning(this, "Błąd", "Błąd połączenia!");

    ui->nazwa->setText(nazwa_);
    ui->opis->setText(opis_);
    ui->email->setText(email_);
    ui->telefon->setText(telefon_);
    ui->ulica->setText(ulica_);
    ui->budynek->setText(budynek_);
    ui->mieszkanie->setText(mieszkanie_);
    ui->miasto->setText(miasto_);
    ui->kod->setText(kod_);
    ui->kraj->setText(kraj_);
}
