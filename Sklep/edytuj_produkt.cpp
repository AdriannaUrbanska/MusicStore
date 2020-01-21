#include "edytuj_produkt.h"
#include "ui_edytuj_produkt.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>

extern QSqlDatabase db;

Edytuj_produkt::Edytuj_produkt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Edytuj_produkt)
{
    ui->setupUi(this);

    QString produkt_ = this->parentWidget()->findChild<QLabel *>("produkt")->text();
    QString opis_ = this->parentWidget()->findChild<QLabel *>("opis")->text();
    int len_ = this->parentWidget()->findChild<QLabel *>("cena")->text().length();
    double cena_ = this->parentWidget()->findChild<QLabel *>("cena")->text().left(len_ - 2).toDouble();
    int sztuki_ = this->parentWidget()->findChild<QLabel *>("sztuki")->text().toInt();
    QString kategoria_ = this->parentWidget()->findChild<QLabel *>("kategoria")->text();
    int idx = 0;
    QString kat_;

    qDebug()<<this->parentWidget()->findChild<QLabel *>("cena")->text().length();

    QSqlQuery query(db);

    if(query.exec("SELECT id_kategoria AS id, nazwa FROM kategoria"))
    {
        while(query.next())
        {
            kat_ = query.value(1).toString();
            if(kat_ == kategoria_ )
                idx =  query.value(0).toInt() - 1;

            ui->kategoria->addItem(kat_);
        }
    }
    else
        QMessageBox::warning(this, "Błąd", "Błąd połączenia!");

    ui->produkt->setText(produkt_);
    ui->kategoria->setCurrentIndex(idx);
    ui->opis->setText(opis_);
    ui->cena->setValue(cena_);
    ui->sztuki->setValue(sztuki_);
}

Edytuj_produkt::~Edytuj_produkt()
{
    delete ui;
}

void Edytuj_produkt::on_powrot_clicked()
{
    this->close();
}

void Edytuj_produkt::on_zapisz_clicked()
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
    else
    {
        QMessageBox::StandardButton button;
        button = QMessageBox::question(this, "Zapisz zmiany", "Jesteś pewien, że chcesz zapisać zmiany?", QMessageBox::Yes | QMessageBox::No);

        if (button == QMessageBox::Yes)
        {
            QMessageBox::information(this, "Zapisz zmiany", "Zmiany zostały zapisane!");
            this->close();
        }
    }
}
