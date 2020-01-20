#include "nowy_uzytkownik.h"
#include "ui_nowy_uzytkownik.h"
#include <QMessageBox>

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
    QString imie_ = ui->imie->text();
    QString nazwisko_ = ui->nazwisko->text();
    QString login_ = ui->login->text();
    QString haslo_ = ui->haslo->text();
    QString haslo2_ = ui->haslo2->text();
    QString telefon_ = ui->telefon->text();
    QString email_ = ui->email->text();

    QString ulica_ = ui->ulica->text();
    QString budynek_ = ui->budynek->text();
    QString mieszkanie_ = ui->mieszkanie->text();
    QString miasto_ = ui->miasto->text();
    QString kod_ = ui->kod->text();
    QString kraj_ = ui->kraj->text();

    if( imie_ == "" || nazwisko_ == "" || login_ == "" || haslo_ == "" || haslo2_ == "" ||
            telefon_ == "" || email_ == "" ||
            ulica_ == "" || budynek_ == "" || miasto_ == "" || kod_ == "" || kraj_ == "")
        QMessageBox::critical(this, "Puste pola", "Należy uzupełnić wszystkie obowiązkowe pola!");
    else if(haslo_ != haslo2_)
        QMessageBox::critical(this, "Błąd hasła", "Hasło wpisane niepoprawnie!");
    else
    {
        s = new Sklep(this);
        this->close();
        s->show();
    }
}

void Nowy_uzytkownik::closeEvent(QCloseEvent *event)
{
    this->parentWidget()->show();
}
