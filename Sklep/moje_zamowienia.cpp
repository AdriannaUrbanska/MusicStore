#include "moje_zamowienia.h"
#include "ui_moje_zamowienia.h"
#include <QTableWidgetItem>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QAbstractItemView>

extern QSqlDatabase db;

Moje_zamowienia::Moje_zamowienia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Moje_zamowienia)
{
    ui->setupUi(this);
    this->setWindowTitle("Moje zamówienia");
    QString login_ = this->parentWidget()->findChild<QLabel*>("login")->text();

    setWindowTitle("Moje zamowienia - uzytkownik: " + login_);
    ui->tab_zrealizowane->setColumnWidth(0,150);
    ui->tab_zrealizowane->setColumnWidth(1,80);
    ui->tab_zrealizowane->setColumnWidth(2,120);
    ui->tab_zrealizowane->setColumnWidth(3,160);
    ui->tab_zrealizowane->setColumnWidth(4,50);

    ui->tab_w_trakcie->setColumnWidth(0,150);
    ui->tab_w_trakcie->setColumnWidth(1,80);
    ui->tab_w_trakcie->setColumnWidth(2,120);
    ui->tab_w_trakcie->setColumnWidth(3,160);
    ui->tab_w_trakcie->setColumnWidth(4,50);

    zamowienia();
    zmien(0);

    ui->tab->setCurrentIndex(0);
    ui->tab_zrealizowane->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tab_zrealizowane->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tab_zrealizowane->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tab_zrealizowane->selectRow(0);

    ui->tab_w_trakcie->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tab_w_trakcie->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tab_w_trakcie->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tab_w_trakcie->selectRow(0);

    if(ui->tab_w_trakcie->rowCount() == 0)
    {
        ui->anuluj->setDisabled(true);
        ui->info->setDisabled(true);
    }

    if(ui->tab_zrealizowane->rowCount() == 0)
        ui->ocena->setDisabled(true);

    connect(ui->tab, SIGNAL(currentChanged(int)), this, SLOT(zmien(int)));

    connect(ui->tab_w_trakcie, SIGNAL(activated(QModelIndex)), this, SLOT(openInfo(QModelIndex)));
    connect(ui->tab_zrealizowane, SIGNAL(activated(QModelIndex)), this, SLOT(openInfo(QModelIndex)));
}

void Moje_zamowienia::zamowienia()
{
    QString login_ = this->parentWidget()->findChild<QLabel*>("login")->text();
    ui->login->setText(login_);

    QSqlQuery query(db);

    i_w_trakcie = 0;
    i_zrealizowane = 0;

    if(query.exec("SELECT * FROM sklep.wyszukaj_zamowienia('" + login_ + "')"))
    {
        while(query.next())
        {    
            if(query.value(3).toString() == "W trakcie realizacji")
            {
                ui->tab_w_trakcie->insertRow(i_w_trakcie);
                ui->anuluj->setEnabled(true);
                ui->tab_w_trakcie->setItem(i_w_trakcie,0,new QTableWidgetItem(query.value(0).toString()));
                ui->tab_w_trakcie->setItem(i_w_trakcie,1,new QTableWidgetItem(query.value(1).toString()));
                ui->tab_w_trakcie->setItem(i_w_trakcie,2,new QTableWidgetItem(query.value(2).toString()));
                ui->tab_w_trakcie->setItem(i_w_trakcie,3,new QTableWidgetItem(query.value(3).toString()));
                ui->tab_w_trakcie->setItem(i_w_trakcie,4,new QTableWidgetItem(query.value(4).toString()));
                i_w_trakcie++;
            }
            else
            {
                ui->tab_zrealizowane->insertRow(i_zrealizowane);
                ui->tab_w_trakcie->setEnabled(true);
                ui->tab_zrealizowane->setItem(i_zrealizowane,0,new QTableWidgetItem(query.value(0).toString()));
                ui->tab_zrealizowane->setItem(i_zrealizowane,1,new QTableWidgetItem(query.value(1).toString()));
                ui->tab_zrealizowane->setItem(i_zrealizowane,2,new QTableWidgetItem(query.value(2).toString()));
                ui->tab_zrealizowane->setItem(i_zrealizowane,3,new QTableWidgetItem(query.value(3).toString()));
                ui->tab_zrealizowane->setItem(i_zrealizowane,4,new QTableWidgetItem(query.value(4).toString()));
                i_zrealizowane++;
            }

            if(i_w_trakcie != 0)
                ui->tab_w_trakcie->selectRow(0);
            if(i_zrealizowane != 0)
                ui->tab_zrealizowane->selectRow(0);
        }
    }
    else
        QMessageBox::warning(this, "Błąd", "Błąd połączenia!");
}

Moje_zamowienia::~Moje_zamowienia()
{
    delete ui;
}

void Moje_zamowienia::on_powrot_clicked()
{
    this->close();
}

void Moje_zamowienia::on_anuluj_clicked()
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, "Anuluj zamówienie", "Jesteś pewien, że chcesz anulować zamówienie?", QMessageBox::Yes | QMessageBox::No);

    if (button == QMessageBox::Yes)
    {
        QSqlQuery query(db);
        int idx = ui->tab_w_trakcie->currentRow();
        QString zamowienie_ = ui->tab_w_trakcie->item(idx,4)->text();
        QString produkt_ = ui->tab_w_trakcie->item(idx,0)->text();
        QString sztuki_ = "";

        if(query.exec("SELECT liczba_sztuk FROM sklep.zamowienie WHERE id_zamowienie = " + zamowienie_))
        {
            while(query.next())
            {
                sztuki_ = query.value(0).toString();
            }
        }
        else
            QMessageBox::warning(this, "Błąd", "Błąd połączenia!");


        if(query.exec("DELETE FROM sklep.produkt_zamowienie WHERE id_zamowienie = " + zamowienie_))
        {
            QMessageBox::information(this, "Anulowanie zamówienia", "Zamówienie zostało anulowane!");
            ui->tab_w_trakcie->setRowCount(0);
            ui->tab_zrealizowane->setRowCount(0);
            zamowienia();

            if(ui->tab_w_trakcie->rowCount() == 0)
                ui->anuluj->setDisabled(true);
        }
        else
            QMessageBox::warning(this, "Błąd", "Błąd połączenia!");


        if(!query.exec("SELECT * FROM sklep.sztuki_dodaj('" + produkt_ + "', " + sztuki_ + ")"))
        {
            QMessageBox::warning(this, "Błąd", "Błąd połączenia!");
        }

    }
}

void Moje_zamowienia::on_ocena_clicked()
{
    o = new Ocena(this);
    o->show();
}

void Moje_zamowienia::on_info_clicked()
{
    zi = new Zamowienie_info(this);
    zi->show();
}

void Moje_zamowienia::zmien(int i)
{
    if(ui->tab->currentIndex() == 0)
    {
        if(i_w_trakcie == 0)
            ui->info->setDisabled(true);
        else
        {
            ui->info->setEnabled(true);
            ui->tab_w_trakcie->selectRow(0);
        }
    }
    else
    {
        if(i_zrealizowane == 0)
            ui->info->setDisabled(true);
        else
        {
            ui->info->setEnabled(true);
            ui->tab_zrealizowane->selectRow(0);
        }
    }
}

void Moje_zamowienia::openInfo(const QModelIndex &)
{
    on_info_clicked();
}
