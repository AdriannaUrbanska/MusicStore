#include "produkt_pracownik.h"
#include "ui_produkt_pracownik.h"
#include <QMessageBox>
#include <QAbstractButton>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QListWidget>
#include <QComboBox>

extern QSqlDatabase db;

Produkt_pracownik::Produkt_pracownik(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Produkt_pracownik)
{
    ui->setupUi(this);
    ui->opis->setWordWrap(true);
    info();
}

Produkt_pracownik::~Produkt_pracownik()
{
    delete ui;
}

void Produkt_pracownik::on_powrot_clicked()
{
    this->close();
}

void Produkt_pracownik::on_edytuj_clicked()
{
    e_p = new Edytuj_produkt(this);
    e_p->show();
}

void Produkt_pracownik::on_usun_clicked()
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, "Usuń produkt", "Jesteś pewien, że chcesz usunąć ten produkt?", QMessageBox::Yes | QMessageBox::No);

    QString nazwa_ = ui->produkt->text();
    QSqlQuery query(db);

    if (button == QMessageBox::Yes)
    {
        if(query.exec("DELETE FROM produkt WHERE nazwa_produktu LIKE '"+ nazwa_ + "'"))
        {
            QMessageBox::information(this, "Usuń produkt", "Produkt został usunięty!");
            this->close();

            QListWidget *list = this->parentWidget()->findChild<QListWidget*>("listWidget");
            this->parentWidget()->findChild<QComboBox*>("kategoria")->setCurrentText(0);
            this->parentWidget()->findChild<QComboBox*>("sortowanie")->setCurrentText(0);

            if(query.exec("SELECT nazwa_produktu FROM produkt ORDER BY nazwa_produktu "))
            {
                list->clear();
                while(query.next())
                {
                    list->addItem(query.value(0).toString());
                }
            }
            else
                QMessageBox::warning(this, "Błąd", "Błąd połączenia!");
        }
        else
            QMessageBox::warning(this, "Błąd", "Błąd połączenia!");
    }
}

void Produkt_pracownik::info()
{
    QString produkt_ = this->parentWidget()->findChild<QListWidget*>("listWidget")->currentItem()->text();
    QString kategoria_{""};
    QString opis_{""};
    QString cena_{""};
    QString sztuki_{""};

    QSqlQuery query(db);

    if(query.exec("SELECT * FROM produkty WHERE n LIKE '" + produkt_ + "'"))
    {
        while(query.next())
        {
            kategoria_ = query.value(1).toString();
            opis_ = query.value(2).toString();
            cena_ = query.value(3).toString() + "zł";
            sztuki_ = query.value(4).toString();
        }
    }
    else
        QMessageBox::warning(this, "Błąd", "Błąd połączenia!");

    if(opis_ == "") opis_ = "Brak opisu";
    if(cena_ == "0") cena_ = "Brak ceny";
    if(sztuki_ == "0") sztuki_ = "Brak dostępnych sztuk";

    ui->produkt->setText(produkt_);
    ui->kategoria->setText(kategoria_);
    ui->opis->setText(opis_);
    ui->cena->setText(cena_);
    ui->sztuki->setText(sztuki_);
}
