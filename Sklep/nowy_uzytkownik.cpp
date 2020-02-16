#include "nowy_uzytkownik.h"
#include "ui_nowy_uzytkownik.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>

extern QSqlDatabase db;

Nowy_uzytkownik::Nowy_uzytkownik(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Nowy_uzytkownik)
{
    ui->setupUi(this);

    setWindowTitle("Nowy użytkownik");
}

Nowy_uzytkownik::~Nowy_uzytkownik()
{
    delete ui;
}

void Nowy_uzytkownik::on_powrot_clicked()
{
    this->close();
    this->parentWidget()->show();
}

void Nowy_uzytkownik::on_utworz_konto_clicked()
{
    QString imie_ = "'" + ui->imie->text() + "'";
    QString nazwisko_ = "'" + ui->nazwisko->text() + "'";
    QString login_ = "'" + ui->login->text() + "'";
    QString haslo_ = "'" + ui->haslo->text() + "'";
    QString haslo2_ = "'" + ui->haslo2->text() + "'";
    QString telefon_ = "'" + ui->telefon->text() + "'";
    QString email_ ="'" + ui->email->text() + "'";

    QString ulica_ = "'" + ui->ulica->text() + "'";
    QString budynek_ = "'" + ui->budynek->text() + "'";
    QString mieszkanie_ = "'" + ui->mieszkanie->text() + "'";
    QString miasto_ = "'" + ui->miasto->text() + "'";
    QString kod_ = "'" + ui->kod->text() + "'";
    QString kraj_ = "'" + ui->kraj->text() + "'";

    QString login_spr = "";
    QString email_spr = "";

    QSqlQuery query(db);

    if(query.exec("SELECT * FROM sklep.login(" + login_ + ")"))
    {
        query.next();
        login_spr = query.value(0).toString();
    }
    else
        QMessageBox::warning(this, "Błąd", "Błąd połączenia!");

    if(query.exec("SELECT * FROM sklep.email(" + email_ + ")"))
    {
        query.next();
        email_spr = query.value(0).toString();
    }
    else
        QMessageBox::warning(this, "Błąd", "Błąd połączenia!");


    if( imie_ == "''" || nazwisko_ == "''" || login_ == "''" || haslo_ == "''" || haslo2_ == "''" ||
            telefon_ == "''" || email_ == "''" ||
            ulica_ == "''" || budynek_ == "''" || miasto_ == "''" || kod_ == "''" || kraj_ == "''")
        QMessageBox::critical(this, "Puste pola", "Należy uzupełnić wszystkie obowiązkowe pola!");
    else if(haslo_ != haslo2_)
        QMessageBox::critical(this, "Błąd hasła", "Hasło wpisane niepoprawnie!");
    else if(kod_.length() != 8 || kod_[3] != '-')
        QMessageBox::critical(this, "Błąd kodu pocztowego", "Źle wpisany kod pocztowy!");
    else if(login_spr == "TAK")
    {
        QMessageBox::critical(this, "Login", "Podany login jest już zajęty!");
    }
    else if(email_spr == "TAK")
    {
        QMessageBox::critical(this, "Email", "Podany adres email posiada już konto klienta!");
    }
    else
    {
        QSqlQuery query(db);
        QString id_dane_;
        QString id_adres_;

        if (query.exec("SELECT * FROM sklep.id_dane_next"))
        {
            query.next();
            id_dane_ = query.value(0).toString();

            if(id_dane_ == "")
                id_dane_ = '1';

            if(query.exec("INSERT INTO sklep.dane VALUES(" + id_dane_ + "," + imie_ + "," + nazwisko_ + "," + telefon_ + "," + email_ + "," + haslo_ + ")"))
            { 
                qDebug()<<"Dodano dane";

                if(query.exec("SELECT * FROM sklep.id_adres_next"))
                {
                    query.next();
                    id_adres_ = query.value(0).toString() + ",";

                    if(id_adres_ == "")
                        id_adres_ = '1';

                    if(query.exec("INSERT INTO sklep.adres VALUES(" + id_adres_ + ulica_ + "," + budynek_ + "," + mieszkanie_ + "," + kod_ + "," + miasto_ + "," + kraj_ +")"))
                    {
                        qDebug()<<"Dodano adres";

                        if(query.exec("INSERT INTO sklep.klient VALUES("+login_ + "," + id_adres_ + id_dane_ + ")"))
                        {
                            qDebug()<<"Dodano klienta";
                            s = new Sklep(this);
                            this->close();
                            s->show();
                        }
                        else
                            QMessageBox::warning(this, "Błąd", "Błąd połączenia! INSERT KLIENT");
                    }
                    else
                        QMessageBox::warning(this, "Błąd", "Błąd połączenia! INSERT ADRES");

                }
                else
                    QMessageBox::warning(this, "Błąd", "Błąd połączenia! ID_ADRES");
            }
            else
            {
               QMessageBox::warning(this, "Błąd", "Błąd połączenia! INSERT DANE");
            }

        }
        else
            QMessageBox::warning(this, "Błąd", "Błąd połączenia! ID_DANE");
    }
}

void Nowy_uzytkownik::closeEvent(QCloseEvent *event)
{
    this->parentWidget()->show();
}
