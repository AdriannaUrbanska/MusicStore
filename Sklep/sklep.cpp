#include "sklep.h"
#include "ui_sklep.h"
#include <QListWidget>
#include <QDate>
#include <QDebug>
#include <QCheckBox>
#include <QRadioButton>
#include <QSqlQuery>
#include <QMessageBox>

extern QSqlDatabase db;

Sklep::Sklep(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sklep)
{
    ui->setupUi(this);

    QDate date = QDate::currentDate();
    setWindowTitle("Sklep muzyczny " + date.toString("dd-MM-yyyy"));

    ui->kategoria->addItem("Wszystkie");
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

    produkty();

    ui->listWidget->setCurrentRow(0);

    connect(ui->listWidget, SIGNAL(activated(QModelIndex)), this, SLOT(openProdukt(QModelIndex)));

    if (QString::fromUtf8(this->parentWidget()->metaObject()->className()) == "Nowy_uzytkownik")
    {
        QSqlQuery query(db);

        if(query.exec("SELECT login FROM klient"))
        {
            while(query.next())
            {
                login_ = query.value(0).toString();
            }
        }
        else
            QMessageBox::warning(this, "Błąd", "Błąd połączenia!");
    }
    else
    {
        login_ = this->parentWidget()->findChild<QLineEdit*>("login")->text();
    }

    ui->login->setText(login_);
}

Sklep::~Sklep()
{
    delete ui;
}

void Sklep::on_m_zamowienia_clicked()
{
    m_z = new Moje_zamowienia(this);
    m_z->show();
}

void Sklep::on_produkt_info_clicked()
{
    p = new Produkt(this);
    p->show();
}

void Sklep::on_wyloguj_clicked()
{
    this->close();

    if (QString::fromUtf8(this->parentWidget()->metaObject()->className()) == "Nowy_uzytkownik")
    {
        this->parentWidget()->parentWidget()->show();
        this->parentWidget()->parentWidget()->findChild<QLineEdit*>("login")->setText("");
        this->parentWidget()->parentWidget()->findChild<QLineEdit*>("haslo")->setText("");
        this->parentWidget()->parentWidget()->findChild<QCheckBox*>("pokaz_haslo")->setChecked(false);
        this->parentWidget()->parentWidget()->findChild<QRadioButton*>("radioKlient")->setChecked(true);
    }
    else
    {
        this->parentWidget()->show();
        this->parentWidget()->findChild<QLineEdit*>("login")->setText("");
        this->parentWidget()->findChild<QLineEdit*>("haslo")->setText("");
        this->parentWidget()->findChild<QCheckBox*>("pokaz_haslo")->setChecked(false);
        this->parentWidget()->findChild<QRadioButton*>("radioKlient")->setChecked(true);
    }
}

void Sklep::closeEvent(QCloseEvent *event)
{
    if (QString::fromUtf8(this->parentWidget()->metaObject()->className()) == "Nowy_uzytkownik")
    {
        this->parentWidget()->parentWidget()->show();
        this->parentWidget()->parentWidget()->findChild<QLineEdit*>("login")->setText("");
        this->parentWidget()->parentWidget()->findChild<QLineEdit*>("haslo")->setText("");
        this->parentWidget()->parentWidget()->findChild<QCheckBox*>("pokaz_haslo")->setChecked(false);
        this->parentWidget()->parentWidget()->findChild<QRadioButton*>("radioKlient")->setChecked(true);
    }
    else
    {
        this->parentWidget()->show();
        this->parentWidget()->findChild<QLineEdit*>("login")->setText("");
        this->parentWidget()->findChild<QLineEdit*>("haslo")->setText("");
        this->parentWidget()->findChild<QCheckBox*>("pokaz_haslo")->setChecked(false);
        this->parentWidget()->findChild<QRadioButton*>("radioKlient")->setChecked(true);
    }
}

void Sklep::produkty()
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


    if(query.exec("SELECT nazwa_produktu FROM produkt " + kategoria_ + "ORDER BY nazwa_produktu " + sort))
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

void Sklep::on_wybierz_clicked()
{
    produkty();
    ui->listWidget->setCurrentRow(0);
    ui->lineEdit->setText("");
}

void Sklep::on_szukaj_clicked()
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

void Sklep::openProdukt(const QModelIndex &)
{
    on_produkt_info_clicked();
}

void Sklep::on_sklep_info_clicked()
{
    si = new Sklep_info(this);
    si->show();
}
