#include "ocena.h"
#include "ui_ocena.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QTableWidget>

extern QSqlDatabase db;

Ocena::Ocena(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ocena)
{
    ui->setupUi(this);
    this->setWindowTitle("Ocena produktu");
    ui->ocena->setCurrentIndex(9);
    ui->usun->setDisabled(true);
    ustaw();
}

Ocena::~Ocena()
{
    delete ui;
}

void Ocena::on_powrot_clicked()
{
    this->close();
}

void Ocena::on_dodaj_clicked()
{
    QString login_ = this->parentWidget()->findChild<QLabel*>("login")->text();
    int idx = this->parentWidget()->findChild<QTableWidget*>("tab_zrealizowane")->currentRow();
    QString produkt_ = this->parentWidget()->findChild<QTableWidget*>("tab_zrealizowane")->item(idx,0)->text();
    QString ocena_ = ui->ocena->currentText();
    QString komentarz_ = ui->komentarz->toPlainText();
    int len_ = ui->komentarz->toPlainText().length();

    if(len_>200)
    {
        QMessageBox::warning(this, "Błąd", "Komentarz jest za długi! (maks. 200 znaków)");
    }
    else
    {
        QSqlQuery query(db);
        if(query.exec("SELECT * FROM sprawdz_ocena('" + login_ + "', '" + produkt_ + "')"))
        {
            while(query.next())
            {
                if(query.value(0).toString() == "NIE")
                {
                    if(query.exec("INSERT INTO ocena_produktu VALUES ('"+ produkt_ + "', '" + login_ + "', " + ocena_ + ", '" + komentarz_ + "')"))
                    {
                        QMessageBox::information(this, "Ocena produktu", "Ocena została dodana!");
                        this->close();
                    }
                    else
                        QMessageBox::warning(this, "Błąd", "Błąd połączenia!");
                }
                else
                {
                    if(query.exec("UPDATE ocena_produktu SET ocena = " + ocena_ + ", komentarz = '" + komentarz_ +
                                  "' WHERE login LIKE '" + login_ + "' AND nazwa_produktu LIKE '" + produkt_ + "'"))
                    {
                        QMessageBox::information(this, "Ocena produktu", "Ocena została zmieniona!");
                        this->close();
                    }
                    else
                        QMessageBox::warning(this, "Błąd", "Błąd połączenia!");
                }
            }
        }
        else
            QMessageBox::warning(this, "Błąd", "Błąd połączenia!");
    }
}

void Ocena::ustaw()
{
    QSqlQuery query(db);
    QString login_ = this->parentWidget()->findChild<QLabel*>("login")->text();
    int idx = this->parentWidget()->findChild<QTableWidget*>("tab_zrealizowane")->currentRow();
    QString produkt_ = this->parentWidget()->findChild<QTableWidget*>("tab_zrealizowane")->item(idx,0)->text();

    if(query.exec("SELECT * FROM sprawdz_ocena('" + login_ + "', '" + produkt_ + "')"))
    {
        while(query.next())
        {
            if(query.value(0).toString() == "TAK")
            {
                if(query.exec("SELECT ocena, komentarz FROM ocena_produktu WHERE login LIKE '" + login_ +
                              "' AND nazwa_produktu LIKE '" + produkt_ + "'"))
                {
                    while(query.next())
                    {
                        ui->ocena->setCurrentIndex(query.value(0).toInt() - 1);
                        ui->komentarz->setText(query.value(1).toString());
                    }
                }
                else
                    QMessageBox::warning(this, "Błąd", "Błąd połączenia!");

                ui->usun->setEnabled(true);
            }
        }
    }
    else
        QMessageBox::warning(this, "Błąd", "Błąd połączenia!");
}

void Ocena::on_usun_clicked()
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, "Usuń ocenę", "Jesteś pewien, że chcesz usunąć ocenę?", QMessageBox::Yes | QMessageBox::No);

    if (button == QMessageBox::Yes)
    {
        QSqlQuery query(db);
        QString login_ = this->parentWidget()->findChild<QLabel*>("login")->text();
        int idx = this->parentWidget()->findChild<QTableWidget*>("tab_zrealizowane")->currentRow();
        QString produkt_ = this->parentWidget()->findChild<QTableWidget*>("tab_zrealizowane")->item(idx,0)->text();

        if(query.exec("DELETE FROM ocena_produktu WHERE login LIKE '" + login_ +
                      "' AND nazwa_produktu LIKE '" + produkt_ + "'"))
        {
            QMessageBox::information(this, "Ocena produktu", "Ocena została usunięta!");
            this->close();
        }
        else
            QMessageBox::warning(this, "Błąd", "Błąd połączenia!");
    }
}
