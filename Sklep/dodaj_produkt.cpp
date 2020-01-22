#include "dodaj_produkt.h"
#include "ui_dodaj_produkt.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QMessageBox>
#include <QListWidget>
#include <QComboBox>
#include <QDebug>

extern QSqlDatabase db;

Dodaj_produkt::Dodaj_produkt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dodaj_produkt)
{
    ui->setupUi(this);

    QSqlQuery query(db);

    if(query.exec("SELECT nazwa FROM kategoria"))
    {
        while(query.next())
        {
            ui->kategoria->addItem(query.value(0).toString());
        }
    }
    else
        QMessageBox::warning(this, "Błąd", "Błąd połączenia!");
}

Dodaj_produkt::~Dodaj_produkt()
{
    delete ui;
}

void Dodaj_produkt::on_powrot_clicked()
{
    this->close();
}

void Dodaj_produkt::on_dodaj_clicked()
{
    QString produkt_ = "'" + ui->produkt->text() + "', ";
    QString kategoria_ = QString::number(ui->kategoria->currentIndex()+1) + ", ";
    QString cena_ = QString::number(ui->cena->value()) + ", '";
    QString opis_ = ui->opis->toPlainText()+ "', ";
    QString sztuki_ = QString::number(ui->sztuki->value());
    int len_ = opis_.length()-2;

    if (len_>200)
    {
        QMessageBox::warning(this, "Błąd", "Wpisany opis jest za długi!");
    }
    else if (produkt_ == "'', ")
    {
        QMessageBox::warning(this, "Błąd", "Produkt musi mieć nazwę!");
    }
    else
    {
        QString query_ = "INSERT INTO produkt VALUES (" + produkt_ + kategoria_ + cena_ + opis_ + sztuki_ + ");";

        QSqlQuery query(db);
        if(query.exec(query_))
        {
            QMessageBox::information(this, "Dodaj produkt", "Produkt został dodany!");
            this->close();

            QListWidget *list = this->parentWidget()->parentWidget()->findChild<QListWidget*>("listWidget");
            this->parentWidget()->parentWidget()->findChild<QComboBox*>("kategoria")->setCurrentText(0);
            this->parentWidget()->parentWidget()->findChild<QComboBox*>("sortowanie")->setCurrentText(0);

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
