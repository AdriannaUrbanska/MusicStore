#include "sklep_pracownik.h"
#include "ui_sklep_pracownik.h"
#include <QDate>
#include <QCheckBox>
#include <QSqlDatabase>
#include <QRadioButton>
#include <QSqlQuery>
#include <QMessageBox>

extern QSqlDatabase db;

Sklep_pracownik::Sklep_pracownik(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sklep_pracownik)
{
    ui->setupUi(this);

    QDate date = QDate::currentDate();
    setWindowTitle("Sklep muzyczny " + date.toString("dd-MM-yyyy"));

    ui->kategoria->addItem("Wszystkie");

    QSqlQuery query(db);

    if(query.exec("SELECT nazwa FROM sklep.kategoria"))
    {
        while(query.next())
        {
            ui->kategoria->addItem(query.value(0).toString());
        }
    }
    else
        QMessageBox::warning(this, "Błąd", "Błąd połączenia!");

    produkty();
    ui->listWidget->setCurrentRow(0);

    connect(ui->listWidget, SIGNAL(activated(QModelIndex)), this, SLOT(openProdukt(QModelIndex)));
}

Sklep_pracownik::~Sklep_pracownik()
{
    delete ui;
}

void Sklep_pracownik::on_wyloguj_clicked()
{
    this->close();
    this->parentWidget()->show();
    this->parentWidget()->findChild<QLineEdit*>("login")->setText("");
    this->parentWidget()->findChild<QLineEdit*>("haslo")->setText("");
    this->parentWidget()->findChild<QCheckBox*>("pokaz_haslo")->setChecked(false);
    this->parentWidget()->findChild<QRadioButton*>("radioKlient")->setChecked(true);
}

void Sklep_pracownik::on_zamowienia_clicked()
{
    z_p = new Zamowienia_pracownik(this);
    z_p->show();
}

void Sklep_pracownik::on_produkt_info_clicked()
{
    p_p = new Produkt_pracownik(this);
    p_p->show();
}

void Sklep_pracownik::on_dodaj_clicked()
{
    d_p = new Dodaj_produkt(this);
    d_p->show();
}

void Sklep_pracownik::produkty()
{
    QSqlQuery query(db);
    QString sort{""};
    QString kategoria_;

    if(ui->sortowanie->currentIndex() == 1)
        sort = "DESC";

    switch (ui->kategoria->currentIndex())
    {
        case 0:
            kategoria_ = "";
            break;
        case 1:
            kategoria_ = "WHERE id_kategoria = 1 ";
            break;
        case 2:
            kategoria_ = "WHERE id_kategoria = 2 ";
            break;
        case 3:
            kategoria_ = "WHERE id_kategoria = 3 ";
            break;
        case 4:
            kategoria_ = "WHERE id_kategoria = 4 ";
            break;
        case 5:
            kategoria_ = "WHERE id_kategoria = 5 ";
            break;
    }


    if(query.exec("SELECT nazwa_produktu FROM sklep.produkt " + kategoria_ + "ORDER BY nazwa_produktu " + sort))
    {
        ui->listWidget->clear();
        while(query.next())
        {
            ui->listWidget->addItem(query.value(0).toString());
        }
    }
    else
        QMessageBox::warning(this, "Błąd", "Błąd połączenia!");
}

void Sklep_pracownik::on_wybierz_clicked()
{
    produkty();
    ui->listWidget->setCurrentRow(0);
    ui->lineEdit->setText("");
}

void Sklep_pracownik::closeEvent(QCloseEvent *event)
{
    this->close();
    this->parentWidget()->show();
    this->parentWidget()->findChild<QLineEdit*>("login")->setText("");
    this->parentWidget()->findChild<QLineEdit*>("haslo")->setText("");
    this->parentWidget()->findChild<QCheckBox*>("pokaz_haslo")->setChecked(false);
    this->parentWidget()->findChild<QRadioButton*>("radioKlient")->setChecked(true);
}

void Sklep_pracownik::on_szukaj_clicked()
{
    QString tmp = ui->lineEdit->text().toLower();
    QString nazwa_ = tmp;
    nazwa_[0] = tmp[0].toUpper();

    QSqlQuery query(db);

    if(query.exec("SELECT n FROM produkty WHERE n LIKE '" + nazwa_ + "%'"))
    {
        ui->listWidget->clear();
        while(query.next())
        {
            ui->listWidget->addItem(query.value(0).toString());
        }
    }
    else
        QMessageBox::warning(this, "Błąd", "Nie znaleziono produktu o podanej nazwie!");

    ui->listWidget->setCurrentRow(0);
}

void Sklep_pracownik::openProdukt(const QModelIndex &)
{
    on_produkt_info_clicked();
}
